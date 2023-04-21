


#ifndef _LEXER_H
#define _LEXER_H

#ifdef __cplusplus
extern "C" {
#endif
;
 typedef int (*action_t)( void * );



  void init_word (char* word);
  list_t find_regexp(char* name_data_base, char* file_name);

#ifdef __cplusplus
}
#endif

#endif /* _LEXER_H*/
