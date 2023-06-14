#include <Rcpp.h>

#include <vector>
#include <list>
#include <memory>

#include "normal.mean.h"
#include "np.conditional.h"
#include "op.pruned.h"

std::vector<int> cpt_normal_mean_impl(const std::vector<double>& X,const double& beta)
{
  changed::cost::normal::mean cf(X);
  return changed::methods::op_pruned(cf,beta,X.size());
}


std::vector<int> cpt_np_conditional_impl(const std::vector<double>& X,
					 const double& k,
					 const double& beta)
{
  changed::cost::np::conditional cf(X,k);
  return changed::methods::op_pruned(cf,beta,X.size());
}


struct normal_mean
{
  std::shared_ptr<changed::cost::normal::mean> sp_cf;
  normal_mean();
  void set(const std::vector<double>&);
  std::vector<double> costs(const std::list<std::vector<int> >&) const;
};


normal_mean::normal_mean() {}

void normal_mean::set(const std::vector<double>& X)
{
  sp_cf = std::shared_ptr<changed::cost::normal::mean>(new changed::cost::normal::mean(X));
}

std::vector<double> normal_mean::costs(const std::list<std::vector<int> >& IJ) const
{
  std::vector<double> result(IJ.size());
  int idx = 0;
  for(const auto& ij : IJ)
    {
      result[idx++] = (*sp_cf)(ij[0],ij[1]);      
    }
  return result;
}

struct np_conditional
{
  std::shared_ptr<changed::cost::np::conditional> sp_cf;
  np_conditional();
  void set(const std::vector<double>&,const double&);
  std::vector<double> costs(const std::list<std::vector<int> >&) const;
};


np_conditional::np_conditional() {}

void np_conditional::set(const std::vector<double>& X, const double& k)
{
  sp_cf = std::shared_ptr<changed::cost::np::conditional>(new changed::cost::np::conditional(X,k));
}

std::vector<double> np_conditional::costs(const std::list<std::vector<int> >& IJ) const
{
  std::vector<double> result(IJ.size());
  int idx = 0;
  for(const auto& ij : IJ)
    {
      result[idx++] = (*sp_cf)(ij[0],ij[1]);      
    }
  return result;
}




RCPP_MODULE(changed){
    using namespace Rcpp;
    function("cpt_normal_mean_impl",&cpt_normal_mean_impl,"");
    function("cpt_np_conditional_impl",&cpt_np_conditional_impl,"");
    class_<normal_mean>("normal_mean")
      .constructor()
      .method("costs", &normal_mean::costs , "get costs")
      .method("set", &normal_mean::set , "set data")
    ;
    class_<np_conditional>("np_conditional")
      .constructor()
      .method("costs", &np_conditional::costs , "get costs")
      .method("set", &np_conditional::set , "set data")
    ;
}
 

