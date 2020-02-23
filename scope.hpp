namespace Scope
{

template
<
  typename T
>
struct Token
{
  Token(const T& t_):Value(t_)
  {}

  template
  <
   typename TSeq_
  >
  bool block_find(const TSeq_& Seq_)
  {
  
    typename TSeq_::iterator result_ = std::find(Seq_.begin(),Seq_.end(),Value);
    return (result_!=Seq_.end());	
  }
  
  
  bool 
  block_find(const std::string& Seq_)
  {
    size_t found_ = Seq_.find(Value);
    printf("[%c]",Value);

//    if (found_!=std::string::npos)
//	printf("detected!!!\r\n");
    return (found_!=std::string::npos);
      
    }

 private:
  T Value;
 
};

typedef Token<char> Token_c;

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
 
  template
  <
   typename T
  >
  bool
  find(const T& Seq_)
    {
    
     printf("Seq_ = %s :%d:%d\r\n",Seq_.c_str(),_se.block_find(Seq_),_ss.block_find(Seq_));
     return (true);    
    }
  private:
  TScopeStart _ss;
  TScopeEnd   _se;
};

}