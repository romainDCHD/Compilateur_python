
#include "../include/pyas/all.h"


int main ( void ) {

  list_t list = list_new();
  list_t list_save; //pour liberer la memoire


  py_codeblock* codeblock = codeblock_new();

  lexem_t lexem_dir_set = lexem_new( "dir::set", ".set", 0, 0 );
  lexem_t lexem_skip_blank = lexem_new( "skip::blank", " ", 1, 0 );
  lexem_t lexem_filename = lexem_new( "set::filename", "nom_fichier", 0, 1 );
  lexem_t lexem_string = lexem_new( "string", "randomstring", 1, 1 );
  lexem_t lexem_comment = lexem_new( "skip::comment", "#random_comment", 1, 0 );
  lexem_t lexem_dir_consts = lexem_new( "dir::consts", "const", 0, 1 );
  lexem_t lexem_integer_dec = lexem_new( "integer::dec", "26", 1, 1 );
  lexem_t lexem_set_version_pyvm = lexem_new( "set::version_pyvm", "version_pyvm", 0, 1 );
  lexem_t lexem_set_name = lexem_new( "set::name", "name", 0, 1 );
  lexem_t lexem_dir_interned = lexem_new( "dir::interned", "intern", 0, 0 );
  lexem_t lexem_integer_hex = lexem_new( "integer::hex", "84", 0, 0 );
  lexem_t lexem_dir_varnames = lexem_new( "dir::varnames", "nom", 0, 0 );
  lexem_t lexem_dir_names = lexem_new( "dir::names", "nom", 0, 0 );
  lexem_t lexem_dir_freevars = lexem_new( "dir::freevars", "freevars", 0, 0 );
  lexem_t lexem_dir_cellvars = lexem_new( "dir::cellvars", "cellvars", 0, 0 );
  lexem_t lexem_dir_line = lexem_new( "dir::line", "\n", 0, 0 );
  lexem_t lexem_insn_0 = lexem_new( "insn::0", "STOP_CODE", 0, 0 );
  lexem_t lexem_newline = lexem_new( "newline", "/n", 0, 1 );
  lexem_t lexem_source_size = lexem_new( "set::source_size", "10", 0, 1 );
  lexem_t lexem_stack_size = lexem_new( "set::stack_size", "11", 0, 1 );
  lexem_t lexem_arg_count = lexem_new( "set::arg_count", "5", 0, 1 );
  lexem_t lexem_posonly_arg_count = lexem_new( "set::posonly_arg_count", "5", 0, 1 );
  lexem_t lexem_kwonly_arg_count = lexem_new( "set::kwonly_arg_count", "5", 0, 1 );
  lexem_t lexem_set_flags= lexem_new( "set::flags", "flags", 0, 1 );
  lexem_t lexem_dir_text=lexem_new( "dir::text", "filename", 0, 1 );

  lexem_t lexem_pycst=lexem_new( "pycst", "None", 0, 1 );
  lexem_t lexem_number_float = lexem_new( "number::float", "49", 0, 0 );
  lexem_t lexem_complex_float = lexem_new( "complex::float", "10", 0, 0 );
  lexem_t lexem_paren_left = lexem_new( "paren::left", "(", 0, 0 );
  lexem_t lexem_paren_right = lexem_new( "paren::right", ")", 1, 0 );
  lexem_t lexem_insn_1 = lexem_new( "insn::1", "DELETE_NAME", 0, 0 );
  lexem_t lexem_skip_comment = lexem_new( "skip::comment", "#k", 1, 1 );
  lexem_t lexem_symbol = lexem_new( "symbol", "+", 0, 0 );
  lexem_t lexem_colon = lexem_new( "colon", ":", 0, 1 );
  lexem_t lexem_brack_right = lexem_new( "brack::right", "]", 1, 0 );
  lexem_t lexem_brack_left = lexem_new( "brack::left", "[", 0, 0 );

 //TEST PYS
 // <pys> : := <eol>* <prologue> <code>
 //eol
 list = list_add_last (list, lexem_newline);

 //PORLOGUE
 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_set_version_pyvm);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_set_flags);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_hex);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_filename);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_comment);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_set_name);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_comment);
 list = list_add_last (list, lexem_newline);

 //parse_set_source_size
 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_source_size);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_skip_blank);

 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_stack_size);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_arg_count);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_newline);

 //[set-kwonly-arg-count]
 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_kwonly_arg_count);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);

 //[set-posonly-arg-count]
 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_posonly_arg_count);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_dir_interned);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);

 //CONSTANSTS
 list = list_add_last (list, lexem_dir_consts);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_newline);

 //names
 list = list_add_last (list, lexem_dir_names);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);

 //parse_varnames
 list = list_add_last (list, lexem_dir_varnames);
 // list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);

 //freevars
 list = list_add_last (list, lexem_dir_freevars);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);

 //parse_cellvars
 list = list_add_last (list, lexem_dir_cellvars);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);
 list = list_add_last (list, lexem_string);
 list = list_add_last (list, lexem_newline);

 //CODE
 list = list_add_last (list, lexem_dir_text);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_dir_line);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);

 list = list_add_last (list, lexem_insn_0);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_newline);

 list_save = list;
 list_t* lexems = &list;



  if (fill_pys( lexems, codeblock ) == 0)
  {
    list_delete(list_save, NULL);
    lexem_delete( lexem_dir_set  );
    lexem_delete( lexem_skip_blank );
    lexem_delete( lexem_filename  );
    lexem_delete( lexem_string );
    lexem_delete( lexem_comment );
    lexem_delete( lexem_brack_left );
    lexem_delete( lexem_dir_consts  );
    lexem_delete( lexem_brack_right );
    lexem_delete( lexem_integer_dec );
    lexem_delete( lexem_set_version_pyvm );
    lexem_delete( lexem_set_name );
    lexem_delete( lexem_dir_interned );
    lexem_delete( lexem_integer_hex  );
    lexem_delete( lexem_number_float  );
    lexem_delete( lexem_complex_float  );
    lexem_delete( lexem_paren_left );
    lexem_delete( lexem_paren_right  );
    lexem_delete( lexem_dir_varnames  );
    lexem_delete( lexem_dir_names );
    lexem_delete( lexem_dir_freevars);
    lexem_delete( lexem_dir_cellvars );
    lexem_delete( lexem_symbol  );
    lexem_delete( lexem_colon  );
    lexem_delete( lexem_dir_line );
    lexem_delete( lexem_insn_0  );
    lexem_delete( lexem_insn_1  );
    lexem_delete( lexem_skip_comment);
    lexem_delete( lexem_newline);
    lexem_delete( lexem_source_size );
    lexem_delete( lexem_stack_size );
    lexem_delete( lexem_arg_count );
    lexem_delete( lexem_posonly_arg_count);
    lexem_delete( lexem_kwonly_arg_count);
    lexem_delete( lexem_set_flags);
    lexem_delete( lexem_dir_text);
    lexem_delete( lexem_pycst);

    printf("end of function\n");
    print_pyobj( codeblock->binary.trailer.name );

    print_codeblock (codeblock);
    printf("detection ok\n");
    codeblock_delete(codeblock);

    exit( EXIT_SUCCESS );
  }

  else
  {
    list_delete(list_save, NULL);
    lexem_delete( lexem_dir_set  );
    lexem_delete( lexem_skip_blank );
    lexem_delete( lexem_filename  );
    lexem_delete( lexem_string );
    lexem_delete( lexem_comment );
    lexem_delete( lexem_brack_left );
    lexem_delete( lexem_dir_consts  );
    lexem_delete( lexem_brack_right );
    lexem_delete( lexem_integer_dec );
    lexem_delete( lexem_set_version_pyvm );
    lexem_delete( lexem_set_name );
    lexem_delete( lexem_dir_interned );
    lexem_delete( lexem_integer_hex  );
    lexem_delete( lexem_number_float  );
    lexem_delete( lexem_complex_float  );
    lexem_delete( lexem_paren_left );
    lexem_delete( lexem_paren_right  );
    lexem_delete( lexem_dir_varnames  );
    lexem_delete( lexem_dir_names );
    lexem_delete( lexem_dir_freevars);
    lexem_delete( lexem_dir_cellvars );
    lexem_delete( lexem_symbol  );
    lexem_delete( lexem_colon  );
    lexem_delete( lexem_dir_line );
    lexem_delete( lexem_insn_0  );
    lexem_delete( lexem_insn_1  );
    lexem_delete( lexem_skip_comment);
    lexem_delete( lexem_newline);
    lexem_delete( lexem_source_size );
    lexem_delete( lexem_stack_size );
    lexem_delete( lexem_arg_count );
    lexem_delete( lexem_posonly_arg_count);
    lexem_delete( lexem_kwonly_arg_count);
    lexem_delete( lexem_set_flags);
    lexem_delete( lexem_dir_text);
    lexem_delete( lexem_pycst);


    print_codeblock (codeblock);
    printf("detection fail\n");
    codeblock_delete(codeblock);
    exit( EXIT_FAILURE );
  }
}
