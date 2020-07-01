#ifndef __PARSER__
#define __PARSER__
#include <typeinfo>
#include <fstream>      // std::ifstream
#include "scope.hpp"
#include "bread.hpp"


namespace Parse
{

bool 
splitter(std::string item,
         char delimiter,
         std::vector<std::string>& out_)
  {
  std::stringstream ss(item);   
  while (std::getline (ss,item,':'))
   out_.push_back(item);
  
  return (!out_.empty());
  }

/*template
<
 typename T
>
unsigned int
finalize_token_pos
(
   T& BlockRead, 
   Scope::_token<char> xtk
)
/*	START,
		DELIMITER,
		END	

{
	std::vector<char> buffer; 
	 bool go =false;
 do
  {
 	 go =BlockRead.next();
    BlockRead.get(buffer);
    for (size_t i=0;i<buffer.size();++i)
    {
       if (buffer[i]==xtk._start)
       {
			printf("i[start] = [%zd]\n",i);
			return(Scope::STATE::START);       
       }
       if (buffer[i]==xtk._delimiter)
       {
			printf("i[delimiter] = [%zd]\n",i);
			return(Scope::STATE::DELIMITER);       

       }      
       
       if (buffer[i]==xtk._end)
       {
			printf("i[end] = [%zd]\n",i);
   		return(Scope::STATE::END);       
       }

    }
    if (!go)
      break;
  }
  while ( true );

} 
*/

std::string
delete_all(std::string str,char sym,char stop)
{
std::string output;
//output.reserve(str.size()); // optional, avoids buffer reallocations in the loop
for(size_t i = 0; i < str.length(); ++i)
{
  if(str[i] == sym) 
    continue;
  if (str[i] == stop)
    break;

  output.push_back( str[i] );
}
printf("finish = [%s:%zd]\n",output.c_str(),output.length());
//output = str;
return (output);
}






template 
<
  typename T1,
  typename T2
>
void create_seq
(
  std::vector< T1 >& _seq,
  const std::vector< T2 >& o_count_seq_i,
  const std::vector< T2 >& c_count_seq_i
 )
{
  _seq.clear();
 for (size_t i=0;i < o_count_seq_i.size();++i)
   {	
   for (size_t j=0;j < c_count_seq_i.size();++j)  
     {
 	    if (o_count_seq_i[i] < c_count_seq_i[j])
        { 	
  	       _seq.push_back(Scope::_block_object(o_count_seq_i[i],c_count_seq_i[j]));
		    break;     
        } 
     }  	
   }
   return ;
 }

template
<
 typename T
 >
void
preparate_x(
   T& BlockRead, 
 	Scope::_token<char> xtk,
 	std::vector<size_t>& o_count_seq,
 	std::vector<size_t>& d_count_seq,
 	std::vector<size_t>& c_count_seq,
 	std::vector<size_t>& f_count_seq
 	)
{
  std::vector<char> buffer; 
  bool go =false;
  size_t f_count = 0;
  size_t count_ = 0;
  bool first_ = false;
  do
  {
 	 go =BlockRead.next();
    if (!go)
    {
      printf("!!!!!REAL STOP!!!\n\n");
      break;
    }
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
          if (( f_count!= count_ )||(buffer[i]=='\n'))
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
      
  
  }
  while ( true );
}



std::vector< std::string > 
get_str_seq(std::vector<char> in_)
{
  std::vector< std::string > out_;
  std::string str;
  for (size_t i = 0 ; i< in_.size();++i)
  {
    str+=in_[i];
    if (in_[i] == 0x0A)
    {
      out_.push_back(str);
      str.clear();
    }
  }
  return out_;

}


template
<
  typename t_blockread 
>
void get_str_seq(
	t_blockread& BlockRead,
  std::vector<Scope::Obj_>& out_
)
{
  std::vector<char> buffer;
  shared::agregator< 
     t_blockread 
     > agr(BlockRead);
  agr.init(BlockRead); 
  agr(buffer);
  printf("agr::[buffer.size == %zd]\n",buffer.size());

  bool end_ = false;
  std::string str_;
  Scope::Obj_ obj;

  obj.start = 0;
  obj.end = 0;
  for (size_t i=0;i<buffer.size();++i)
  {

    str_ += buffer[i];
    if (end_)
    {
      end_ = false; 
      obj.start = i;
    }
    if (buffer[i] == 0x0A)
    {
      obj.end = i;
      obj.str = str_;
      printf("obj=[%s]%zd:%zd\n",obj.str.c_str(),obj.start,obj.end);
      out_.push_back(obj);
      str_.clear();
      end_ = true;
    }
  }
  return;
}

template
<
 typename t_blockread_
>
void
preparate_x(
	t_blockread_& BlockRead,
 	Scope::_token<char> xtk,
 	std::vector<size_t>& o_count_seq,
 	std::vector<size_t>& c_count_seq)
{
  std::vector<char> buffer; 

  bool go =false;
  size_t count_ = 0;
 // printf("typeid = %s",typeid(BlockRead).name());
  do
  {
 	 go =BlockRead.next();
   
    BlockRead.get(buffer);

    printf("[buffer.size == %zd]\n",buffer.size());
  
    for (size_t i=0;i<buffer.size();++i)
    {
          if (buffer[i]==xtk._start)
          {
            printf("+%zd+",count_);
		        o_count_seq.push_back(count_);    
          }
        
          if (buffer[i]==xtk._end)
          {
            printf("+%zd+",count_);
		        c_count_seq.push_back(count_);
		      }     
		    printf("%c",buffer[i]);      
			  ++count_;      
       }
      if (!go)
      {
        printf("!!!***REAL STOP***!!!\n");
        break;
      }
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
    printf("obj_start=%zd ; obj_end=%zd\n",obj_.start,obj_.end);
    std::vector<size_t>::iterator found_=std::find(o_count_seq.begin(),o_count_seq.end(),obj_.start);
    printf("found_ = %zd\n",(*found_));
    o_count_seq.erase(found_);
    found_=std::find(c_count_seq.begin(),c_count_seq.end(),obj_.end);
    printf("found_ = %zd\n",(*found_));
       c_count_seq.erase(found_,c_count_seq.end());
//  o_count_seq.erase(min);
//  c_count_seq.erase(max); 
  return (obj_);
}



}
#endif
