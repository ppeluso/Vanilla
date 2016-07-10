Portfolio = 100000
quantity = 0 
buyStock <-
  function(price, q, quantity)
  {
   Portfolio = Portfolio - (price * q)
   quantity =  quantity + q
  }
sellStock <- 
  function(price, q, quantity)
  {
    Portfolio = Portfolio + (price * q)
    quantity = quantity + q
  }

value <- 
  function(p)
  {
    return((p * quantity )+ Portfolio)
  }
print(Portfolio)
buyStock(100, 10, 10)
print(quantity)
print( value(90))

