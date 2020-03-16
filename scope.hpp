#include <memory>
#include <vector>
#include <map>

#ifndef __SCOPE__
#define __SCOPE__
namespace Scope
{

	struct pair_min_max
	{
  		size_t min;
  		size_t max;
	};

template<
 typename T
>
struct _token
{
	T _start;
	T _delimiter;
	T _end;
	
	_token(T st,T et ):_start(st),_end(et)
	{};
	_token(T st,T dt,T et ):_start(st),_delimiter(dt),_end(et)
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
					  size_t e_p
					  )
	{
		start_pos = s_p;
		delim_pos = d_p;
		end_pos = e_p;
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
};	




};

#endif
	
