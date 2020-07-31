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
 u_search(typename T::iterator first,
	typename T::iterator last,typename T::value_type value,const size_t sz)
{

  typename T::iterator ret(last);
 
  do
  {
   ++first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;
   ret = ((ret != last)&&(*first != value))?(++first):first;


  }
  while ((ret != last)&&(*first != value));
  return (ret);
}


template
<
typename T
>
 typename std::vector<T>::iterator
 u_search(std::vector<T>& buffer,const T& value,const size_t obj_sz)
{
  size_t count = 0;
  size_t index_ = 0;
 
  const size_t sz_ = buffer.size(); 
  float P_A = static_cast<float>(obj_sz) / static_cast<float>(sz_);
  printf("obj_sz = %zd , P_A = %f\n\n" ,obj_sz ,  P_A);

  typename std::vector<T>::iterator ret = buffer.begin();
  const T *x_buffer = reinterpret_cast<const T *>(&buffer[0]);
  size_t obj_detected = 0;
  do
  {

    ++count;   

    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;

    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(x_buffer[count] != value))?(++count):count;
    printf("obj_detected(%c,%d)\n",buffer[count].token_,buffer[count].count_);
    obj_detected += (buffer[count].token_ == value.token_);
    printf("obj_detected = %zd",obj_detected);
    float P_A = static_cast<float>(obj_sz - obj_detected) / static_cast<float>(sz_);
    printf (" ==P_A = %f , %zd\n\n",P_A,obj_detected);

  }
  while ((count < sz_)/*&&(x_buffer[count] != value)*/);

  std::advance(ret,index_);

  return (ret);
}





template
<
typename T
>
 void
 u_search(T *buffer,const T& value,const size_t sz_,const size_t obj_sz)
{
  size_t count = 0;
  size_t index_ = 0;

 // const size_t sz_ = buffer.size(); 
 // const T *x_buffer = reinterpret_cast<const T *>(&buffer[0]);
  do
  {
    ++count;   
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;

    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
    index_ = ((count < sz_)&&(buffer[count] != value))?(++count):count;
  }
  while ((count < sz_)&&(buffer[count] != value));



  return ;
}






const size_t counter_ = 20;


const char find_obj = '"';
//#define FIND_IF 1

//no_find_if 1325446
//           1539518
//           1028040
//            971844
//            958274
//find_if     963310
typedef std::vector<x_token_count> type_seq;

int main ()
{
  type_seq xtcs;
  srand (time(NULL));
  size_t total_ = 0;
  x_token_count *test = new x_token_count[counter_];
  for (size_t i = 0 ; i < counter_ ;++i)
  {
    int iSecret = rand() % 45 + 1;
    
    if (iSecret < ( '"' + ( i%35 ) ) )
    {
      test[i] = x_token_count ( '"', i);
      ++total_;
    }
    else
    {
      printf("iSecret = %d\n",iSecret);
      test[i] = x_token_count ( find_obj, i);  
    }

    
      
  }
  xtcs.insert(xtcs.end(),test,test+counter_);
  delete [] test;

  test = new x_token_count[counter_];

  for (size_t i = 0 ; i < counter_  ; ++i)
  {
    int iSecret = rand() % 55 + 1;
    
    if (iSecret < ( '"' + ( i%35 ) ) )
    {
      test[i] = x_token_count ( '"', i);
      ++total_;
    }
    else
    {
      printf("iSecret = %d\n",iSecret);
      test[i] = x_token_count ( find_obj, i);  
    }
  }
  
  xtcs.insert(xtcs.end(),test,test+counter_);
  delete [] test;
  printf("total_ = %zd\n",total_);
  
  printf("total objects = %zd",xtcs.size());
  type_seq::iterator found = xtcs.end();
  {
    measure ms;
    #ifdef FIND_IF
      found = std::find_if(xtcs.begin(),xtcs.end(),find_type<x_token_count>(x_token_count (find_obj, 32020 )));
    #else
     // found = u_search< type_seq >(xtcs.begin(),xtcs.end(),x_token_count(find_obj,32020),xtcs.size());
      u_search<x_token_count>( xtcs , x_token_count(find_obj, 32020 ), xtcs.size() - total_ );
    #endif
  }
 /*
  if (found!=xtcs.end())
  {
    printf("detected!\n");
    printf("found = [%c , %zd]\n",found->token_,found->count_);
  }
  else
  {
    printf("\n\nnot detected!\n\n");
  }*/
  printf("times:%f\n",measure::get_times());
 
  return 0;
}
