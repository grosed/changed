#include <Rcpp.h>

#include <vector>
#include <list>
#include <memory>
#include <thread>
#include <chrono>
#include <future>


#include "normal.mean.h"
#include "np.conditional.h"
#include "np.average.h"
#include "np.max.h"
#include "op.pruned.h"


template <typename Ftype, typename... Args>
std::vector<int> run_method(Ftype& f,Args... args)
{
  // Create a std::promise object
  std::promise<void> exitSignal;
  // fetch std::future object associated with promise
  std::shared_future<void> futureObj = exitSignal.get_future();
  // start worker thread
  auto future = std::async(std::launch::async,f,args...,std::move(futureObj));
  // check for user interrupt and lack of resources and rethrow to R if necessary 
  try
    {
      while(std::future_status::ready != future.wait_for(std::chrono::milliseconds(0)))
	{
	  Rcpp::checkUserInterrupt();
	}
    }  
  catch(std::bad_alloc &e)
    {
      exitSignal.set_value();
      auto result = future.get(); // wait for it to tidy up
      Rcpp::stop("insufficient memory");
    }
  catch(...)
    {
      exitSignal.set_value();
      auto result = future.get(); // wait for it to tidy up
      Rcpp::stop("user interrupt");
    }
  // return the result
  return future.get();
}


std::vector<int> cpt_normal_mean_impl(const std::vector<double>& X,const double& beta)
{
  changed::cost::normal::mean cf(X);
  return run_method(changed::methods::op_pruned<changed::cost::normal::mean>,cf,beta,X.size());
}


std::vector<int> cpt_np_conditional_impl(const std::vector<double>& X,
					 const std::vector<double>& Q,
					 const double& beta)
{
  changed::cost::np::conditional cf(X,Q);
  return run_method(changed::methods::op_pruned<changed::cost::np::conditional>,cf,beta,X.size());
}

std::vector<int> cpt_np_average_impl(const std::vector<double>& X,
				     const std::vector<double>& Q,
				     const double& beta)
{
  changed::cost::np::average cf(X,Q);
  return run_method(changed::methods::op_pruned<changed::cost::np::average>,cf,beta,X.size());
}

std::vector<int> cpt_np_max_impl(const std::vector<double>& X,
				     const std::vector<double>& Q,
				     const double& beta)
{
  changed::cost::np::max cf(X,Q);
  return run_method(changed::methods::op_pruned<changed::cost::np::max>,cf,beta,X.size());
}


struct normal_mean
{
  std::shared_ptr<changed::cost::normal::mean> sp_cf;
  normal_mean();
  void set(const std::vector<double>&);
  double cost(const int&, const int&) const;
};


normal_mean::normal_mean() {}

void normal_mean::set(const std::vector<double>& X)
{
  sp_cf = std::shared_ptr<changed::cost::normal::mean>(new changed::cost::normal::mean(X));
}

double normal_mean::cost(const int& i,const int& j) const
{
  return (*sp_cf)(i,j);      
}

struct np_conditional
{
  std::shared_ptr<changed::cost::np::conditional> sp_cf;
  np_conditional();
  void set(const std::vector<double>&,const std::vector<double>&);
  double cost(const int&, const int&) const; 
};


np_conditional::np_conditional() {}

void np_conditional::set(const std::vector<double>& X, const std::vector<double>& Q)
{
  sp_cf = std::shared_ptr<changed::cost::np::conditional>(new changed::cost::np::conditional(X,Q));
}

double np_conditional::cost(const int& i, const int& j) const
{
  return (*sp_cf)(i,j);
}


struct np_average
{
  std::shared_ptr<changed::cost::np::average> sp_cf;
  np_average();
  void set(const std::vector<double>&,const std::vector<double>&);
  double cost(const int&, const int&) const; 
};


np_average::np_average() {}

void np_average::set(const std::vector<double>& X, const std::vector<double>& Q)
{
  sp_cf = std::shared_ptr<changed::cost::np::average>(new changed::cost::np::average(X,Q));
}

double np_average::cost(const int& i, const int& j) const
{
  return (*sp_cf)(i,j);
}



struct np_max
{
  std::shared_ptr<changed::cost::np::max> sp_cf;
  np_max();
  void set(const std::vector<double>&,const std::vector<double>&);
  double cost(const int&, const int&) const; 
};


np_max::np_max() {}

void np_max::set(const std::vector<double>& X, const std::vector<double>& Q)
{
  sp_cf = std::shared_ptr<changed::cost::np::max>(new changed::cost::np::max(X,Q));
}

double np_max::cost(const int& i, const int& j) const
{
  return (*sp_cf)(i,j);
}


RCPP_MODULE(changed){
    using namespace Rcpp;
    function("cpt_normal_mean_impl",&cpt_normal_mean_impl,"");
    function("cpt_np_conditional_impl",&cpt_np_conditional_impl,"");
    function("cpt_np_average_impl",&cpt_np_average_impl,"");
    function("cpt_np_max_impl",&cpt_np_max_impl,"");
    class_<normal_mean>("normal_mean")
      .constructor()
      .method("cost", &normal_mean::cost , "get cost")
      .method("set", &normal_mean::set , "set data")
    ;
    class_<np_conditional>("np_conditional")
      .constructor()
      .method("cost", &np_conditional::cost , "get cost")
      .method("set", &np_conditional::set , "set data")
    ;
    class_<np_average>("np_average")
      .constructor()
      .method("cost", &np_average::cost , "get cost")
      .method("set", &np_average::set , "set data")
      ;
    class_<np_max>("np_max")
      .constructor()
      .method("cost", &np_max::cost , "get cost")
      .method("set", &np_max::set , "set data")
      ;
}
 

