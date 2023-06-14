#ifndef ___NP_CONDITIONAL_H___
#define ___NP_CONDITIONAL_H___

#include <vector>

namespace changed
{
  namespace cost
  { 
    namespace np
    {      
      template <typename Rtype,typename Ctype>
	struct conditional_template
	{
	  Ctype Q;
	  Ctype K;
	  conditional_template(const std::vector<Ctype>&, const Ctype&, const Ctype&);
	  Ctype operator()(const Rtype&,const Rtype&) const;
	};
      
      template <typename Rtype,typename Ctype>
	conditional_template<Rtype,Ctype>::conditional_template(const std::vector<Ctype>& X,
								const Ctype& _Q,
								const Ctype& _K) : Q(_Q), K(_K) {}
      
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
