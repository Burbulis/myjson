#ifndef ConvertorsH
#define ConvertorsH
#include <cstdlib>
#include "ctype.h"
#include "windows.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include "type_decl.h"
#include "../common/exceptions.h"
#include "../head_gen/funct.h"

namespace Parser  
{
  namespace tag_convertors
  {
//
//
//
    struct alpha_helper:public  std::binary_function<size_t,size_t,char>
	  {
      size_t 
      operator () 
		  (size_t prev_size,const char ch_x) const
	    {
        if (isalpha(ch_x))
	        return (++prev_size);
		    return (prev_size);
	    }
	  };
//
//
//
	  struct digit_helper:public  std::binary_function<size_t,size_t,char>
	  {
      
      bool 
      operator()(const char ch_x) const
      {
        return (!!isdigit(ch_x));
      }

      size_t 
      operator () 
		  (size_t prev_size,const char ch_x) const
	    {
        if (isdigit(ch_x))
	       return (++prev_size);
		    return (prev_size);
	    }
	  };
//
//  Кортэж данных для smtp/esmtp.
    struct smtp_tuples
    {
      enum
      {
        PLAIN,
        STARTTLS,
        METHODS_END
      };//метод аутентификации 15/02/08 21:24
      smtp_tuples():_port(0),_host(""),_login(""),_pass("")
        ,ath_required(false),_base64_login(""),
         _base64_pass(""),_valid(false),
         initialized(false),conn_method(PLAIN)
      {
      }
      unsigned short _port;
      std::string    _host;
      std::string    _login;
      std::string    _pass;    
      std::string    _base64_login;
      std::string    _base64_pass;    
      std::string    _linked_mail; //емайл для которого предназначена аутентификация
      bool _valid; //внутренний флаг предназначен для различных целей.
      bool ath_required;//аутентификация нужна или нет?
      unsigned int conn_method; //метод аутентификации 15/02/08 21:24
      bool initialized;
    };
//
//

//**************************************************     
//
//**************************************************     
   template 
   <
    typename Strategy_
   >
   bool 
   accum_(const char *str , 
   Strategy_ strategy_ ) 
   {
     if ( !str )
       return (0);
     size_t count_ = strategy_( str[0] );   
		 size_t size_= strlen(str);
		 if (  count_ != size_ )
		   count_ = std::accumulate(
       &str[1],&str[size_],count_,strategy_);
     return ( count_ == size_ );
   }
//**************************************************
//
//**************************************************
   struct 
   mail_to_strategy
   {
     enum 
     {MAIL_TO =1,MAIL_TO_INDEX};

     typedef 
       std::pair<  std::string , size_t > 
     type_pair;

     mail_to_strategy(std::string i_elem_):
      elem_(i_elem_){};

     void
     operator()(size_t counter_, 
      type_pair& mail_to_pair)
     {
       switch ( counter_ )
       {
         case MAIL_TO:
           mail_to_pair.first =  elem_;
         break;
         case MAIL_TO_INDEX: 
           if ( accum_( elem_.c_str() , digit_helper() ) )
             mail_to_pair.second = atol( elem_.c_str() );  
         break; 
         default:
         break;
       }
     }
   private:
     std::string elem_;
   };
//**************************************************
//
//**************************************************
   struct    
   smtp_strategy
   {
     enum 
     {
        DOMAIN =1,
        HOST,
        PORT,
        LOGIN,
        PASSWORD,
        LINKED_MAIL,
        CONN_METHOD
     };

     typedef 
       std::pair<  std::string , smtp_tuples > 
     type_pair;
     enum{MAX_CONN_CHR_NAME = 5};
     char conn_meth_arr
        [
          type_pair::second_type::METHODS_END
        ]
        [MAX_CONN_CHR_NAME];
    
     smtp_strategy(std::string i_elem_):
      elem_(i_elem_)
      {
        strcpy_s( conn_meth_arr[type_pair::second_type::PLAIN] , "PL");
        strcpy_s( conn_meth_arr[type_pair::second_type::STARTTLS] , "STLS" );        
      };
     
     void
     operator()(size_t counter_ , 
      type_pair& smtp_pair_)
     {
       switch ( counter_ )
       {
         case HOST: 
           smtp_pair_.second._host = elem_;
         break;
         case PORT: 
           if ( accum_( elem_.c_str() , digit_helper() ) )
             smtp_pair_.second._port = atoi( elem_.c_str() );
         break; 
         case DOMAIN: 
           smtp_pair_.first = elem_;
         break;
         case LOGIN:
           smtp_pair_.second._login = elem_;
           Func::base64_code( smtp_pair_.second._base64_login ,
		              elem_);
         break;
         case PASSWORD: 
           smtp_pair_.second._pass = elem_;
           Func::base64_code( smtp_pair_.second._base64_pass ,
		                elem_);
         break;
         case LINKED_MAIL:
           smtp_pair_.second._linked_mail = elem_; 
         break;
         case CONN_METHOD:
           smtp_pair_.second.conn_method = 
             type_pair::second_type::PLAIN; 
           for (
                size_t mtd_inc = 0;
                mtd_inc < type_pair::second_type::METHODS_END;
                ++mtd_inc               
              )
           {
             if (elem_.length()>5)
               break;
             if (!elem_.compare(conn_meth_arr[mtd_inc]))
             {
               smtp_pair_.second.conn_method = mtd_inc; 
               break;
             }
           }
         break;
         default:
         break;
       }
       smtp_pair_.second.ath_required =
       ( 
         (!smtp_pair_.second._base64_login.empty()) && 
         (!smtp_pair_.second._base64_pass.empty()) 
       );
       smtp_pair_.second.initialized = 
       (
         (!smtp_pair_.second._host.empty()) && 
         (!smtp_pair_.first.empty()) 
       );
     }
//**************************************************     
   private:
     std::string elem_;
   };
//**************************************************     
//
//
    template
    <
      typename 
      tuple_strategy = smtp_strategy
    >
	  struct char_analisator
	  {
      
      typedef 
       typename tuple_strategy::type_pair 
      type_pair;
//--------------------------------------------------------------------     
	    char_analisator
        (const char *str)
	    {
	      str_ = const_cast<char *>(str); 
	    }
//--------------------------------------------------------------------     
	    template
      <
        typename chr_analis_strategy
      >
	    bool 
      is_( chr_analis_strategy strategy_ ) const 
	    {
        return ( 
            accum_( const_cast<const char *>( str_ ) ,
                strategy_ 
              ) 
          );
	    }
//--------------------------------------------------------------------     
      type_pair
      get_tuples( char delimiter )
      {
        std::string elem_;
        type_pair tuple_pair_;
        bool while_init = false;
        bool eod = false;  //END OF DELIMITER 
        char *ptr_cursor = str_; 
        char *ptr_end = &str_[strlen (str_) ];
        char *ptr_prev = ptr_cursor;
        size_t counter_ = 1;
        while ( ptr_cursor++  != ptr_end ) 
        {      
          if ( !eod )
          {
            ptr_cursor =  std::find( ptr_cursor   , 
                       ptr_end    , delimiter );
            eod = ( ptr_cursor == ptr_end );
          }
          elem_.erase();
          elem_.insert( elem_.begin() , ptr_prev + while_init ,
              ptr_cursor );
          tuple_strategy strategy_(elem_);
          strategy_( counter_ , tuple_pair_ ); 
#ifdef DBG_PRINT_ON
          printf("test =%s\n counter = %d\n" ,elem_.c_str(),counter_ );
#endif
          ptr_prev = ptr_cursor;
          ++counter_;
          while_init = true;
        }
        return (  tuple_pair_  );
      }
//--------------------------------------------------------------------     
	  private:
      mutable char *str_;
		  char_analisator& operator=(char_analisator&);
		  char_analisator(char_analisator&);
	  };
//
//
//
	  template <typename T> 
	  struct tag_convertor_
	  {
	    const 
	    static 
	    T convert(char const *str)
	    {
        T t;
        while ((*str)!=0)
        {
          if (((*str)!='\r') && ((*str)!='\n'))         
            t += (*str);
          ++str;
        }
        return (t);
	    }
	  };
//
//
//
	  template <> 
	  struct tag_convertor_<int>
	  {
      const 
	    static
      int convert(const char *str)
	    {
        if ( !IsBadReadPtr(str,strlen(str)) )
		    {
	        char_analisator<> char_a(str);
           if (char_a.is_(digit_helper())) 
		      return (atoi(str));
		    }
	      return (-1);
	    }
	  };
//
//
    template <typename T>
    std::string 
    to_str(T unk_type_obj)
    {
      if(
          (typeid(T)!=typeid(unsigned short)) && 
          (typeid(T)!=typeid(size_t))         && 
          (typeid(T)!=typeid(short))          &&
          (typeid(T)!=typeid(const short))    &&
          (typeid(T)!=typeid(const int))      &&
          (typeid(T)!=typeid(const long))     &&
          (typeid(T)!=typeid(int))            &&
          (typeid(T)!=typeid(unsigned long))  &&
          (typeid(T)!=typeid(long))           &&
          (typeid(T)!=typeid(char *))         &&
          (typeid(T)!=typeid(const char *)) 
        )
        return (std::string(""));     
      char tmp[MAX_PATH];
      (
        typeid(T)==typeid(char *) ||
        typeid(T)==typeid(const char *) 
       )
      ?sprintf_s(tmp,"%s",unk_type_obj)
      :sprintf_s(tmp,"%d",unk_type_obj);
      return (std::string(tmp));
    }
//
//
	  template <> 
	  struct tag_convertor_<long>
	  {
      const 
	    static
      long convert(const char *str)
	    {
        size_t  size_ = strlen(str);
        if ( !IsBadReadPtr(str,size_) )
		    {
 		      char_analisator<> char_a(str);
          if (char_a.is_(digit_helper())) 
			      return (atol(str));
		    }
	      return (-1);
	    }
	  }; 
//--------------------------------------------------------------------   
	  template <> 
    struct tag_convertor_
    <  
      smtp_strategy::type_pair
    >
	  {
      const 
	    static
      smtp_strategy::type_pair
      convert(const char *str)
	    {
        smtp_strategy::type_pair pair_;
        size_t  size_ = strlen(str);
        if ( !IsBadReadPtr(str,size_) )
		    {
 		      char_analisator<> char_a(str);
          return ( char_a.get_tuples('/') ); 			      
		    }
        return (pair_);
	    }
	  }; 
//--------------------------------------------------------------------   
    template <> 
    struct tag_convertor_
    <  
      mail_to_strategy::type_pair
    >
	  {
      const 
	    static
      mail_to_strategy::type_pair
      convert(const char *str)
	    {
        mail_to_strategy::type_pair pair_;
        size_t  size_ = strlen(str);
        if ( !IsBadReadPtr(str,size_) )
		    {
 		      char_analisator
            <
              mail_to_strategy
            > char_a(str);
          return ( char_a.get_tuples('/') ); 			      
		    }
        return (pair_);
	    }
	  }; 
  };
};
#endif;
