#ifndef ___SPLIT_H___
#define ___SPLIT_H___

#include <set>
#include <list>
#include <ranges>
#include <algorithm>
#include <concepts>
#include <tuple>


namespace changed
{
  namespace core
  {
    template <typename Ftype,
      typename Rtype,
      typename Ctype = typename std::result_of<Ftype(const Rtype&,const Rtype&)>::type>
      requires std::invocable<Ftype,const Rtype&, const Rtype&> 
      auto split(Ftype f, Ftype g, std::set<Rtype> R)
      {
	auto a = *std::min_element(R.begin(),R.end());
	auto d = *std::max_element(R.begin(),R.end());
	std::list<std::tuple<Rtype,Ctype> > locations;
	std::ranges::transform(std::ranges::take_view(R,R.size()-1),
			       std::ranges::drop_view(R,1),
			       std::back_inserter(locations),
			       [&a,&d,&f,&g](const auto& b,const auto& c)
			       {
				 return std::make_tuple(c,f(a,b) + g(c,d)); 
			       });
	locations.push_back(std::make_tuple(a,g(a,d)));
	return *std::min_element(locations.begin(),
				 locations.end(),
				 [](const auto &a, const auto &b)
				 {
				   return std::get<1>(a) < std::get<1>(b);
				 });
      }
  } // namespace core
} // namespace changed

#endif
