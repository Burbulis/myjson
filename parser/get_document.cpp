#include "stdafx.h"
#include "get_document.h"
#include "type_selector.h"
#include "type_decl.h"
#include <cstdlib>
#include <typeinfo>
#include <list>


namespace Parser
{
  extern  const int tags_count;
  extern  const char *tags_argv[tags_count];
  extern  const char *tags_argv_fini[tags_count];
  extern  unsigned int is_sub_type[tags_count+1];
  extern  const char *token;
  extern  const char *end_of_file_token;
  long Parser::t_body::count;
  long Parser::t_header::count;
  //-----------------------------------------------------------------------  
  ParseTemplate::
  ParseTemplate()
  {
    for (size_t i = 0; i < tags_count;++i)
    {
	    tag_size_cache[i] = strlen(tags_argv[i]);
	    tag_size_cache_fini[i] = strlen(tags_argv_fini[i]);
    }
  }
  //-----------------------------------------------------------------------  
  inline
  char *ParseTemplate:: // замена memcmp 
	  mem_test(char *byte_buffer,
	  char *tag_buffer,size_t tag_size)
  {
	  unsigned long  is_not_equal = 0;
	  __asm
    {
	    mov ecx,tag_size
 	    mov esi,tag_buffer
      mov edi,byte_buffer
      cld
	    repe cmpsb
	    mov is_not_equal,ecx
 	  }

	  if (!is_not_equal)
		   return (byte_buffer + tag_size);

    return (NULL);
  }
//-----------------------------------------------------------------------  
  inline 
  char *ParseTemplate::
  tagSelector(int tag_pos,int tag_index)
  {
    /*
     Этот селектор можно было сделать полной специализацией метода-шаблона 
	   с нешаблонным параметром.
     Но к сожалению у меня MSVC6. :-( Поэтому пришлось делать ТУПО:-(
    */
    char *tag_ =NULL;
    switch (tag_pos)
	  {
	    
	    case first_tag: 
  	    tag_ = const_cast<char *>(tags_argv[tag_index]);
	      tagPair.first_tag = tag_;  
	    break;

	    case last_tag:
	      tag_ = const_cast<char *>(tags_argv_fini[tag_index]);
	      tagPair.last_tag = tag_;
	    break;	
		  
      default:
        tag_ = NULL;		  
	      tagPair.last_tag = tag_;
	      tagPair.first_tag = tag_;  
  	  break;
	  }    
	  return (tag_);
  }
//-----------------------------------------------------------------------  
  inline
  void ParseTemplate::
  tagInitValue(int tag_index)
  {
    if (tag_index<tags_count)
	  {
 	    tagPair.first_tag = const_cast<char *>(tags_argv[tag_index]);  
	    tagPair.fist_size = tag_size_cache[tag_index];//strlen (tags_argv[tag_index]);
	    tagPair.last_tag  = const_cast<char *>(tags_argv_fini[tag_index]);
      tagPair.last_size = tag_size_cache_fini[tag_index];
	    tagPair.tag_index = tag_index + 1;
	  }
  }
//
  inline
  bool ParseTemplate::
  end_of_doc_found(char *byte_buffer,size_t buffer_sz)
  {      
    char *mem_test_ptr = 
     (buffer_sz >= strlen(end_of_file_token))
     ?mem_test( 
        byte_buffer , 
        const_cast<char *>(end_of_file_token) , 
        strlen(end_of_file_token) 
      )
     :NULL;
    return (mem_test_ptr?true:true);
  }
//-----------------------------------------------------------------------  
  inline
  char *ParseTemplate::
  is_tag_ptr(char *byte_buffer,
      size_t sz_buffer,int tag_pos
    )
  {
	  for (long tag_count=0;tag_count<tags_count;++tag_count)
	  { 	  
      char *tag_ = tagSelector(tag_pos,tag_count);
     
	    if ( !tag_ ) // impossible error -continue 
		    continue;     
	  
	    char *mem_test_ptr = NULL; 
      if (tag_pos)
      {
         if (sz_buffer >= tag_size_cache_fini[tag_count])      
         mem_test_ptr = mem_test( byte_buffer ,
             tag_ , tag_size_cache_fini[tag_count]   
          );
      }       
      else
      {
        if (sz_buffer >= tag_size_cache[tag_count])
        {
          mem_test_ptr = mem_test( byte_buffer ,
               tag_ , tag_size_cache[tag_count] 
            );
        }
      }
	    if (mem_test_ptr)
	    {
	      tagInitValue(tag_count);
		    return (mem_test_ptr);
	    }
	  }
    return (NULL);
  }
//-------------------------------------------------------------------------  
  bool 
  ParseTemplate::
  init_by_buffer( const char *init_buffer , size_t size )
  {
    return(
      init_by_buffer(
         const_cast<char *>(init_buffer) , size )
         );  
  }
//-------------------------------------------------------------------------  
  bool 
  ParseTemplate::
  init_by_buffer( char *init_buffer , size_t size )
  {
    if ( IsBadReadPtr(init_buffer,size) )
	  return(false);	
	//
    bool end_doc_found = false;
    size_t count = 0;
    p_str = "";
    bool read_to_str = false; 
    tagPair.first_tag = NULL;
	  tagPair.last_tag = NULL;
    // 
	  while (count < size)
   	{
      //
	  // Проверяем , найден ли первый тэг. если найден 
	  //  установим флаг read_to_str = true и расчитаем 
    //  его длинну поместив её в count.
      unsigned long  not_token_ = 0;
	    __asm //сравнение токена с init_buffer ка машинного слова
      {       
 	      mov esi,token
        mov edi,init_buffer
		    add edi,count
        xor eax,eax
		    xor ebx,ebx
		    mov ax,word ptr [esi]
		    mov bx,word ptr [edi] 
        xor ax,bx // "сравнение" xor-ом. 
		    mov not_token_,eax
      }
	  
	    char *first_tag_ptr = NULL; 
	    char *last_tag_ptr  = NULL;
	    if ( !not_token_ )//оптимизация с помощью 
        //предварительного поиска тэга	          
      {
        size_t sz_diff_count = size - count; 
        end_doc_found =
          end_of_doc_found(&init_buffer[count],sz_diff_count);
        first_tag_ptr = is_tag_ptr(&init_buffer[count],
          sz_diff_count , first_tag );
        (first_tag_ptr)?read_to_str = true,
          count = first_tag_ptr - init_buffer :count;
	  // Аналогично , последний тэг. если найден 
	  //  установим флаг read_to_str = false и расчитаем его длинну поместив её в count.
        last_tag_ptr = is_tag_ptr(&init_buffer[count],
            sz_diff_count , last_tag
          );
        (last_tag_ptr)?read_to_str = false,
          count = last_tag_ptr - init_buffer :count;
      }

	    if ( read_to_str )
      {
        if ( ( 0x0A != init_buffer[count] ) && 
			     ( 0x0D != init_buffer[count] ) ) 
	  	     p_str += init_buffer[count];
		    else  
 	      init_metadata();
      }
	    else if ( last_tag_ptr   )
      {
        bool result_ = (type_tags::COUNTED == is_sub_type[tagPair.tag_index]);
		    init_metadata( result_ );
      }
	    ++count;
    }
    return ( end_doc_found );
  }
//------------------------------------------------------------------------------
  const meta_data_type& 
  ParseTemplate::
  get_metadata(void) const
  {
    return (metadata);
  }
//------------------------------------------------------------------------------
  inline
  void
  ParseTemplate::
  init_metadata(bool increment_)
  {  
    if ( (!p_str.empty()) || (increment_) )
    {
      if ( (!metadata[tagPair.tag_index]) || (is_sub_type[tagPair.tag_index]) )
      {
		    TagTypeSelector selector(tagPair.tag_index);//задаём индекс типа
		    selector.getMetadata(p_str,metadata,increment_);//получаем метаданные  
      }
    }
    p_str.erase();
  }
//------------------------------------------------------------------------------- 
/*end of namespace*/
}
