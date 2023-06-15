
cpt.normal.mean <- function(X,beta)
{
   changepoints <- cpt_normal_mean_impl(X,beta)
   return(cpt.normal.mean.class(X,beta,changepoints))
}