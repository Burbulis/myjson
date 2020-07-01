#ifndef  __SCOPE__
#define  __SCOPE__

#include <memory>
#include <vector>
#include "hash.hpp"
namespace Scope
{

enum STATE
{
  START,
  DELIMITER,
  END
};

	

	struct x_count
	{
		x_count(){};            
		x_count(char tk,size_t count):
			token_(tk),count_(count){

				hash::tok_obj to(count_,token_);
				hash_ = to.rehasher(count_ + token_);		
				printf("[token=%c|(%x),count=%zd,hash = %zd]\n",tk,tk,count,hash_);	
			}

		void 
		add_pos(std::size_t _pos)
		{
			positions.push_back( _pos );
		}
  
		size_t hash(void) const
		{
			return (hash_);
		}

  template
  <
	typename T
  >
  static size_t
  counter(const T string_obj_templ[])
  {
	size_t templ_count = 0; 
	const size_t END = 443588293172173636;
  	do
  	{
    	if (string_obj_templ[templ_count].hash() == END) 
		{
        	break;
		}
    	++templ_count;
  	} while (true);

	  return (--templ_count);
  }

		std::vector<std::size_t> positions;
		char token_;	
		size_t count_;
		size_t hash_;
	};


	struct Obj_
	{
  		size_t start;
  		size_t end;
  		std::string str;  
	};


	struct x_Obj:public Obj_
 	{
		std::vector<x_count> seq; 
		std::string str;
	 };

	template
	<
	  typename T
	>
	struct common
	{
		common(size_t sz_):SZ(sz_){}
	   T obj_[];
	   size_t SZ;	
		/* data */
	};
	



template<
 typename T
>
struct _token
{
	T _start;
	T _delimiter;
	T _end;
	T _fin_val;
	
	_token(T st,T et ):_start(st),_end(et)
	{};
	_token(T st,T dt,T et,T ft):_start(st),_delimiter(dt),_end(et),_fin_val(ft)
	{};
	
	~_token(){};
};	
	
typedef _token<char> _tk;	
	
struct _block_object
{

   _block_object(
					  size_t s_p,
					  size_t e_p
					  )
	{
		start_pos = s_p;
		delim_pos = 0;
		end_pos = e_p;
	}
	
	

	
	
	_block_object(
					  size_t s_p,
					  size_t d_p,
					  size_t e_p,
					  size_t f_p
					  )
	{
		start_pos = s_p;
		delim_pos = d_p;
		end_pos   = e_p;
		fin_pos   = f_p;
	}

	bool
	operator==(_block_object& obj)
	{
		return ((start_pos == obj.start_pos)&&(end_pos == obj.end_pos));
	}	
	
	bool
	operator<(const _block_object& obj)
	{
		return (end_pos < obj.end_pos);
	}	
	
	bool
	operator>(const _block_object& obj)
	{
		return ((start_pos > obj.start_pos)&&(end_pos > obj.end_pos));
	}		
	
	//private:
	size_t start_pos;
	size_t delim_pos;	
	size_t end_pos;
	size_t fin_pos;
};	





};
#endif