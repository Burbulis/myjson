#include <memory>
#include <algorithm>
#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "scope.hpp"
#include "parse.hpp"


int main(int argc,char *argv[])
{
  std::vector<size_t> o_count_seq;
  std::vector<size_t> c_count_seq;
  std::vector<size_t> d_count_seq;
  printf("object detector started..\n")  ;
  
  Scope::_token<char> _xtk('{','}');

  Parse::preparate_x(argv[1],_xtk,o_count_seq,c_count_seq);	
  
  printf("[o_count=%zd]\n",o_count_seq.size());
  printf("[c_count=%zd]\n",c_count_seq.size());

  for (size_t j=0;j<o_count_seq.size();++j)
  {
	 printf("o_count_seq[%zd]=%zd,",j,o_count_seq[j]);  	
	 printf("c_count_seq[%zd]=%zd\n",j,c_count_seq[j]);  	
  }
  
  
  Scope::pair_min_max mm_ = Parse::_xX(o_count_seq,c_count_seq);
  std::vector<Scope::_block_object > _seq_obj;	
  std::vector<Scope::_block_object > _seq;
  
  _seq.push_back((Scope::_block_object(mm_.min,mm_.max)));
  _seq_obj.push_back((Scope::_block_object(mm_.min,mm_.max)));
  for (size_t i=0;i < o_count_seq.size();++i)
  {	
	for (size_t j=0;j < c_count_seq.size();++j)  
   {
 	  if (o_count_seq[i] < c_count_seq[j])
     { 	
  	    _seq.push_back(Scope::_block_object(o_count_seq[i],c_count_seq[j]));
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
    printf("min->ep=%zd\n",min->end_pos);
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
		 	printf("_seq_obj.size()=%zd\n",_seq_obj.size());
  			for (size_t j=0;j < _seq_obj.size();++j)  
        	{
        		printf("o_count= %zd,c_count=%zd\n", _seq_obj[j].start_pos,_seq_obj[j].end_pos);
	     	}      		 
  		   printf("Is_Empty\n");
         break;  	   
  	    }
  	  }
     
  }
  
  std::vector<size_t> b_o_count_seq;
  std::vector<size_t> b_c_count_seq;
  std::vector<size_t> b_d_count_seq;
  printf("variable block detector started..\n")  ;
  
  Scope::_token<char> _bxtk('"',':','"');

  Parse::preparate_x(argv[1],_bxtk,b_o_count_seq,b_d_count_seq,b_c_count_seq);
  
 // printf("b_o_count_seq.sz=%zd\n",b_o_count_seq.size());
 // printf("b_d_count_seq.sz=%zd\n",b_d_count_seq.size());
 // printf("b_c_count_seq.sz=%zd\n",b_c_count_seq.size());
   blockread_ BlockRead(argv[1],100);
   std::vector<char> Buffer;
   Buffer.resize(BlockRead.size()); 	
   BlockRead.get(Buffer,BlockRead.size());
   printf("Buffer.sz=%zd\n",Buffer.size()); 		
	for (size_t i = 0;i<b_o_count_seq.size();++i) 
	{
		std::string str;
		for (size_t j=b_o_count_seq[i];j<b_c_count_seq[i];++j)
       {
       	str+=Buffer[j];
       //	printf("b_o_count_seq[%zd]=%c , ",j,Buffer[j]);
		 }
		 printf("str = %s\n",str.c_str());
	} 
  	

}

