#ifndef __MANIPULATORS__
#define __MANIPULATORS__
namespace manip
{
//
//
//    
  struct null_manipulator
  {
    null_manipulator(std::string tag_name,
		std::string manip_){}
    bool
    operator() (std::string token_str)
    {
    }
  };
//
//
//    
  struct sym_manipulator
  {
    sym_manipulator(std::string tag_name,
		std::string manip_):
    _tag_name(tag_name),_manip(manip_)
    {};

    
    std::string
    operator() (std::string token_str)
    {
      while (true)
      {
        int _pos = token_str.find(_tag_name,0);
        if (  std::string::npos == _pos  )
          break;
        token_str.erase ( _pos , _tag_name.length() );
        token_str.insert( _pos , &_manip[0] , _manip.length() );
      }
      return ( token_str );
    }

  private:
    std::string _tag_name;
    std::string _manip;
  };	
//
//
//    
};  
#endif 