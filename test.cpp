#include <memory>
#include <algorithm>
#include <string>
#include <iostream>     // std::cout
#include <fstream>   
#include <regex>
#include "scope.hpp"
#include "parse.hpp"
#include "bread.hpp"


void normalise(std::string obj,std::string reg_ex)
{

      //std::regex ab("[^A-Za-zА-Яа-я0-9_]");
      std::regex ab(reg_ex);
      std::smatch m;
      printf("Obj=%s\n",obj.c_str());

 
      while (std::regex_search(obj,m,ab))
      {
        char detected_ = m[0].str()[0];
        printf("detected (0)std:=%x\n",detected_);
        obj.erase(std::remove(obj.begin(),obj.end(),detected_),obj.end());
        printf("detected (1)std:=%s\n",m[1].str().c_str());
        printf("obj=%s\n",obj.c_str());
    	}    
      

}

template
<
typename T
>
bool 
token_found(T string_obj_templ[],size_t hash)
{
        size_t count_of_sot = Scope::x_count::counter (string_obj_templ);
        printf("count_of_sot=%zd\n",count_of_sot);
        size_t i = 0;
        bool d_out =false;
        while (i<count_of_sot)
        {
          if (string_obj_templ[i].hash() == hash)
          {
            d_out = true;
            
            printf("***token_ detected all right!!!,%zd\n",string_obj_templ[i].hash());
            break;
          }
          ++i;  
        }

        return( d_out );
        
}

//
//
//  TODO : need fixed bug stack overflov on this code. 
//  in str 63/65
//
//
template
<
  typename T
>
void 
get_tokens(T string_obj_templ[],
      std::string obj,
      std::string reg_ex, 
      Scope::x_Obj&  out_obj)
{
      std::regex ab(reg_ex);
      std::smatch m;
      printf("get_tokens Obj=%s\n",obj.c_str());
	  //char token_;	
		//size_t count_;      
      out_obj.str = obj;
     
      while (std::regex_search(obj,m,ab))
      {
        char detected_ = m[0].str()[0];
        printf("detected (0)std:=[%c,%x]",detected_,detected_);
        size_t count_ = std::count(obj.begin(),obj.end(),detected_);
        printf("count = %zd,(%c|%x)\n",count_,detected_,detected_);  
        Scope::x_count x_c(detected_,count_);
        
          if (token_found<T>(string_obj_templ,x_c.hash()))
          {
  
         // x_c.token_ = detected_;
         // x_c.count_ = ;
          //printf("token counted!!!%zd\n",x_c.count_);
          size_t pos = obj.find(detected_);
            if (pos!=std::string::npos)
            {
              printf("get_tokens::detected = %c,pos= %zd",detected_,pos);
              x_c.add_pos(pos);
              out_obj.seq.push_back(x_c);
              
              printf("***xc[%c,%zd,%zd][_obj.seq_sz=%zd,(%s)]",x_c.token_,x_c.count_,x_c.hash(),out_obj.seq.size(),out_obj.str.c_str()); 
            }
             
            
          }
       // out_.push_back(detected_);
      //  std::string::iterator end_ = std::remove(obj.begin(),obj.end(),detected_);
        printf("token=%s , len=%zd\n",obj.c_str(),obj.length());
       // obj.erase(end_,obj.end());
       // HERE ERROR DETECTED!!!!!!!
        if (detected_ == 0x0A)
        {
          
          printf("*_obj.seq_sz=%zd",out_obj.seq.size());
          for (size_t i= 0 ; i<out_obj.seq.size();++i)
          {
            printf("***token_=[%c,%x],%zd\n",out_obj.seq[i].token_,out_obj.seq[i].token_,out_obj.seq[i].count_);  

          }
          
          
          printf("enter detected .. \n");
          break;
        }
       // obj = Parse::delete_all(obj,detected_,0x0A);
        obj.erase(std::remove(obj.begin(), obj.end(),detected_ ), obj.end());
        printf("obj_del = %s\n",obj.c_str());
      //  getc(stdin); 
     
       // printf("obj_str=[%s]sym=[%c,%x] obj_sz=%zd\n",obj.c_str(),x_c.token_,x_c.token_,x_c.count_);
    	}  
      printf("exit..\n");  
}

bool
compare(
              const Scope::x_Obj&  _lobj,
             const Scope::x_Obj&  _robj,
             Scope::x_Obj&  _out_robj
             )
{
 if (_lobj.seq.empty() || _robj.seq.empty())
   return (false);

  if (_lobj.seq.size() != _robj.seq.size())
  {
    printf("_lobj.seq.size()=%zd , _robj.seq.size() = %zd",_lobj.seq.size(),_robj.seq.size());
    size_t min_ = (_lobj.seq.size()<_robj.seq.size())?_lobj.seq.size():_robj.seq.size();
    for (size_t i = 0 ; i<min_;++i)
    {
      printf("hash_detector = [%zd]\n",_lobj.seq[i].hash());
    }

    return (false);
  }
//bool token_ detected
 size_t counter = 0;
 size_t count_detect = 0;
 for(size_t j = 0 ; j < _lobj.seq.size()   ; ++j)
 {
   for (size_t i = 0; i < _robj.seq.size() ; ++i)
   {
  
     count_detect += (_robj.seq[i].hash() ==  _lobj.seq[j].hash());
     
     //if (_robj.seq[i].token_ ==  _lobj.seq[j].token_){
    
     
     if (_lobj.seq.size()==count_detect)
     {
      // printf("'!!!test:(%c|%c)|(%zd ,%zd)'\n",_robj.seq[i].token_,_lobj.seq[j].token_,i,j);
      // printf("DETECTED!!!!!!!:%s:%zd:'%c':%zd\n",_robj.str.c_str(),_lobj.seq[j].count_,_lobj.seq[j].token_,count_detect);
      // printf("DETECTED!!!!!!!:%s:%zd:'%c':%zd\n",_lobj.str.c_str(),_robj.seq[i].count_,_robj.seq[i].token_,count_detect);
       _out_robj = _robj;

     }
   }
  }
    std::size_t pos = 0;
   // do
   // {
   //     pos = _robj.str.find(_robj.seq[i].token_,pos);
         
   //     if (pos == std::string::npos)
   //        break; 
   //      _out_robj.seq[i].positions.push_back(pos);
   //       ++pos;

   //    }while (true);
      
      
       
       
    //   ++counter;
    //   continue;

   
  // }
  //}
  //printf("counter = %zd , test_sz = %zd\n",counter,_lobj.seq.size()); 

  return (_lobj.seq.size()==count_detect);

}

template
<
  typename T
>
void
get_seq_by_flag(T& BlockRead,
      Scope::_token<char> _xxtk,
      std::vector<Scope::_block_object >& _seq
    )
{

    std::vector<char> Buffer;
    std::vector<size_t> c_count_seq_i;
    std::vector<size_t> o_count_seq_i;
   
   // Scope::_token<char> _xxtk('{','}');
   // file::blockread_< shared::base_of > BlockRead(argv[1],total_size_);
    BlockRead.get(Buffer,BlockRead.size());
    printf("BlockRead.get.buffer.sz  = %zd\n",BlockRead.size());
    Parse::preparate_x< T >(BlockRead,_xxtk,o_count_seq_i,c_count_seq_i);
    printf("o_count_seq_i.sz= %zd\n",o_count_seq_i.size());
    printf("c_count_seq_i.sz= %zd\n",o_count_seq_i.size());

    Scope::Obj_ mm = Parse::_xX(o_count_seq_i,c_count_seq_i);
    o_count_seq_i.push_back(mm.start);
    c_count_seq_i.push_back(mm.end);
    printf("(0)[mm.start= %zd,mm.end= %zd]\n",mm.start,mm.end); 
  
  //  std::vector< Scope::_block_object > x_seq;
    Parse::create_seq< Scope::_block_object , size_t> (  _seq , o_count_seq_i , c_count_seq_i);
 	  printf("_seq.size()=%zd\n",_seq.size());
   

}

 //  Scope::x_count string_obj_templ[] = {{'"',4},{':',1}};   
 //  T test;
 //  T string_obj_templ[] = {{'"',4},{':',1}};  
void
get_value()
{


}


//void 



template
<
  typename T,
  typename t_read
>
bool
templ_(
  //templ_<Scope::x_count,mem::b_read>(name_obj,"[^A-Za-zА-Яа-я0-9_]",obj_detected_,mem::b_read(_buffer))
   T string_obj_templ[],
   std::string token_,
   std::vector<Scope::x_Obj>& detected_,
   t_read BlockRead)
{

  Scope::x_Obj out_obj;
  Scope::x_Obj xout_obj;
   std::vector<Scope::Obj_> out_;
   ;
    Parse::get_str_seq<t_read>(
      BlockRead,out_
    );

  size_t templ_count = Scope::x_count::counter(string_obj_templ);
  //printf("TEMPL_COUNT = %zd\n",templ_count);  
  //printf("sz_str_out=%zd\n",out_.size());

  bool ret_ = false;

  for (size_t i = 0 ; i<out_.size(); ++i)
  {
    out_obj.seq.clear();
    //get_tokens(std::string obj,std::string reg_ex, Scope::x_Obj&  _obj)
    //	char token_;	
		//size_t count_;
    get_tokens<T>(string_obj_templ,out_[i].str,token_,out_obj);
    out_obj.start = out_[i].start;
    out_obj.end = out_[i].end;
    
    printf("out_obj.str=%s\n",out_obj.str.c_str()); 
    printf("out_obj.start=%zd,out_obj.end=%zd",out_obj.start,out_obj.end);
    printf("\n****\n");
    printf("out_obj.str=%s\n",out_obj.str.c_str());
    for (size_t i = 0; i < out_obj.seq.size(); i++)
    {
      /* code */
      printf("out_obj.seq[%zd].count_ = %zd,%zd\n",i, out_obj.seq[i].count_,out_obj.seq[i].hash());
    }
    printf("****");
    
   // printf("out_obj.start=%zd , out_obj.end=%zd\n\n",out_obj.start,out_obj.end);

    Scope::x_Obj _xobj;  
    _xobj.seq.insert(_xobj.seq.end(),&string_obj_templ[0],&string_obj_templ[templ_count]);
    Scope::x_Obj out_;
    printf("out_obj (out_obj.seq.size=[%zd])\n",out_obj.seq.size());
    ret_ = compare(_xobj , out_obj , out_ );
    
   
   
    if (ret_)
    {
       printf("ret_ = %d,(%s)\n",ret_,out_.str.c_str()); 
      detected_.push_back(out_);
      printf("**[out_str=%s]:%zd**\n",out_.str.c_str(),detected_.size());
   
    }
  }  
  printf("detected=[%zd]\n",detected_.size());
  return (!detected_.empty());
}  

int main(int argc,char *argv[])
{

  printf("variable block detector started..\n")  ;

    file::blockread_< shared::base_of > BlockRead(argv[1],100);
    std::vector<char> Buffer;
    std::vector< Scope::_block_object > t_seq;
    std::vector<size_t> c_count_seq_i;
    std::vector<size_t> o_count_seq_i;
    Scope::_token<char> _xxtk('{','}');
    Parse::preparate_x< file::blockread_< shared::base_of > >(BlockRead,_xxtk,o_count_seq_i,c_count_seq_i);
    BlockRead.get(Buffer);
    printf("_seq.size()=%zd\n",t_seq.size());
    Scope::Obj_ x_obj = Parse::_xX(o_count_seq_i , c_count_seq_i);
    printf("x_start=%zd\n",x_obj.start);
    printf("x_end=%zd",x_obj.end);
    Parse::create_seq< Scope::_block_object , size_t> (  t_seq , o_count_seq_i , c_count_seq_i);
    file::pascal::blockread b_read(argv[1]);
    printf("t_seq_sz = %zd",t_seq.size());
    for (size_t j = 0;j<t_seq.size();++j)
    {
      printf("t_seq[%zd].start_pos = %zd,t_seq[%zd].end_pos=%zd\n",j,t_seq[j].start_pos,j,t_seq[j].end_pos);
      b_read.init(t_seq[j].start_pos,t_seq[j].end_pos);
      b_read.get(Buffer);
      printf("*******************************\n");
      Scope::x_count name_obj[] = {{'"',4},{':',1},{',',1},{0,0}};
      printf("*******************************\n");
      
      std::vector<Scope::x_Obj> obj_detected_;

      if (templ_<Scope::x_count,mem::b_read>(name_obj,"[^A-Za-zА-Яа-я0-9_]",obj_detected_,mem::b_read(Buffer)))
      { 
        printf("Detected!\n");
   
        for (size_t i =0 ; i < obj_detected_.size() ;++i)
        {
          
           printf("!!!::%s",obj_detected_[i].str.c_str());
        }
      }
        printf("*******************************\n");
    }
  return (0);
}
 	
   
   
                                    //}   
  
