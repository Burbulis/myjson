#ifndef _FREAD_
#define _FREAD_
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>

namespace shared
{
  class base_of
  {
public:

base_of(){}
virtual ~base_of(){}

virtual void reinit(std::vector<char> &buffer_)=0;
virtual void reinit(std::vector<char> &buffer_,size_t sz_)=0;

protected:
  virtual size_t get_size(void) = 0;

 	  size_t size_b;
    size_t _counter;    
    size_t total_sz;

    void test()
    {
      printf("test!\n");
    }

public:  

  virtual bool next(void) = 0;
 // virtual void get(std::vector<char>& Buffer,size_t sz_)=0;
 // virtual void get(std::vector<char>& Buffer)=0;

  };

  template
  <
    typename t_bread
  >
  struct agregator
  {
    std::vector< char > _buffer;

    agregator(){}

    agregator(t_bread& BlockRead)
    {
      //init< t_bread >(BlockRead);
    }

    
    void
    init(t_bread& BlockRead)
    {
      printf("****init******\n");
      size_t total_size_ = BlockRead.size();
      bool go = false;  
      std::vector< char > Buffer;
      do{     
        

        go = BlockRead.next();
        BlockRead.get(Buffer);
        _buffer.insert(_buffer.end(),Buffer.begin(),Buffer.end());
        printf("init()::typeid(%s),buff_sz=%zd\n",typeid(t_bread).name(),_buffer.size());
        if (!go)
          break;

        }
      while(true);
      printf("while exit.. go = %d , buffer.sz = %zd\n",go,_buffer.size());
    
    }

    bool 
    operator()(std::vector< char >& buffer)
    {
      printf("arg()::typeid(%s),buff_sz=%zd\n",typeid(t_bread).name(),_buffer.size());
      buffer = _buffer;
    }

  };

};

namespace file
{

  namespace pascal
  {
//test
  class blockread
  {
     FILE *f;
     size_t _begin;
     size_t _end;
     std::vector< char > _buffer;
  public:
    blockread(
      std::string filename
    )
    {
       f = fopen(filename.c_str(),"rb+") ;
    }

    void init(
     size_t begin,
     size_t end
    )
  {
    _begin=begin;
    _end = end;
    size_t sz_ =  _end - _begin;
    _buffer.resize(sz_);
    bzero(&_buffer[0],sz_);
    fseek(f,_begin,SEEK_SET);
    fread(&_buffer[0],1,sz_,f);
  }

  void
  get(std::vector<char>& buffer)
  {
    buffer = _buffer;
  }



  ~blockread()
  {
    fclose(f);
  }



  };

  }

  template
  <
  typename base_
  >
  class blockread_
   :protected base_
  {
    FILE *f;
   
    std::vector<char> _buffer;	
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
    	  fseek(f,base_::_counter,SEEK_SET);  
        fread(&buffer_[0],1,base_::size_b,f);
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
   // base_::test();

     base_::_counter = 0;
	   base_::size_b = _sz;
	  	_buffer.resize(base_::size_b);
	  	bzero(&_buffer[0],base_::size_b); 
      f=fopen(filename.c_str(),"r");
      base_::total_sz =  get_size();
    }

    bool
    next(void)
    {
      bzero(&_buffer[0],base_::size_b); 
       size_t rest_= (base_::total_sz - base_::_counter);
  		 
      bool ok = (rest_ > base_::size_b);

  	   if (ok)
      {
    		reinit(_buffer);	
        base_::_counter += base_::size_b;
        printf("go = true,base_::size_b=%zd , rest_ = %zd\n",base_::size_b,rest_);       
        return (	true );
      }
      else
      {
       base_::size_b = rest_;
		  std::vector<char> buffer_;
		  buffer_.resize(base_::size_b);	   	
	     reinit(buffer_);    	
       printf("go = false,base_::size_b=%zd",base_::size_b);
        return (	false );
      }
    }

	size_t size(void) const
	{
		return (base_::total_sz);
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
    f = NULL;
    //printf("fclose()-test \n");
    }
 };


  typedef blockread_< shared::base_of > b_read;
 };


namespace mem
{




 template
  <
  typename base_
  > 
 class blockread_
   :protected base_
 {
  // size_t size_b;//block size;
   std::vector<char> _buffer;	
	
   /*
TODO: Создать методы 
get();
next();
и отладить.
   */
 
	
   public:
    blockread_(const std::vector< char >& buffer)
      {
      _buffer.clear();
      _buffer.insert(_buffer.end(),buffer.begin(),buffer.end());
      printf("blockread.ctr():sz = %zd : %zd \n",_buffer.size() , buffer.size());   
      base_::size_b = buffer.size();
      base_::_counter = 0;
      }
    
    void get(std::vector<char>& Buffer)
    {
      Buffer = _buffer;
      
    }

    bool
    next(void)
    {
      printf("emulator\n\n");
      return (	false );
    }

    void 
    reinit(std::vector<char> &buffer_)
    {}
    
    void 
    reinit(std::vector<char> &buffer_,size_t sz_)
    {}
   
    void 
    get(std::vector<char>& Buffer,size_t sz_)
	  {
    }
    /*void 
    get(std::vector<char>& Buffer,size_t sz_)
	  {}*/

    size_t 
    get_size(void)
    {
      return(_buffer.size());
    }
    size_t size(void) const
    {
      return(_buffer.size());
    }

   void
   set_borders(size_t begin,size_t end) 
   {
     std::vector<char> buffer_;
     buffer_.clear();
     buffer_.insert(buffer_.end(),_buffer.begin()+begin,_buffer.begin()+end);
     //std::swap(_buffer,buffer_);
     base_::total_sz = buffer_.size();
     printf("++[debug]\n"); 
     for (size_t i = 0 ;i<buffer_.size(); ++i)
     {
       printf("%c",buffer_[i]);
     }
     printf("\n--[debug]\n"); 

   } 



   void
   set_borders(const Scope::_block_object& obj)
   {
      set_borders(obj.start_pos + 1,obj.end_pos);     
   } 

 	void
	add(const std::vector<char>& buffer)
	{
		if (buffer.empty())
		  return ;
		_buffer = buffer;
    base_::total_sz = _buffer.size();
	}	   
 
 
 };
 typedef blockread_< shared::base_of > b_read;
 } 
 
 
 
#endif