quantiles <- function(X,k,method)
{
  # derived from code provided by Hyeyoung Maeng 
  n <- length(X)
  Q <- matrix(0, k, n+1)
  sorted.X = sort(X)
  yk = -1 + (2*(1:k)/k-1/k)
  c = -log(2*n-1)
  if(method=="equally")
  {
    pk = seq(0, 1, length.out = k+2)[-c(1, k+2)]
  }
  else
  {
    pk  = (1+exp(c*yk))^-1
  }
  qnt = rep(NA, k)
  for (i in 1:k){
    j  = as.integer((n-1)*pk[i] + 1)
    qnt[i] = sorted.X[j]
  }
  return(c(-Inf,qnt,Inf))
}