#include <iostream>
#include <assert.h>
#define REF_PARM(T , INDEX) TYPE_TESTER<T,INDEX>::result_


using namespace std;

enum
{FLOAT=555444555,SIZE_T,UNSIGNED_INT,UNSIGNED_CHAR,INT,CHAR,UNSIGNED_LONG,LONG};


template
< 
typename T
>
struct DetectType
{
  enum{TYPE = 5050505};     
};

template<>
struct DetectType<char>
{
  enum{TYPE = CHAR};     
};

template<>
struct DetectType<long>
{
  enum{TYPE = LONG};     
};


template<>
struct DetectType<unsigned char>
{
  enum{TYPE = UNSIGNED_CHAR};     
};


template<>
struct DetectType<int>
{
  enum{TYPE = INT};     
};

template<>
struct DetectType<float>
{
  enum{TYPE = FLOAT};     
};


template<>
struct DetectType<size_t>
{
  enum{TYPE = SIZE_T};     
};

template<>
struct DetectType<unsigned int>
{
  enum{TYPE = UNSIGNED_INT};     
};

template
<
  typename T,
  int t_detector
>
struct
TYPE_TESTER
{
  static bool result_;
};

template
<
  typename T,
  int t_detector
>
bool TYPE_TESTER<T,t_detector>::result_ = (DetectType<T>::TYPE == t_detector);

template
<
int idx,
typename T
>
void REFERENCE_PARM(T test)
{
 TYPE_TESTER<T,idx>::result_ = (DetectType<T>::TYPE == idx);
 printf("%d::%d\n",DetectType<T>::TYPE,idx);
 printf("res:%d\n",TYPE_TESTER<T,idx>::result_);
 assert( ( TYPE_TESTER<T,idx>::result_ ) );
  // assert( (REF_PARM( T , INDEX )) );
 // {
//    printf("Type Error!!!");
 // }
}

void test(unsigned char x,int y,float z)
{

  REFERENCE_PARM<UNSIGNED_CHAR>( x );
  REFERENCE_PARM<INT>( y );
  REFERENCE_PARM<FLOAT>( z );
  
 // ParamTest<FLOAT>( x );

}


int main()
{
  test(1,2,3);
  
    return 0;
}