


#include <Rcpp.h>

#include "mean.h"
#include <vector>
#include <algorithm>

namespace changed
{
  namespace methods
  {
      template <typename Ftype>
      // requires std::invocable<Ftype,const int&, const int&>
      std::vector<int> pelt(const std::vector<double>& X,const double& beta)
      {
	Ftype cf(X);
	int n = X.size();
	std::vector<double> F(n+1);
	F[0] = -beta;
	std::vector<int>  cpts(n);
	std::vector<double> C(n);
	std::vector<int> R(n);
	R[0] = 0;
	int ncands = 1;
	for(int tstar = 1; tstar <= n; tstar++)
	  { 
	    std::transform(std::begin(R),std::begin(R) + ncands,std::begin(C),[&](const auto& t){return F[t] + cf(t+1,tstar) + beta;});
	    auto it = std::min_element(std::begin(C), std::begin(C) + ncands);
	    F[tstar] = *it;
	    cpts[tstar-1] = tstar - R[std::distance(std::begin(C),it)];
            int j = ncands;
	    ncands = 0;
	    for(int i = 0;i < j; i++)
	      {
		if(F[R[i]] + cf(R[i]+1,tstar) <= F[tstar] + beta)
		{
		    R[ncands++] = R[i];
		}
	      }
	    R[ncands++] = tstar;
	  }	
	return cpts;
      }
      
  } // namespace methods
} // namespace changed


std::vector<int> cpt_normal_mean_impl(const std::vector<double>& X,const double& beta)
{
    return changed::methods::pelt<changed::cost::normal::mean>(X,beta);
}


RCPP_MODULE(changed){
    using namespace Rcpp ;
    function("cpt_normal_mean_impl",&cpt_normal_mean_impl,"");
}


