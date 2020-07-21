#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <list>
#include <algorithm>

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
    bool ret_ = false;
    if ((larg.token_ == rarg.token_)&&(larg.count_ == rarg.count_))
    {
      ret_ = true;    
    //  printf("[%c,%zd]:[%c,%zd]\n",larg.token_,larg.count_,rarg.token_,rarg.count_);
    }
    return (ret_);
}

bool operator!=(const x_token_count& larg,const x_token_count& rarg)
{
  return (!(larg==rarg));
    
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


/*
  ++beg_;
    --end_;
    if (beg_ == end_)
      break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}
*/
template
<
  typename iter_t
>
struct iter_struct
{
    iter_struct(iter_t iter_,bool detected_):iter(iter_),detected(detected_){}
    iter_t iter ;
    bool detected;
};


template
<
  typename iter,
  typename T
>
iter
next(iter& first,iter& last,T val)
{
    
  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));
  return (first);
}



template
<
    typename T
>
typename T::iterator
 search(typename T::iterator beg_,
	typename T::iterator end_,typename T::value_type val)
{
  size_t count_ = 0;    
  iter_struct<typename T::iterator> ret_(end_,false);
  iter_struct<typename T::iterator> b_iter(beg_,false);
  iter_struct<typename T::iterator> e_iter(end_,false);
  
  while (true)
  {

    ret_ = next(b_iter,e_iter,val);
    if (ret_.detected)
      break;

    ret_ = next(b_iter,e_iter,val);
    if (ret_.detected)
      break;

    ret_ = next(b_iter,e_iter,val);
    if (ret_.detected)
      break;  

    ++count_;

  }
 // printf("count = %zd\n" , count_);
  
//  {
//      
//  }
  
  /*
  typename T::iterator ret_;
  while (true)
  {

    if (beg_ == end_)
      break;

    ++beg_;
    --end_;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}
    ++beg_;
    --end_;
    if (beg_ == end_)
      break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}

    ++beg_;
    --end_;
    if (beg_ == end_)
    break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}

    ++beg_;
    --end_;
    if (beg_ == end_)
    break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}

    ++beg_;
    --end_;
    if (beg_ == end_)
      break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}

    ++beg_;
    --end_;
    if (beg_ == end_)
    break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}
*/
    
//  }
// printf("ret_[%c::%zd]",ret_->token_,ret_->count_);
 printf("count_ = %zd",count_);
 return (ret_.iter);
}






int main ()
{
  std::list< x_token_count > xtcs;
  
  for (size_t i = 0;i<4000000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  xtcs.push_back (x_token_count ('X', 32020 ));
  for (size_t i = 0;i<2000000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  
  {
    measure ms;
    
    std::list < x_token_count >::iterator found=
      search<std::list < x_token_count > >(xtcs.begin(),xtcs.end(),x_token_count('1',32020));
      
    printf("found = [%c , %zd]\n",found->token_,found->count_);
  }
  printf("times:%f\n",measure::get_times());

  return 0;
}


#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <list>
#include <algorithm>

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
    bool ret_ = false;
    if ((larg.token_ == rarg.token_)&&(larg.count_ == rarg.count_))
    {
      ret_ = true;    
    //  printf("[%c,%zd]:[%c,%zd]\n",larg.token_,larg.count_,rarg.token_,rarg.count_);
    }
    return (ret_);
}

bool operator!=(const x_token_count& larg,const x_token_count& rarg)
{
  return (!(larg==rarg));
    
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


/*
  ++beg_;
    --end_;
    if (beg_ == end_)
      break;
    if (val == (*beg_))
    { ret_ = beg_;
      break;}
    if (val == (*end_))
    { ret_ = end_;
      break;}
*/
template
<
  typename iter_t
>
struct iter_struct
{
    iter_struct(iter_t iter_,bool detected_):iter(iter_),detected(detected_){}
    iter_t iter ;
    bool detected;
};


template
<
  typename iter,
  typename T
>
iter
next_x8(iter& first,iter& last,T val)
{
    
  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));

  ++first.iter;
    first.detected = ((first.iter == last.iter) || (*first.iter == val));


  return (first);
}



template
<
    typename T
>
typename T::iterator
 search(typename T::iterator beg_,
	typename T::iterator end_,typename T::value_type val)
{
  size_t count_ = 0;    
  iter_struct<typename T::iterator> ret_(end_,false);
  iter_struct<typename T::iterator> b_iter(beg_,false);
  iter_struct<typename T::iterator> e_iter(end_,false);
  
  while (true)
  {

    ret_ = next_x8(b_iter,e_iter,val);
    if (ret_.detected)
      break;

    ret_ = next_x8(b_iter,e_iter,val);
    if (ret_.detected)
      break;

    ret_ = next_x8(b_iter,e_iter,val);
    if (ret_.detected)
      break;  

    ret_ = next_x8(b_iter,e_iter,val);
    if (ret_.detected)
      break;  

    ret_ = next_x8(b_iter,e_iter,val);
    if (ret_.detected)
      break;  

    ret_ = next_x8(b_iter,e_iter,val);
    if (ret_.detected)
      break;  

    ++count_;

  }
 printf("count_ = %zd",count_);
 return (ret_.iter);
}


#define FIND_IF



int main ()
{
  std::list< x_token_count > xtcs;
  
  for (size_t i = 0;i<4000000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  xtcs.push_back (x_token_count ('X', 32020 ));
  for (size_t i = 0;i<4000000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
   printf("total objects = %zd",xtcs.size());
   std::list < x_token_count >::iterator found;
  {
    measure ms;
    #if defined(FIND_IF)
    found = std::find_if(xtcs.begin(),xtcs.end(),find_type<x_token_count>(x_token_count('X',32020)));
    #endif
    
    found =   search<std::list < x_token_count > >(xtcs.begin(),xtcs.end(),x_token_count('X',32020));
      
    printf("found = [%c , %zd]\n",found->token_,found->count_);
  }
  printf("times:%f\n",measure::get_times());

  return 0;
}


