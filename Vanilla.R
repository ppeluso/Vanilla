BS <-
  function(S,K,T,r,sig,type = "C"){
    d1 <- (log(S/K) + (r + sig^2/2)*T) / (sig *sqrt(T))
    d2 <- d1 -sig * sqrt(T)
    
    if(type=="C")
    {
      value <- S*pnorm(d1) - K *exp(-r*T)* pnorm(d2)
    }
    
    if(type=="P")
    {
      value <- K*exp(-r*T)*pnorm(-d2)-S*pnorm(-d1)
    }
    return(value)
  }
implied.vol <-
  function(S, K, T, r, market, type){
    sig <- 0.20
    sig.up <- 1
    sig.down <- 0.001
    count <-  0
    err <- BS(S, K, T, r, sig, type) - market 
    
    
    while(abs(err) > 0.00001 && count<1000){
      if(err < 0){
        sig.down <- sig
        sig <- (sig.up + sig)/2
      }else{
        sig.up <- sig
        sig <- (sig.down + sig)/2
      }
      err <- BS(S, K, T, r, sig, type) - market
      count <- count + 1
    }
    
    
    if(count==1000){
      return(NA)
    }else{
      return(sig)
    }
  }

impVolSmile <- c()
impVolSmileStrike <- c()
for(i in 1:61)
{
  impVolSmile[i] <- implied.vol(2102.95, SPX_option.$Strike[i], 12.0/252.0, .017, SPX_option.$Last[i], "C")
  impVolSmileStrike[i] <- SPX_option.$Strike[i]
  
}

TOSiv <- c()
TOSiv <- as.numeric(sub("%","",SPX_option.$IV))/100


plot(impVolSmileStrike,impVolSmile, type = "l", col = "blue", xlab = "SPX Strike", ylab = "Implied Volatility", main = "SPX JUL 16 Call Options")
lines(SPX_option.$Strike,TOSiv, col = "green")

 f <-qplot( impVolSmileStrike, impVolSmile)
 print (f)
 


