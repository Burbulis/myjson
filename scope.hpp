namespace Scope
{

template
<
  typename T
>
struct StartTokens
{
  StartTokens(const T& t_)
  {}

};

typedef StartTokens<char> StartTokens_c;

template
<
  typename T
>
struct EndTokens
{
  EndTokens(const T& t_)
  {}

};

typedef EndTokens<char> EndTokens_c;


template
<
  typename TScopeStart,
  typename TScopeEnd
>
struct Detector
{
 Detector(const TScopeStart& lvalue,const TScopeEnd& rvalue):
 _ss(lvalue),_se(rvalue)
 {}
 
  private:
  TScopeStart _ss;
  TScopeEnd   _se;
};

}