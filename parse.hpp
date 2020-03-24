#include <fstream>      // std::ifstream
#include "scope.hpp"
#include "bread.hpp"
#ifndef __PARSER__
#define __PARSER__

namespace Parse
{

void
preparate_x(
	std::string FileName,
 	Scope::_token<char> xtk,
 	std::vector<size_t>& o_count_seq,
 	std::vector<size_t>& d_count_seq,
 	std::vector<size_t>& c_count_seq,
 	std::vector<size_t>& f_count_seq
 	)
{
  std::vector<char> buffer; 
  blockread_ BlockRead(FileName.c_str(),100); 
  bool go =false;
  size_t f_count = 0;
  size_t count_ = 0;
  bool first_ = false;
  do
  {
 	 go =BlockRead.next();
    BlockRead.get(buffer);
    for (size_t i=0;i<buffer.size();++i)
    {
      if (buffer[i]==xtk._start)
      {
      	if (!first_)
      	{
           first_=true;	
           printf(" fs |%zd",count_);
		     o_count_seq.push_back(count_);    
           f_count = count_;
	      }
      }

      if (buffer[i]==xtk._delimiter)
      {
        printf("dlm |%zd",count_);
		  d_count_seq.push_back(count_);     
      }

      if (buffer[i]==xtk._end)
      {
        if (first_)
        {     	
          if ( f_count!= count_)
          {
           first_=false;
           printf(" fc |%zd",count_);
		     c_count_seq.push_back(count_);
			 }
		  }     
      }
      

      if (buffer[i]==xtk._fin_val)
      {
      	if (!first_)
      	{   
           printf(" fv |%zd",count_);
	        f_count_seq.push_back(count_);
	      }
		}    
			   printf("%c",buffer[i]);	   
++count_;    
    }         
      
    if (!go)
      break;
  }
  while ( true );
}

void
preparate_x(
	std::string FileName,
 	Scope::_token<char> xtk,
 	std::vector<size_t>& o_count_seq,
 	std::vector<size_t>& c_count_seq)
{
  std::vector<char> buffer; 
  blockread_ BlockRead(FileName.c_str(),100); 
  bool go =false;
  size_t count_ = 0;
  do
  {
 	 go =BlockRead.next();
    BlockRead.get(buffer);
    for (size_t i=0;i<buffer.size();++i)
    {
       if (buffer[i]==xtk._start)
       {
          printf("%zd",count_);
		    o_count_seq.push_back(count_);    
                 }
        if (buffer[i]==xtk._end)
        {
          printf("%zd",count_);
		    c_count_seq.push_back(count_);
		  }     
		 printf("%c",buffer[i]);      
			++count_;      
      }
     if (!go)
      break;
   }
   while ( true );
}

//typedef   s_pair_mm;

Scope::Obj_
_xX(
 std::vector<size_t>& o_count_seq,
 std::vector<size_t>& c_count_seq
)
{
  Scope::Obj_ obj_;	
  std::vector<std::unique_ptr<Scope::_block_object> > seq_;
  std::vector<size_t>::iterator max = std::max_element(c_count_seq.begin(),c_count_seq.end());
  std::vector<size_t>::iterator min = std::min_element(o_count_seq.begin(),o_count_seq.end());
  seq_.push_back( std::unique_ptr<Scope::_block_object>(new Scope::_block_object( (*min) , (*max) )));
	obj_.start = (*min);
	obj_.end = (*max);
  o_count_seq.erase(min);
  c_count_seq.erase(max); 
  return (obj_);
}



}
#endif
