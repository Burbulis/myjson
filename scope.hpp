#include <memory>
#include <vector>
#include <map>
namespace Scope
{

struct json_struct
{
  json_struct(std::string Str_):Value_s(Str_)
  {}
  json_struct(long long Digit_):Value_l(Digit_)
  {}
  json_struct()
  {}
  std::string Value_s;
  long long Value_l;
};

template
<
  typename T
>
struct Token
{
  Token(const T& t_):Value(t_),pos_(0)
  {}

 void
 set(size_t start_,size_t count_)
 {
   start_pos = start_;
   count = count_;
 }

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
    pos_ = Seq_.find(Value);
    printf("[%c]",Value);

    return (pos_!=std::string::npos);
      
    }
  
    size_t get_pos(void)const{
 //   	printf("pos_ = %d",static_cast<int>(pos_));
		return (pos_);    
    }
    

 private:
  size_t start_pos;
  size_t count;
  size_t pos_;
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
  size_t
  find(const T& Seq_)
  {
    
    size_t end_block   = _se.block_find(Seq_);
    size_t start_block = _ss.block_find(Seq_);
    bool any_block = (end_block || start_block);
   // if (start_block)
   // {
   //  );
   // }
     //result = 
   //  s_jblock[result] = std::unique_ptr< json_struct>(new json_struct);
    // printf("Seq_ = %s :%d\r\n",Seq_.c_str(),any_block);
     return ((start_block)&&(!end_block));    
  }
 
  size_t
  find(const std::string& Seq_)
  {
    
    bool end_block   = _se.block_find(Seq_)  ;
    bool start_block  = _ss.block_find(Seq_) ;
    bool all_block = (end_block && start_block);
	 std::string result_;    
    if (all_block)
    {
      printf("pos_ss = %zd",_ss.get_pos());
      printf("pos_se = %zd",_se.get_pos());
      size_t lenghth =  _se.get_pos() - _ss.get_pos() ;
      result_ = Seq_.substr( _ss.get_pos()+1,lenghth-2 );
      s_jblock[result_] = std::unique_ptr< json_struct>(new json_struct);      
      printf("Seq_ = ![%s]! :%zd\r\n",result_.c_str(),lenghth);
    }
    printf("==keys_count=%zd",s_jblock.size());
    std::map<std::string,std::unique_ptr<json_struct> >::iterator begin = s_jblock.begin();
    std::map<std::string,std::unique_ptr<json_struct> >::iterator end = s_jblock.end();
    printf("===============================================================\n");
    while (begin!=end)
    {
		printf("map_key=%s\n",begin->first.c_str());
 		++begin;    
    }
     return ((start_block)&&(end_block));    
  }
  
 
 
 
 
  private:
  std::map<std::string,std::unique_ptr<json_struct> > s_jblock;

  TScopeStart _ss;
  TScopeEnd   _se;
};

}