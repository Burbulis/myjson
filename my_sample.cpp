#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct x_token_count
{
  x_token_count (char token, size_t count)
  :token_ (token), count_ (count){}
  
  
  friend bool operator==(const x_token_count& larg,const x_token_count& rarg);
  
  char token_;
  size_t count_;
};

bool operator==(const x_token_count& larg,const x_token_count& rarg)
{
    bool ret_ = false;
    if ((larg.token_ == rarg.token_)&&(larg.count_ == rarg.count_))
    {
      ret_ = true;    
      printf("[%c,%zd]:[%c,%zd]\n",larg.token_,larg.count_,rarg.token_,rarg.count_);
    }
    return (ret_);
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
void our_find_if(typename T::iterator beg_,
	typename T::iterator end_,typename T::value_type val)
{
  while (true)
  {
    if (beg_ == end_)
      break;
    
   /* if (*beg_ == val)
    {
     printf("%c:%zd\n",beg_->token_,beg_->count_);
     break;
        
    }
    
    if (*end_ == val) 
    {
     printf("%c:%zd\n",beg_->token_,beg_->count_);
    break;
        
    }*/
    
    ++beg_;
    --end_;
  }

}



int main ()
{
  std::list< x_token_count > xtcs;
  for (size_t i = 0;i<100000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  xtcs.push_back (x_token_count ('8', 1020));
  for (size_t i = 0;i<100000;++i)
  {
    xtcs.push_back (x_token_count ('"', i));
  }
  {
    measure ms;
    //std::vector < x_token_count >::iterator find =
    //  std::find_if(xtcs.begin(),xtcs.end(),
    //     find_type<x_token_count>());
    //if ( find!=xtcs.end() )
    our_find_if<std::list < x_token_count > >(xtcs.begin(),xtcs.end(),x_token_count('8',1020));
   // printf("found = [%c , %zd]\n",find->token_,find->count_);
  }
  printf("times:%f\n",measure::get_times());

  return 0;
}
