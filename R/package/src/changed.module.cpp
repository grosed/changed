#include <Rcpp.h>

#include <vector>

#include "normal.mean.h"
#include "op.pruned.h"

std::vector<int> cpt_normal_mean_impl(const std::vector<double>& X,const double& beta)
{
    return changed::methods::op_pruned<changed::cost::normal::mean>(X,beta);
}


RCPP_MODULE(changed){
    using namespace Rcpp;
    function("cpt_normal_mean_impl",&cpt_normal_mean_impl,"");
}


