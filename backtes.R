# require(quantmod)
# require(PerformanceAnalytics)
# require(fUnitRoots)
# require(tseries)
# 
# symbols <- c("SPY", "AAL")
# 
# getSymbols(symbols)
# 
# #training set 
# startT <- "2009-01-01"
# endT <- "2009-01-01"
# rangeT <- paste(startT,"::", endT, sep="")
# tTLT <-TLT[,6][rangeT]
# tJOE <-JOE[,6][rangeT]
# 
# #out of sampe
# 
# startO <- "2009-02-01"
# endO <- "2010-12-01"
# rangeO <- paste(startO, "::", endO, sep="")
# oTLT <- TLT[,6][rangeO]
# oJOE <- JOE[,6][rangeO]
# 
# pdtTLT <- diff(tTLT)[-1]
# pdtJOE <- diff(tJOE)[-1]
# 
# model <- lm(pdtTLT ~ pdtJOE - 1)
# hr <- as.numeric(model$coefficients[1])
# 
# spreadT <- tTLT - hr * tJOE 
# 
# meanT <- as.numeric(mean(spreadT, na.rm=TRUE))
# sdT <- as.numeric(sd(spreadT, na.rm=TRUE))
# 
# upperThr <- meanT + 1 * sdT
# lowerThr <- meanT - 1 * sdT
# 
# plot(spreadT, main = "TLT vs. JOE spread (in-sample period)")
# abline(h = meanT, col = "red", lwd =2)
# abline(h = meanT + 1 * sdT, col = "blue", lwd=2)
# abline(h = meanT - 1 * sdT, col = "blue", lwd=2)
# 
# hist(spreadT, col = "blue", breaks = 100, main = "Spread Histogram (TLT vs. JOE)")
# abline(v = meanT, col = "red", lwd = 2)
# 
# indSell <- which(spreadT >= meanT + sdT)
# indBuy <- which(spreadT <= meanT - sdT)
# 
# spreadL <- length(spreadT)
# pricesB <- c(rep(NA,spreadL))
# pricesS <- c(rep(NA,spreadL))
# sp <- as.numeric(spreadT)
# tradeQty <- 100
# totalP <-0
# 
# poop <- FALSE
# for(i in 1:spreadL) {
#   spTemp <- sp[i]
#   if(spTemp < lowerThr) {
#     if(totalP <= 0){
#       totalP     <- totalP + tradeQty
#       pricesB[i] <- spTemp
#       
#     }
#   } 
#   else if(spTemp > upperThr) {
#     if(totalP >= 0)
#       {
#       totalP <- totalP - tradeQty
#       pricesS[i] <- spTemp
#      
#     }
#   }
# 
# 
# }
# 
# plot(spreadT, main = "TLT vs. JOE spread (in-sample period)")
# abline(h = meanT, col = "red", lwd =2)
# abline(h = meanT + 1 * sdT, col = "blue", lwd = 2)
# abline(h = meanT - 1 * sdT, col = "blue", lwd = 2)
# points(xts(pricesB,index(spreadT)), col="green", cex=1.9, pch=19)
# points(xts(pricesS,index(spreadT)), col="red", cex=1.9, pch=19)

symbolLst<-c("AAL","SPY")
title<-c("AAL vs LUV")

symbolData <- new.env() #Make a new environment for quantmod to store data in
getSymbols(symbolLst, env = symbolData, src = "yahoo", from =startT)

stockPair <- list(
  a = coredata(Cl(eval(parse(text=paste("symbolData$\"",symbolLst[1],"\"",sep="")))))   #Stock A
  ,b = coredata(Cl(eval(parse(text=paste("symbolData$\"",symbolLst[2],"\"",sep=""))))) #Stock B
  ,hedgeRatio = -0.15156872035821
  ,name=title)

testForCointegration <- function(stockPairs){
  #Pass in a pair of stocks and do the necessary checks to see if it is cointegrated
  
  #Plot the pairs
  
  dev.new()
  par(mfrow=c(2,2))
  print(c((0.99*min(rbind(stockPairs$a,stockPairs$b))),(1.01*max(rbind(stockPairs$a,stockPairs$b)))))
  plot(stockPairs$a, main=stockPairs$name, ylab="Price", type="l", col="red",ylim=c((0.99*min(rbind(stockPairs$a,stockPairs$b))),(1.01*max(rbind(stockPairs$a,stockPairs$b)))))
  lines(stockPairs$b, col="blue")
  print(length(stockPairs$a))
  print(length(stockPairs$b))
  #Step 1: Calculate the daily returns
  dailyRet.a <- na.omit((Delt(stockPairs$a,type="arithmetic")))
  dailyRet.b <- na.omit((Delt(stockPairs$b,type="arithmetic")))
  dailyRet.a <- dailyRet.a[is.finite(dailyRet.a)] #Strip out any Infs (first ret is Inf)
  dailyRet.b <- dailyRet.b[is.finite(dailyRet.b)]
  
  print(length(dailyRet.a))
  print(length(dailyRet.b))
  #Step 2: Regress the daily returns onto each other
  #Regression finds BETA and C in the linear regression retA = BETA * retB + C
  regression <- lm(dailyRet.a ~ dailyRet.b + 0)
  beta <- coef(regression)[1]
  print(paste("The beta or Hedge Ratio is: ",beta,sep=""))
  plot(x=dailyRet.b,y=dailyRet.a,type="p",main="Regression of RETURNS for Stock A & B") #Plot the daily returns
  lines(x=dailyRet.b,y=(dailyRet.b*beta),col="blue")#Plot in linear line we used in the regression
  
  
  #Step 3: Use the regression co-efficients to generate the spread
  spread <- stockPairs$a - beta*stockPairs$b  #Could actually just use the residual form the regression its the same thing
  spreadRet <- Delt(spread,type="arithmetic")
  spreadRet <- na.omit(spreadRet)
  #spreadRet[!is.na(spreadRet)]
  plot((spreadRet), type="l",main="Spread Returns") #Plot the cumulative sum of the spread
  plot(spread, type="l",main="Spread Actual") #Plot the cumulative sum of the spread
  #For a cointegrated spread the cumsum should not deviate very far from 0
  #For a none-cointegrated spread the cumsum will likely show some trending characteristics
  
  #Step 4: Use the ADF to test if the spread is stationary
  #can use tSeries library
  adfResults <- adf.test((spread),k=0,alternative="stationary")
  
  print(adfResults)
  if(adfResults$p.value <= 0.05){
    print(paste("The spread is likely Cointegrated with a pvalue of ",adfResults$p.value,sep=""))
  } else {
    print(paste("The spread is likely NOT Cointegrated with a pvalue of ",adfResults$p.value,sep=""))
  }
  
}

simulateTrading <- function(stockPair){
  #Generate the spread
  spread <- stockPair$a - stockPair$hedgeRatio*stockPair$b
  
  #Strategy is if the spread is greater than +/- nStd standard deviations of it's rolling 'lookback' day standard deviation
  #Then go long or short accordingly
  lookback <- 90 #look back 90 days
  nStd <- 1 #Number of standard deviations from the mean to trigger a trade
  
  movingAvg = rollmean(spread,lookback, na.pad=TRUE) #Moving average
  movingStd = rollapply(spread,lookback,sd,align="right", fill = NA ) #Moving standard deviation / bollinger bands
  
  upperThreshold = movingAvg + nStd*movingStd
  lowerThreshold = movingAvg - nStd*movingStd
  
  aboveUpperBand <- spread>upperThreshold
  belowLowerBand <- spread<lowerThreshold
  
  aboveMAvg <- spread>movingAvg
  belowMAvg <- spread<movingAvg
  
  aboveUpperBand[is.na(aboveUpperBand)]<-0
  belowLowerBand[is.na(belowLowerBand)]<-0
  aboveMAvg[is.na(aboveMAvg)]<-0
  belowMAvg[is.na(belowMAvg)]<-0
  
  #The cappedCumSum function is where the magic happens
  #Its a nice trick to avoid writing a while loop
  #Hence since using vectorisation is faster than the while loop
  #The function basically does a cumulative sum, but caps the sum to a min and max value
  #It's used so that if we get many 'short sell triggers' it will only execute a maximum of 1 position
  #Short position - Go short if spread is above upper threshold and go long if below the moving avg
  #Note: shortPositionFunc only lets us GO short or close the position
  cappedCumSum <- function(x, y,max_value,min_value) max(min(x + y, max_value), min_value)
  shortPositionFunc <- function(x,y) { cappedCumSum(x,y,0,-1) }
  longPositionFunc <- function(x,y) { cappedCumSum(x,y,1,0) }
  shortPositions <- Reduce(shortPositionFunc,-1*aboveUpperBand+belowMAvg,accumulate=TRUE)
  longPositions <- Reduce(longPositionFunc,-1*aboveMAvg+belowLowerBand,accumulate=TRUE)
  positions = longPositions + shortPositions
  
  dev.new()
  par(mfrow=c(2,1))
  plot(movingAvg,col="red",ylab="Spread",type='l',lty=2)
  title("AAL vs LUV spread with bollinger bands")
  lines(upperThreshold, col="red")
  lines(lowerThreshold, col="red")
  lines(spread, col="blue")
  legend("topright", legend=c("Spread","Moving Average","Upper Band","Lower Band"), inset = .02,
         lty=c(1,2,1,1),col=c("blue","red","red","red")) # gives the legend lines the correct color and width
  
  plot((positions),type='l')
  
  #Calculate spread daily ret
  stockPair$a - stockPair$hedgeRatio*stockPair$b
  aRet <- Delt(stockPair$a,k=1,type="arithmetic")
  bRet <- Delt(stockPair$b,k=1,type="arithmetic")
  dailyRet <- aRet - stockPair$hedgeRatio*bRet
  dailyRet[is.na(dailyRet)] <- 0
  
  tradingRet <- dailyRet * positions
  simulateTrading <- tradingRet
}

tradingRet <- simulateTrading(stockPair)


#### Performance Analysis ###
#Calculate returns for the index
indexRet <- Delt(Cl(eval(parse(text=paste("symbolData$\"",symbolLst[1],"\"",sep="")))),k=1,type="arithmetic") #Daily returns
indexRet <- as.zoo(indexRet)
tradingRetZoo <- indexRet
tradingRetZoo[,1] <- tradingRet
zooTradeVec <- as.zoo(cbind(tradingRetZoo,indexRet)) #Convert to zoo object
colnames(zooTradeVec) <- c("AAL v. LUV Stat Arb","AAL")
zooTradeVec <- na.omit(zooTradeVec)

#Lets see how all the strategies faired against the index
dev.new()
charts.PerformanceSummary(zooTradeVec,main="TLT v. FXE statArb",geometric=FALSE)

cat("Sharpe Ratio")
print(SharpeRatio.annualized(zooTradeVec))
