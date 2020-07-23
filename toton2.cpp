#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <exception>

struct x_token_count
{
    x_token_count(){}
  x_token_count (char token, size_t count)
  :token_ (token), count_ (count){}
  
  
  friend bool operator==(const x_token_count& larg,const x_token_count& rarg);
  friend bool operator!=(const x_token_count& larg,const x_token_count& rarg);
  char token_;
  size_t count_;
};

bool operator==(const x_token_count& larg,const x_token_count& rarg)
{
    return ((larg.token_ == rarg.token_)&&(larg.count_ == rarg.count_));
}

bool operator!=(const x_token_count& larg,const x_token_count& rarg)
{
  return(!(larg == rarg));
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

class next_6_exception
: public std::exception
{
};




template
<
  typename iterator_type,
  typename T
>
bool
next_x8(iterator_type& first,const iterator_type &last,const T& value,iterator_type &out)
{
   bool detect = false;  

   if (!detect) ++first;
   out = first;
   detect = ((out == last)||(*first == value)); 

   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 
 
   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 

   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 

   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 

   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 

   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 

   if (!detect) ++first;
   out = first;
   detect = ((detect)||(out == last)||(*first == value)); 

   return (detect);   
 }

template
<
    typename T
>
typename T::iterator
 search(typename T::iterator beg_,
	typename T::iterator end_,typename T::value_type val,const size_t sz)
{
  size_t count_ = 0;
  typename T::iterator ret(end_);

  while (true) 
  {

     if (next_x8(beg_,end_,val,ret))
     {
        break;
     }

     if (next_x8(beg_,end_,val,ret))
     {
        break;
     }

  //   ++count_;  
 
  }

 return (ret);
}




const size_t counter_ = 10000000;

//#define FIND_IF 1

int main ()
{
  std::list< x_token_count > xtcs;
  for (size_t i = 0;i<counter_;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  xtcs.push_back (x_token_count ('X', 32020 ));
  for (size_t i = 0;i<counter_;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }

  printf("total objects = %zd",xtcs.size());
  std::list < x_token_count >::iterator found = xtcs.end();
  {
    measure ms;
    #ifdef FIND_IF
      found = std::find_if(xtcs.begin(),xtcs.end(),find_type<x_token_count>(x_token_count ('z', 32020 )));
    #else
      found = search< std::list< x_token_count > >(xtcs.begin(),xtcs.end(),x_token_count('z',32020),xtcs.size());
    #endif
  }
 
  if (found!=xtcs.end())
  {
    printf("detected!\n");
    printf("found = [%c , %zd]\n",found->token_,found->count_);
  }
  else
  {
    printf("\n\nnot detected!\n\n");
  }
  printf("times:%f\n",measure::get_times());
 
  return 0;
}
