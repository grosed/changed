
cpt.np.conditional <- function(X,k,beta)
{
   changepoints <- cpt_np_conditional_impl(X,k,beta)
   return(cpt.np.conditional.class(X,k,beta,changepoints))
}