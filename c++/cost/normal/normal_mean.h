#ifndef ___NORMAL_MEAN_H___
#define ___NORMAL_MEAN_H___

#include <vector>

namespace changed
{

  namespace cost
  {
  
    namespace normal
    {
  
      template <typename Ctype>
	struct sumstats
	{
	  std::vector<Ctype> SX;
	  std::vector<Ctype> SXX;
	  sumstats(const std::vector<Ctype>&);
	  std::vector<Ctype> getSX() const;
	  std::vector<Ctype> getSXX() const;
	};
      
      template <typename Ctype>
	sumstats<Ctype>::sumstats(const std::vector<Ctype>& X)
	{
	  SX = std::vector<Ctype>(X.size()+1,0.0);
	  SXX = std::vector<Ctype>(X.size()+1,0.0);
	  std::transform(X.begin(),X.end(),SX.begin()+1,[](const auto& x){return x;});
	  std::partial_sum(SX.begin(), SX.end(),SX.begin());
	  std::transform(X.begin(),X.end(),SXX.begin()+1,[](const auto& x){return x*x;});
	  std::partial_sum(SXX.begin(), SXX.end(),SXX.begin());
	}
      
      template <typename Ctype>
	std::vector<Ctype> sumstats<Ctype>::getSX() const
	{
	  return SX;
	}
      
      template <typename Ctype>
	std::vector<Ctype> sumstats<Ctype>::getSXX() const
	{
	  return SXX;
	}
      
      template <typename Rtype,typename Ctype>
	struct normal_mean
	{
	  sumstats<Ctype> S;  
	  normal_mean(const std::vector<Ctype>&);
	  Ctype operator()(const Rtype&,const Rtype&);
	};
      
      
      template <typename Rtype,typename Ctype>
	normal_mean<Rtype,Ctype>::normal_mean(const std::vector<Ctype>& X) : S(X) {}
      
      template <typename Rtype,typename Ctype>
	Ctype normal_mean<Rtype,Ctype>::operator()(const Rtype& i,const Rtype& j)
	{
	  Ctype val = S.SX[j+1] - S.SX[i];
	  val *= val;
	  val /= (j - i + 1);
	  val = -val;
	  val += S.SXX[j+1] - S.SXX[i];
	  return val;
	}
    } // namespace normal
  } // namespace cost
} // namespace changed



#endif
