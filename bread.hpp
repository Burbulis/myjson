#ifndef _FREAD_
#define _FREAD_
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>

  class blockread_
  {
    FILE *f;
    size_t size_b;//block size;
    std::vector<char> _buffer;	
	 size_t _counter;    
    size_t total_sz;
/////////////////////////////////////////////
//
//
/////////////////////////////////////////////
	size_t 
	get_size(void)
	{
	  if (f==NULL)
	    return (0);	
	  size_t current_sz = ftell(f);	
	  fseek(f,0,SEEK_END);	
     size_t _size = ftell(f); 
     fseek(f,current_sz,SEEK_SET);
     return (_size);
	}
/////////////////////////////////////////////
//
//
/////////////////////////////////////////////
    void 
    reinit(std::vector<char> &buffer_)
    {
    	  fseek(f,_counter,SEEK_SET);  
        fread(&buffer_[0],1,size_b,f);
        std::swap(_buffer,buffer_);
    }

    void 
    reinit(std::vector<char> &buffer_,size_t sz_)
    {
    	  buffer_.resize(sz_);
    	  bzero(&buffer_[0],sz_);
    	  fseek(f,0,SEEK_SET);  
        fread(&buffer_[0],1,sz_,f);
     }


    public:

    blockread_(){}
    
    blockread_(std::string filename,size_t _sz)
    { 
      _counter = 0;
	   size_b = _sz;
	  	_buffer.resize(size_b);
	  	bzero(&_buffer[0],size_b); 
      f=fopen(filename.c_str(),"r");
      total_sz =  get_size();
    }

    bool
    next(void)
    {
      bzero(&_buffer[0],size_b); 
       size_t rest_= (total_sz - _counter);
  		 
      bool ok = (rest_ > size_b);

  	   if (ok)
      {
    		reinit(_buffer);	
        _counter += size_b;
         
        return (	true );
      }
      else
      {
        size_b = rest_;
		  std::vector<char> buffer_;
		  buffer_.resize(size_b);	   	
	     reinit(buffer_);    	
        return (	false );
      }
    }

	size_t size(void) const
	{
		return (total_sz);
	}	    
    
	 void get(std::vector<char>& Buffer)
	 {
 		Buffer=_buffer;
	 }

	 void get(std::vector<char>& Buffer,size_t sz_)
	 {
	 	
	 	reinit(Buffer,sz_);
	 }


    ~blockread_()
    {
		fclose(f);
    }
 };
#endif