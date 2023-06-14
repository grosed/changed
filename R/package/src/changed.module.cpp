#include <Rcpp.h>

#include <vector>

#include "normal.mean.h"
#include "np.conditional.h"
#include "op.pruned.h"

std::vector<int> cpt_normal_mean_impl(const std::vector<double>& X,const double& beta)
{
  changed::cost::normal::mean cf(X);
  return changed::methods::op_pruned(cf,beta,X.size());
}


std::vector<int> cpt_np_conditional_impl(const std::vector<double>& X,
					 const double& Q,
					 const double& K,
					 const double& beta)
{
  changed::cost::np::conditional cf(X,Q,K);
  return changed::methods::op_pruned(cf,beta,X.size());
}


RCPP_MODULE(changed){
    using namespace Rcpp;
    function("cpt_normal_mean_impl",&cpt_normal_mean_impl,"");
    function("cpt_np_conditional_impl",&cpt_np_conditional_impl,"");
}


