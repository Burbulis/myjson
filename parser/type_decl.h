#ifndef TypeDeclarationH
#define TypeDeclarationH

namespace Parser
{

  struct type_tags
  {
    enum 
    {
	    NONE = 0,TID , THREADS , TIMEOUT_SEND_RECV , SLEEP , 
	    MX_CACHE , REPORT_FREQUENCY , LETTER_FORMAT ,
	    CHARSET , MAIL_FROM , MAIL_TO , SMTP_SERVERS ,
      BODY, HEADER , HEADER_MAIL_MACROS , BODY_MAIL_MACROS ,
      MX_BAD_COUNT , BOT_ID,BOT_AUTH , HAVE_TASK , BOT_ID_EXIST,
      BOT_ERROR , BOT_SERVER_DOMAIN,BOT_SERVER_CMD,BOT_UPD_DOMAIN,
      BOT_UPD_PATH,MAIL_SUBJECT,RANDOMIZATION_LEVEL,
      LINKS_ROTATE_LIST,
      LINKS_XCHG_COUNT,
      /***/
      END_OF_ENUM
    };

	  enum
    {
      SINGLE = 0,MULTIPLE = 1,COUNTED =2  
    };

  };

  struct cnull
  {};

  const int tags_count = (type_tags::END_OF_ENUM - 1);    
  enum{first_tag,last_tag}; 

};
#endif