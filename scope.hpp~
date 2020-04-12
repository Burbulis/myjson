#include <memory>
#include <vector>
#include <string>
#include <map>

#ifndef __SCOPE__
#define __SCOPE__
namespace Scope
{
	enum STATE
	{
 		START,
		DELIMITER,
		END	
	};

	struct Obj_
	{
  		size_t start;
  		size_t end;
  		std::string name;
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
	
