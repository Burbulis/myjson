// parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "get_document.h"
#include "stdio.h"
#include <sstream>
#define DEBUG //убрать после отладки.
int main(int argc, char* argv[])
{
   Parser::ParseTemplate parser;
    /*
     ƒанные парсинга будут находитьс€ в структуре metadata.
     Parser::meta_data_type metadata = parser.get_metadata();
      оторую возвращает соответствующий метод класса ParseTemplate.
     —труктура определена в заголовочном файле tag_types.h.
    */
  //if (argc<2)
	//{
  //  MessageBox(NULL,"usage: parser.exe test.xml","debug_error",NULL);
  //  return (-1);
//	}
  FILE *f = fopen("test.xml","rb");
	
	if (!f)
      return (-1);
	
	unsigned long times_first = GetTickCount();
	  //-----------------------------------------------------------
	fseek(f,0,SEEK_END);
	long buffer_size = ftell(f) + 1;
	fseek(f,0,SEEK_SET);
	char *Test = new char[buffer_size]; 
	fread(Test,buffer_size,1,f);
	fclose(f); 
	parser.init_by_buffer(Test,buffer_size);
	delete [] Test;
	Parser::meta_data_type metadata = parser.get_metadata();
      //------------------------------------------------------------
	unsigned long times_last = GetTickCount();

	std::ostringstream time_str;
  time_str << "time_first =" << times_first << " time_last =" 
	<< times_last << " differene =" <<  times_last - times_first << '\n';

	MessageBox(NULL,time_str.str().c_str(),"current parsing time",NULL);

	#ifdef DEBUG
	for (int i =0;i<Parser::meta_data_type::ELEMENT_COUNT;i++)
	{
	  if (metadata[i])
		{
      if ( Parser::type_tags::MX_BAD_COUNT == i )
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.mx_bad_count << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
      }
      if (Parser::type_tags::THREADS == i)
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.threads << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

      if (Parser::type_tags::TID == i)
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.tid << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

		  if (Parser::type_tags::TIMEOUT_SEND_RECV==i)
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.timeout << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

		  if (Parser::type_tags::CHARSET==i)
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.charset << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

		  if (Parser::type_tags::SLEEP==i)
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.sleep << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

		  if (Parser::type_tags::MX_CACHE==i)
		  {
	      std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.mxcache << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }
      if (Parser::type_tags::RANDOMIZATION_LEVEL==i)
		  {
        std::ostringstream strs;
	      strs << Parser::tags_argv[i-1] << ":" << metadata.rand_level << '\n'; 
	      MessageBox(NULL,strs.str().c_str(),"debug",NULL);
      }
      if (Parser::type_tags::MAIL_FROM==i)
		  {
	      std::ostringstream strs;
		    Parser::t_mail_from::getType::iterator first = metadata.mail_from.begin();
		    Parser::t_mail_from::getType::iterator last  = metadata.mail_from.end();
		    while (first!=last)
	           strs << Parser::tags_argv[i-1] << ":" << (*first++).c_str() << '\n'; 
        MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

		  if (Parser::type_tags::MAIL_TO==i)
		  {
	      std::ostringstream strs;
		    Parser::t_mail_to::getType::iterator first = metadata.mail_to.begin();
		    Parser::t_mail_to::getType::iterator last  = metadata.mail_to.end();
		    while (first!=last)
        {
          strs << Parser::tags_argv[i-1] << ":" << (*first).first << ":" << (*first).second << '\n'; 
          ++first;
        }
        MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

		  if (Parser::type_tags::SMTP_SERVERS==i)
		  {
	      std::ostringstream strs;
        Parser::t_smtp_servers::getType::iterator first = metadata.smtp_servers.begin();
 	      Parser::t_smtp_servers::getType::iterator last  = metadata.smtp_servers.end();
	      while  (first!=last)
		    {
          strs << Parser::tags_argv[i-1] << ":" << (*first).first << ":"  << (*first).second._port<< ":" << (*first).second.conn_method <<'\n';
		      ++first;
        }
        MessageBox(NULL,strs.str().c_str(),"debug",NULL);
		  }

      if (Parser::type_tags::BODY_MAIL_MACROS == i)
      {
	      std::ostringstream strs;
        Parser::t_body_macros ::getType::iterator first = metadata.body_macros.begin();
		    Parser::t_body_macros ::getType::iterator last  = metadata.body_macros.end();
	      while  (first!=last)
		    {
		      strs << Parser::tags_argv[i-1] << ":" <<  (*first) << '\n';
			    ++first;
			  }
        MessageBox(NULL,strs.str().c_str(),"mail_macro",NULL);
      }
		  if (Parser::type_tags::BODY==i)
		  {
        for (long m_count = 0 ;m_count < Parser::t_body::get_count();++m_count)
			  {
  	      std::ostringstream strs;
          Parser::t_body::getType::iterator first = metadata.body.find(m_count);
		      Parser::t_body::getType::iterator last  = metadata.body.end();
	        while  (first!=last)
			    {
			      if ( (*first).first == m_count)
			         strs << Parser::tags_argv[i-1] << ":" << m_count << ":" << (*first).second << '\n';
			      ++first;
			    }
          MessageBox(NULL,strs.str().c_str(),"body",NULL);
        }
      }


      if (Parser::type_tags::HEADER==i)
		  {
        std::ostringstream strs;
        for (long m_count = 0 ;m_count < Parser::t_header::get_count();++m_count)
			  {
		      Parser::t_header::getType::iterator first = metadata.header.find(m_count);
		      Parser::t_header::getType::iterator last  = metadata.header.end();
	        while  (first!=last)
			    {
			      if ( (*first).first == m_count)
			       strs << Parser::tags_argv[i-1] << ":" << m_count << ":" <<(*first).second << '\n';
			      ++first;
			    }
			  }
		 MessageBox(NULL,strs.str().c_str(),"header",NULL);          
      }
    }
  }
  #endif;
	return 0;
}
