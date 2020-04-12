#include <memory>
#include <algorithm>
#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "scope.hpp"
#include "parse.hpp"
#include "bread.hpp"





int main(int argc,char *argv[])
{
/*  std::vector<size_t> o_count_seq_i;
  std::vector<size_t> c_count_seq_i;
  std::vector<size_t> d_count_seq_i;
  printf("object detector started..\n")  ;
  
  Scope::_token<char> _xxtk('{','}');
  file::blockread_ BlockRead(argv[1],100);
  Parse::preparate_x<file::blockread_>(BlockRead,_xxtk,o_count_seq_i,c_count_seq_i);	
  
  printf("[o_count=%zd]\n",o_count_seq_i.size());
  printf("[c_count=%zd]\n",c_count_seq_i.size());

  for (size_t j=0;j<o_count_seq_i.size();++j)
  {
	 printf("o_count_seq[%zd]=%zd,",j,o_count_seq_i[j]);  	
	 printf("c_count_seq[%zd]=%zd\n",j,c_count_seq_i[j]);  	
  }
  
  
   Scope::Obj_ mm_ = Parse::_xX(o_count_seq_i,c_count_seq_i);
   printf("mm->start=%zd\n",mm_.start);  
   printf("max->end=%zd\n",mm_.end);
 
   std::vector<Scope::_block_object > _seq;
  
   
   std::vector<Scope::_block_object > _seq_obj;	 
  _seq_obj.push_back((Scope::_block_object(mm_.start,mm_.end)));
  _seq.push_back((Scope::_block_object(mm_.start,mm_.end)));
  
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
  
    printf("**total_seq_count=%zd**\n",_seq.size()); 
    for (size_t i=0;i < _seq.size();++i)
    {	
  		printf("sp:%zd,ep:%zd\n",_seq[i].start_pos,_seq[i].end_pos);
    }   
   std::vector<Scope::_block_object >::iterator min = std::min_element(_seq.begin(),_seq.end());
    
    size_t count = 0;//std::count(c_count_seq.begin(),c_count_seq.end(),min->end_pos);
   
    for (size_t i=0;i < _seq.size();++i)
    {	
  		count += ( min->end_pos == _seq[i].end_pos) ;
    }   
    
    printf("counter=%zd\n",count);

	 if (count>1)
	 {
	 	
	  while(true)
	  {
	     mm_ = Parse::_xX(o_count_seq,c_count_seq);
		  printf("min=%zd,max=%zd\n",mm_.min,mm_.max);		  
		
		_seq_obj.push_back(Scope::_block_object(mm_.min,mm_.max));	
       if (o_count_seq.empty()&&o_count_seq.empty())	
		 {  
		   printf("Is_Empty\n");
         break;  	   
  	    }
  	  }

     
  }
{
	    mm_ = Parse::_xX(o_count_seq,c_count_seq);
		 	printf("min=%zd,max=%zd\n",mm_.min,mm_.max);		  

		 	printf("_seq.size()=%zd\n",_seq.size());
  			for (size_t j=0;j < _seq.size();++j)  
        	{
        		printf("o_count= %zd,c_count=%zd\n", _seq[j].start_pos,_seq[j].end_pos);
	     	}      		 
	  blockread_ BlockRead(argv[1],100);
     std::vector<char> Buffer;
     Buffer.resize(BlockRead.size()); 	
     BlockRead.get(Buffer,BlockRead.size());
	  printf("*************************************************************\n");
	   printf("start_pos = %zd, end_pos=%zd\n",_seq[2].start_pos,_seq[2].end_pos);  
     create_seq
	  for (size_t i=_seq[2].start_pos;i<=_seq[2].end_pos;++i)	
	  {
       printf("%c",Buffer[i]);	  
	  }	
	  printf("\n*************************************************************\n");
 } */
  std::vector<size_t> b_o_count_seq;
  std::vector<size_t> b_c_count_seq;
  std::vector<size_t> b_d_count_seq;
  std::vector<size_t> b_f_count_seq;
  printf("variable block detector started..\n")  ;
     std::vector<char> Buffer;
  file::blockread_ BlockRead(argv[1],100); 
{  
   
  Scope::_token<char> _bxtk('"',':','"',',');

  Parse::preparate_x<file::blockread_>(BlockRead,_bxtk,
  b_o_count_seq,
  b_d_count_seq,
  b_c_count_seq,
  b_f_count_seq);

  std::vector<size_t> c_count_seq_i;
  std::vector<size_t> o_count_seq_i;
  std::vector<Scope::_block_object > _seq;
  Scope::_token<char> _xxtk('{','}');
  file::blockread_ BlockRead(argv[1],100);
  Parse::preparate_x<file::blockread_>(BlockRead,_xxtk,o_count_seq_i,c_count_seq_i);
  Parse::create_seq< Scope::_block_object , size_t>(  _seq , o_count_seq_i , c_count_seq_i);
 	printf("_seq.size()=%zd\n",_seq.size());
 	
 	for (size_t i = 0 ; i< _seq.size();++i)
 	{
 	}
}

 {
//	file::blockread_ BlockRead(argv[1],100);  
   Scope::_token<char> _bxtk('[',',',']',',');
   unsigned int state_ = Parse::finalize_token_pos<file::blockread_>(BlockRead,_bxtk);
   printf("STATE:%d\n",state_);
   Buffer.resize(BlockRead.size()); 	
   BlockRead.get(Buffer,BlockRead.size());
   printf("Buffer.sz=%zd\n",Buffer.size()); 		

 }
   

   printf("Buffer.sz=%zd\n",Buffer.size()); 		
   printf("b_o_count_seq.sz=%zd,\n ",b_o_count_seq.size());
	printf("b_c_count_seq.sz=%zd,\n ",b_c_count_seq.size());		
	printf("b_d_count_seq.sz=%zd,\n ",b_d_count_seq.size());		
	printf("b_f_count_seq.sz=%zd\n",b_f_count_seq.size());	
	
	for (size_t i=0;i<b_o_count_seq.size();++i)
	{
     printf("b_o_count_seq[%zd] = %zd\n",i,b_o_count_seq[i]);
      printf("b_c_count_seq[%zd] = %zd\n",i,b_c_count_seq[i]);	
	}	
	
	
	std::vector<Scope::Obj_> obj_seq_;

	std::vector<Scope::Obj_> obj_seq_x;

   std::vector<size_t> obj;
	for (size_t i = 0;i<b_d_count_seq.size();++i)	
	{	 	  	
	  for (size_t j = 0;j<b_c_count_seq.size();++j)
     {
     	size_t current = b_c_count_seq[j];
      size_t obj_current = b_o_count_seq[j];
		size_t delim_ = b_d_count_seq[j];      
      
      size_t jn = j+1;
     
      size_t first = b_o_count_seq[jn]; 
      size_t next = b_c_count_seq[jn];
      printf("current = %zd , delim_=%zd ,next=%zd\n",current,delim_,next);
      if ((current < delim_) && (next > delim_))
      {
        	obj.push_back(obj_current);	
        	Scope::Obj_ pmx;
       	Scope::Obj_ pmx_;
        	if (obj_current < current)
        	{
       // 	printf("obj_current=%zd\n",obj_current);
          	pmx.start = obj_current;
          	pmx.end = current;
			 	pmx_.start = first;
			 	pmx_.end = next;           
          	
          	obj_seq_.push_back(pmx);
			 	obj_seq_x.push_back(pmx_);	        
        	}
       // printf("obj_seq_.size() = %zd\n",obj_seq_.size());
        	printf("start = %zd, end=%zd, next = %zd , obj=%zd\n",obj_seq_[obj_seq_.size()-1].start,obj_seq_[obj_seq_.size()-1].end,next,first);
     }	
	}
	printf("obj.sz=%zd\n",obj.size());
	for (size_t i = 0;i<obj_seq_x.size();++i) 
	{
				
	  //if (std::find(obj.begin(),obj.end(),obj_seq_[i].start)!=obj.end())
		//{
	    std::string str_x;
	    std::string str_;
		 for (size_t j=obj_seq_[i].start+1;j<obj_seq_[i].end;++j)
       {
      	str_+=Buffer[j];
		 }
		 for (size_t j=obj_seq_x[i].start+1;j<obj_seq_x[i].end;++j)
       {
      	str_x+=Buffer[j];
		 }
		 obj_seq_[i].name = str_x;
		 printf("obj_seq_[%zd].name =[%s] : %s\n",i,str_x.c_str(),str_.c_str());
 	 // } 
  	}

 /* std::vector<size_t> o_count_seq;
  std::vector<size_t> c_count_seq;
  Scope::_token<char> _xtk('[',']');

  file::blockread_ _XBlockRead(argv[1],100);  

  Parse::preparate_x<file::blockread_>(_XBlockRead,_xtk,o_count_seq,c_count_seq);	
  
  printf("[o_count=%zd]\n",o_count_seq.size());
  printf("[c_count=%zd]\n",c_count_seq.size());

  for (size_t j=0;j<o_count_seq.size();++j)
  {
	 printf("o_count_seq[%zd]=%zd,",j,o_count_seq[j]);  	
	 printf("c_count_seq[%zd]=%zd\n",j,c_count_seq[j]);  	
  }
 */

}}