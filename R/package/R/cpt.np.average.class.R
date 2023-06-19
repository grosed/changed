.cpt.np.average.class<-setClass("cpt.np.average.class",representation(X="numeric",
						                      beta="numeric",
						                      Q="numeric",
						                      changepoints="numeric"))

cpt.np.average.class<-function(X,Q,beta,changepoints)
{
    .cpt.np.average.class(X=X,
			  Q=Q,
	                  beta=beta,
	                  changepoints=changepoints)
}


if(!isGeneric("changepoints")) {setGeneric("changepoints",function(object) {standardGeneric("changepoints")})}
#setGeneric("changepoints",function(object) {standardGeneric("changepoints")})
setMethod("changepoints",signature=list("cpt.np.average.class"),
          function(object)
          {
	    res <- c()
            idx <- length(object@changepoints)
            while(idx - object@changepoints[idx] > 0)
            {
              res <- c(res,idx - object@changepoints[idx])
              idx <- idx - object@changepoints[idx]
            }
	    res <- c(0,rev(res),length(object@X))
	    np <- new(np_average)
	    np$set(object@X,object@Q)
	    costs <- c()
	    for(idx in 1:(length(res)-1))
	    {
	      costs <- c(costs,np$cost(res[idx]+1,res[idx+1]))
	    }
	   
	    df <- data.frame("start"=res[1:(length(res)-1)]+1,"end"=res[2:length(res)],"cost"=costs)
	    return(df)
          })	      