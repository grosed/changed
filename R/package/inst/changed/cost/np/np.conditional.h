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
	  std::vector<std::vector<Rtype> > S;
	  conditional_template(const std::vector<Ctype>&, const Ctype&);
	  Ctype operator()(const Rtype&,const Rtype&) const;

	  std::vector<Ctype> sumstats(const Rtype&,const Rtype&) const;
	  
	};
      
      template <typename Rtype,typename Ctype>
	conditional_template<Rtype,Ctype>::conditional_template(const std::vector<Ctype>& X, const Ctype& k)
	{
	  // sort the data
	  auto n = X.size();
	  auto XS = X;
	  std::sort(std::begin(XS),std::end(XS));
	  std::vector<Rtype> I(k);
	  auto c = std::log(2*n-1);
	  for(int i = 0; i < k; i++)
	    {
	      auto yk = (-1+2*(i+1)/k-1/k);
	      auto pk = std::pow(1 + std::exp(c*yk),-1);
	      auto Ik = (Rtype)((n-1)*pk + 1);
	      I[k-i-1] = Ik;
	    }
	  // calculate quantiles
	  std::vector<Ctype> Q(k+2);
	  auto infinity = std::numeric_limits<Ctype>::infinity();
	  Q[0] = -infinity;
	  Q[k+1] = infinity;
	  std::transform(std::begin(I),std::end(I),std::begin(Q) + 1,[&XS](const auto& i){return XS[i-1];});
	  S = std::vector<std::vector<Rtype> >(n+1);
	  S[0] = std::vector<Rtype>(Q.size()-1,0);	  
	  // indicate
	  for(int i = 1; i <= n; i++)
	    {
	      S[i] = std::vector<Rtype>(Q.size()-1);
	      std::transform(std::begin(Q) + 1,std::end(Q),std::begin(Q),std::begin(S[i]),
			     [&X,&i](const auto& b,const auto& a)
			     {
			       return 1 ? a < X[i-1] && X[i-1] <= b : 0;
			     }
			     );
	    }
	  // accumalate 
	  for(int i = 0; i < n; i++)
	    {
	      for(int j = 0; j < Q.size()-1; j++)
		{
		  S[i+1][j] += S[i][j]; 
		}
	    }	  
	}

      
      template <typename Rtype,typename Ctype>
	Ctype conditional_template<Rtype,Ctype>::operator()(const Rtype& i,const Rtype& j) const
	{
	  
	  Ctype t = (Ctype)(j - i + 1);
	  std::vector<Ctype> M(S[0].size());
	  std::transform(std::begin(S[j]),std::end(S[j]),std::begin(S[i-1]),std::begin(M),
			 [&t](const auto& a, const auto& b)
			 {
			   auto m = a - b;
			   double val;
			   if(m == 0 || m == t)
			     {
			       val =  0.0;
			     }
			   else
			     {
			       val = -m*std::log(m/t);
			     }
			   return val;
			 }
			 );
	  auto val = std::accumulate(M.begin(),M.end(),0.0);
	  return val;
	}      
      typedef conditional_template<int,double> conditional;
    } // namespace normal
  } // namespace cost
} // namespace changed



#endif
