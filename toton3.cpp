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


template
<
    typename T
>
typename T::iterator
 search(typename T::iterator beg_,
	typename T::iterator end_,typename T::value_type value,const size_t sz)
{
  size_t count_ = 0;
  typename T::iterator first(beg_);
  typename T::iterator  last(end_);
  typename T::iterator ret(end_);
  static bool detect = 0; 
 
  do
  {
 //1
   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));
 
   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));

   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));
 
   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));

   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));
 
   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));

   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));
 
   ret = first;
   detect = static_cast<unsigned int>(((ret == last)||(*first == value))); 
   std::advance(first,static_cast<unsigned int>(!detect));


 //2
/*   ret = first;
   detect = ((detect!=0)||(ret == last)||(*first == value)); 
   count_ += (!detect);
//3   
   if (!detect) ++first;
   ret = first;
   detect = ((detect)||(ret == last)||(*first == value)); 
   count_ += (!detect);
//4
   if (!detect) ++first;
   ret = first;
   detect = ((detect)||(ret == last)||(*first == value)); 
   count_ += (!detect);
//5
   if (!detect) ++first;
   ret = first;
   detect = ((detect)||(ret == last)||(*first == value)); 
   count_ += (!detect);
//6   
   if (!detect) ++first;
   ret = first;
   detect = ((detect)||(ret == last)||(*first == value)); 
   count_ += (!detect);
//7
   if (!detect) ++first;
   ret = first;
   detect = ((detect)||(ret == last)||(*first == value)); 
   count_ += (!detect);
//8
   if (!detect) ++first;
   ret = first;
   detect = ((detect)||(ret == last)||(*first == value)); 
   count_ += (!detect);
   
   if (!detect) ++first;*/
   count_ += (!detect);
  }
  while (( count_ < sz ) && (!detect));
  printf("count_=%zd\n\n",count_);
 
  return (ret);
}




const size_t counter_ = 50000000;

const char find_obj = 'z';
//#define FIND_IF 1

//no_find_if 1325446
//           1539518
//           1028040
//            971844
//            958274
//find_if     963310

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
      found = std::find_if(xtcs.begin(),xtcs.end(),find_type<x_token_count>(x_token_count (find_obj, 32020 )));
    #else
      found = search< std::list< x_token_count > >(xtcs.begin(),xtcs.end(),x_token_count(find_obj,32020),xtcs.size());
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