#ifndef ___NP_CONDITIONAL_H___
#define ___NP_CONDITIONAL_H___

#include <vector>
#include <cmath>
#include <limits>

namespace changed
{
  namespace cost
  { 
    namespace np
    {      
      template <typename Rtype,typename Ctype>
	struct conditional_template
	{
	  conditional_template(const std::vector<Ctype>&, const Ctype&);
	  Ctype operator()(const Rtype&,const Rtype&) const;
	};
      
      template <typename Rtype,typename Ctype>
	conditional_template<Rtype,Ctype>::conditional_template(const std::vector<Ctype>& X, const Ctype& k)
	{
	  // sot the data
	  auto n = X.size();
	  auto XS = X;
	  std::sort(std::begin(XS),std::end(XS));
	  std::vector<int> I(k);
	  auto c = -2.0*std::log(2*n-1);
	  for(int i = 0; i < k; i++)
	    {
	      I[k] = (int)((n-1)*std::pow(1 + std::exp(c*(-1+2*(i+1)/k-1/k)),-1));
	    }
	  std::vector<Ctype> Q(k+2);
	  auto infinity = std::numeric_limits<Ctype>::infinity();
	  Q[0] = -infinity;
	  Q[k+1] = infinity;
	  std::transform(std::begin(I),std::end(I),std::begin(Q) + 1,[&XS](const auto& i){return XS[i];});
	}
      
      
      template <typename Rtype,typename Ctype>
	Ctype conditional_template<Rtype,Ctype>::operator()(const Rtype& i,const Rtype& j) const
	{
	  Ctype val = 3.14; // TEMP
	  return val;
	}
      typedef conditional_template<int,double> conditional;
    } // namespace normal
  } // namespace cost
} // namespace changed



#endif
