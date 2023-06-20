
cpt.np.max <- function(X,Q,beta)
{
   
   changepoints <- cpt_np_max_impl(X,Q,beta)
   return(cpt.np.max.class(X,Q,beta,changepoints))
}