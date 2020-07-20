#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct x_token_count
{
    x_token_count(){}
  x_token_count (char token, size_t count)
  :token_ (token), count_ (count){}
  
  
  friend bool operator==(const x_token_count& larg,const x_token_count& rarg);
  
  char token_;
  size_t count_;
};

bool operator==(const x_token_count& larg,const x_token_count& rarg)
{
   // bool ret_ = false;
    return ((larg.token_ == rarg.token_)&&(larg.count_ == rarg.count_));
    //{
    //  ret_ = true;    
   //   printf("[%c,%zd]:[%c,%zd]\n",larg.token_,larg.count_,rarg.token_,rarg.count_);
   // }
   // return (ret_);
}

template
<
  typename T
>
struct find_type:public std::unary_function
< T , bool >
{
    find_type(const T& t_):_t(t_)
    {}

    bool operator()(const T& obj)
    {
      return(_t == obj) ; 
    }
    T _t;
};

struct measure
{
    measure():start(clock()){}
    
    ~measure()
    {
      end = clock();
      times = (double)(end - start);
    }
    
    static 
    double
    get_times(void)
    { return (times); }
    
    clock_t end;
    clock_t start;
    static double times;
};
double measure::times;



/*template
<
  typename iterator_type,
  typename T
>
next(iterator_type& first,iterator_type &last,T &var)
*/


template
<
    typename T
>
typename T::iterator
 search(typename T::iterator beg_,
	typename T::iterator end_,typename T::value_type val,const size_t sz)
{
  //size_t count_ = 0;
  typename T::iterator ret(end_);
  // printf("size_= %zd",sz);
  const size_t end_of_iteration = ((sz/2) + sz%2);
  for (size_t i = 0;i < end_of_iteration ;++beg_,--end_,++i)
  {
    if (*beg_ == val) 
    {
     ret = beg_;
     break;
    }
    if (*end_ == val)
    {
     ret = end_;
     break;
    }
  }

// printf("ret_[%c::%zd]",val.token_,val.count_);
// printf("count_ = %zd",count_);
 return (ret);
}






int main ()
{
  std::list< x_token_count > xtcs;
  for (size_t i = 0;i<40000000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  xtcs.push_back (x_token_count ('X', 32020 ));
  for (size_t i = 0;i<40000000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  {
    measure ms;
    
    std::list < x_token_count >::iterator found = //std::find_if(xtcs.begin(),xtcs.end(),find_type<x_token_count>(x_token_count ('X', 32020 )));
      search<std::list < x_token_count > >(xtcs.begin(),xtcs.end(),x_token_count('X',32020),xtcs.size());
      
    printf("found = [%c , %zd]\n",found->token_,found->count_);
  }
  printf("times:%f\n",measure::get_times());

  return 0;
}