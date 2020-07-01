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
  std::vector<size_t> b_o_count_seq;
  std::vector<size_t> b_c_count_seq;
  std::vector<size_t> b_d_count_seq;
  std::vector<size_t> b_f_count_seq;
  printf("variable block detector started..\n")  ;
     
  file::blockread_< shared::base_of > BlockRead(argv[1],100);    
  std::vector< Scope::_block_object > _seq;
  {  
    Scope::_token<char> _bxtk('"',':','"',',');

    Parse::preparate_x< file::blockread_< shared::base_of > >(BlockRead,_bxtk,
    b_o_count_seq,
    b_d_count_seq,
    b_c_count_seq,
    b_f_count_seq);
    std::vector<char> Buffer;
    std::vector<size_t> c_count_seq_i;
    std::vector<size_t> o_count_seq_i;
    Scope::_token<char> _xxtk('{','}');
    file::blockread_< shared::base_of > BlockRead(argv[1],100);
    Parse::preparate_x< file::blockread_< shared::base_of > >(BlockRead,_xxtk,o_count_seq_i,c_count_seq_i);
    Parse::create_seq< Scope::_block_object , size_t> (  _seq , o_count_seq_i , c_count_seq_i);
 	  printf("_seq.size()=%zd\n",_seq.size());
  }
   std::vector<char> Buffer;
   Buffer.resize(BlockRead.size()); 	
   BlockRead.get(Buffer,BlockRead.size());
  for (size_t i = 0;i < _seq.size();++i)
    {
      printf("_seq[%zd] = (%zd,%zd)\n",i,_seq[i].start_pos,_seq[i].end_pos);
    }

 {
   std::vector<size_t> c_count_seq_i;
   std::vector<size_t> o_count_seq_i;
   mem::blockread_<shared::base_of> BlockRead(100);
   BlockRead.add(Buffer);  
   Scope::_token<char> _bxtk('[',',',']',',');
 //  unsigned int state_ = Parse::finalize_token_pos<file::blockread_>(BlockRead,_bxtk);
   Parse::preparate_x< mem::blockread_< shared::base_of > >(BlockRead,_bxtk,o_count_seq_i,c_count_seq_i);

   printf("_o_count_seq.sz=%zd,\n ",o_count_seq_i.size());
	 printf("_c_count_seq.sz=%zd,\n ",c_count_seq_i.size());

   Parse::create_seq< Scope::_block_object , size_t>(  _seq , o_count_seq_i , c_count_seq_i);
   printf("_seqxx.size()=%zd\n",_seq.size());
    for (size_t i = 0;i < _seq.size();++i)
    {
      printf("_seqx[%zd] = (%zd,%zd)\n",i,_seq[i].start_pos,_seq[i].end_pos);
    }
   //printf("STATE:%d\n",state_);

   printf("Buffer.sz=%zd\n",Buffer.size()); 		

 }		
  printf("b_o_count_seq.sz=%zd,\n ",b_o_count_seq.size());
	printf("b_c_count_seq.sz=%zd,\n ",b_c_count_seq.size());		
	printf("b_d_count_seq.sz=%zd,\n ",b_d_count_seq.size());		
	printf("b_f_count_seq.sz=%zd\n",b_f_count_seq.size());	
	
//	for (size_t i=0;i<b_o_count_seq.size();++i)
//	{
//     printf("b_o_count_seq[%zd] = %zd\n",i,b_o_count_seq[i]);
//      printf("b_c_count_seq[%zd] = %zd\n",i,b_c_count_seq[i]);	
//	}	
	
	
	std::vector<Scope::Obj_> obj_seq_;

	std::vector<Scope::Obj_> obj_seq_x;

   std::vector<size_t> obj;
	//for (size_t i = 0;i<b_d_count_seq.size();++i)	
	//{	 
   // finalize_token_pos()

	  for (size_t j = 0;j<b_c_count_seq.size();++j)
     {
     	size_t current = b_c_count_seq[j];
      size_t obj_current = b_o_count_seq[j];
		  size_t delim_ = b_d_count_seq[j];      
      
      size_t jn = j+1;
     
      size_t next = b_o_count_seq[jn]; 
      size_t first = b_c_count_seq[jn];
      printf("current = %zd , obj_current=%zd ,delim_ = %zd ,first= %zd,next=%zd\n",current,obj_current,delim_,first,next);
      if ((current < delim_)/* && (next > delim_)*/)
      {
        	obj.push_back(obj_current);	
        	Scope::Obj_ pmx;
       	  Scope::Obj_ pmx_;
        //	if (obj_current < current)
        //	{
       // 	printf("obj_current=%zd\n",obj_current);
          	pmx.start = obj_current;
          	pmx.end = current;
			 	    pmx_.start = next;
			 	    pmx_.end = first;           
          	obj_seq_.push_back(pmx);
			    	obj_seq_x.push_back(pmx_);	        
        	//}
        //  printf("obj_seq_.size() = %zd\n",obj_seq_.size());
         // getc(stdin);
        //	printf("start = %zd, end=%zd, next = %zd , obj=%zd\n",obj_seq_[obj_seq_.size()-1].start,obj_seq_[obj_seq_.size()-1].end,next,first);
	      //  printf("start_x = %zd, end_x=%zd, next_x = %zd , obj_x=%zd\n",obj_seq_x[obj_seq_.size()-1].start,obj_seq_x[obj_seq_.size()-1].end,next,first);

      }	
	}
  printf("obj_seq_.size() = %zd\n",obj_seq_.size());
  printf("obj_seq_x.size() = %zd\n",obj_seq_x.size());
	printf("obj.sz=%zd\n",obj.size());
	for (size_t i = 0;i<obj_seq_.size();++i) 
	{
		printf("[start = %zd, end=%zd]\n",obj_seq_[i].start,obj_seq_[i].end);	
    printf("[start_x = %zd, end_x=%zd]\n",obj_seq_x[i].start,obj_seq_x[i].end);	
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

  //}
}