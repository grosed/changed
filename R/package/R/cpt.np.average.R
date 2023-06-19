
cpt.np.average <- function(X,Q,beta)
{
   
   changepoints <- cpt_np_average_impl(X,Q,beta)
   return(cpt.np.average.class(X,Q,beta,changepoints))
}