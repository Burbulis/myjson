#include "stdafx.h"
#include "type_decl.h"

namespace Parser
{ 
  const char *tags_argv[tags_count] =
  {
	  {"###TID###"},
	  {"###THREADS###"},
	  {"###TIMEOUT_SEND_RECV###"},
	  {"###SLEEP###"},
	  {"###MX_CACHE###"},
	  {"###REPORT_FREQUENCY###"},
	  {"###LETTER_FORMAT###"},
	  {"###CHARSET###"},
	  {"###MAIL_FROM###"},
	  {"###MAIL_TO###"},
    {"###SMTP###"},
	  {"###BODY###"},
	  {"###HEADER###"},
	  {"###HEADER_MAIL_MACROS###"},
	  {"###BODY_MAIL_MACROS###"},
    {"###MX_BAD_MAXCOUNT###"},
    {"###BOT_ID###"},
    {"###BOT_AUTH###"},
    {"###HAVE_TASK###"},
    {"###BOT_ID_EXIST###"},
    {"###ERROR###"},
    {"###SERVER_DOMAIN###"},
    {"###SERVER_COMMAND###"},
    {"###BOT_UPDATE_DOMAIN###"},
    {"###BOT_UPDATE_PATH###"},
    {"###SUBJECT###"},
    {"###RANDOMIZATION_LEVEL###"},
    {"###LINKS_ROTATE_LIST###"},
    {"###LINKS_XCHG_COUNT###"}
  };

   const char *tags_argv_fini[tags_count] =
   {
	  {"###TID_END###"},
	  {"###THREADS_END###"},
	  {"###TIMEOUT_SEND_RECV_END###"},
	  {"###SLEEP_END###"},
	  {"###MX_CACHE_END###"},
	  {"###REPORT_FREQUENCY_END###"},
	  {"###LETTER_FORMAT_END###"},
	  {"###CHARSET_END###"},
	  {"###MAIL_FROM_END###"},
    {"###MAIL_TO_END###"},
	  {"###SMTP_END###"},
    {"###BODY_END###"},
	  {"###HEADER_END###"},
	  {"###HEADER_MAIL_MACROS_END###"},
	  {"###BODY_MAIL_MACROS_END###"},
    {"###MX_BAD_MAXCOUNT_END###"},
    {"###BOT_ID_END###"},
    {"###BOT_AUTH_END###"},
    {"###HAVE_TASK_END###"},
    {"###BOT_ID_EXIST_END###"},
    {"###ERROR_END###"},
    {"###SERVER_DOMAIN_END###"},
    {"###SERVER_COMMAND_END###"},
    {"###BOT_UPDATE_DOMAIN_END###"},
    {"###BOT_UPDATE_PATH_END###"},
    {"###SUBJECT_END###"},
    {"###RANDOMIZATION_LEVEL_END###"},
    {"###LINKS_ROTATE_LIST_END###"},
    {"###LINKS_XCHG_COUNT_END###"}
   };   
  const char *token="##";
  const char *end_of_file_token="###TRANSMISSION_END###\0";
  unsigned int is_sub_type[tags_count+1];
   

}