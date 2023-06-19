
cpt.np.conditional <- function(X,Q,beta)
{
   
   changepoints <- cpt_np_conditional_impl(X,Q,beta)
   return(cpt.np.conditional.class(X,Q,beta,changepoints))
}