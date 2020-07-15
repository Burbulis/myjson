#include <iostream>
#include <assert.h>
#define REF_PARM(T , INDEX) TYPE_TESTER<T,INDEX>::result_


using namespace std;

enum
{FLOAT,SIZE_T,UNSIGNED_INT,UNSIGNED_CHAR,INT,CHAR,UNSIGNED_LONG,LONG};


template
< 
typename T
>
struct DetectType
{
  enum{TYPE = LONG};     
};

template<>
struct DetectType<char>
{
  enum{TYPE = CHAR};     
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
int INDEX,
typename T
>
void ParamTest(T test)
{
  assert(( TYPE_TESTER<T,INDEX>::result_ = (DetectType<T>::TYPE == INDEX) ));
  // assert( (REF_PARM( T , INDEX )) );
 // {
//    printf("Type Error!!!");
 // }
}

void test(unsigned char x,int y,float z)
{
  ParamTest<UNSIGNED_CHAR>( z );
}


int main()
{
  test(1,2,3);
  
    return 0;
}