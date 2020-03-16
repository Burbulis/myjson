#ifndef GetDocumentH
#define GetDocumentH
#include "stdafx.h"
#include <cstdlib>
#include "windows.h"
#include <list>
#include "type_selector.h" 
namespace Parser
{
  class ParseTemplate
  {

  
  public:
	  ParseTemplate::ParseTemplate();
    bool init_by_buffer( char *init_buffer , size_t size );
    bool init_by_buffer( const char *init_buffer , size_t size );
    const meta_data_type& get_metadata(void) const;
  
  private:
 
	/*
      Структура для хренения пары тэгов.
      открывающего  и закрывающего.
    */
    meta_data_type metadata;
    size_t tag_size_cache[tags_count];
	  size_t tag_size_cache_fini[tags_count];
	  struct type_tagPair
	  {  
	    char *first_tag;
	    int   fist_size;  
	    char *last_tag;
	    int   last_size; 
      unsigned int tag_index; 
	    type_tagPair():first_tag(NULL),last_tag(NULL),
                fist_size(0),last_size(0),tag_index(0)
	    {                                               };

	  }tagPair;

   	std::string p_str;
	  void init_metadata(bool increment_ = false);
    bool
    end_of_doc_found(char *byte_buffer,size_t buffer_sz);

    char *mem_test(char *byte_buffer,char *tag_buffer,size_t tag_size);
    char *is_tag_ptr(char *byte_buffer,
      size_t sz_buffer,int tag_pos
    );
    char *tagSelector(int tag_pos,int tag_index);
    void  tagInitValue(int tag_index);
  };
  /* end of namespace */
}

#endif