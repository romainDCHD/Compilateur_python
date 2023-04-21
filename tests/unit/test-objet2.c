

#include "../include/pyas/all.h"


int main (void) {

  // list_t type = list_new();
  // // list_t list_del;
  // char* type_du_pyobj = malloc( sizeof( char ) );
  // *type_du_pyobj = PYOBJ_STRING;
  // type = list_add_last( type, type_du_pyobj );
  // char* type_du_pyobj2 = malloc( sizeof( char ) );
  // *type_du_pyobj2 = PYOBJ_STRING;
  // type = list_add_last( type, type_du_pyobj2 );
  // // list_del = type;
  // list_print(type, char_print_2);
  // list_delete(type, char_delete);

  char* string = "je manque de thunes";
  printf("%s\n",string );
  string = str_sans_guillemets(string);
  printf("%s\n",string );



  exit( EXIT_SUCCESS );


 //  lexem_t lexem_dir_set = lexem_new( "dir::set", ".set", 0, 0 );
 //  lexem_t lexem_skip_blank = lexem_new( "skip::blank", " ", 1, 0 );
 //  lexem_t lexem_filename = lexem_new( "set::filename", "nom_fichier", 0, 1 );
 //  lexem_t lexem_string = lexem_new( "string", "randomstring", 1, 1 );
 //  lexem_t lexem_string2 = lexem_new( "string", "randomstring2", 1, 1 );
 //  lexem_t lexem_comment = lexem_new( "skip::comment", "#random_comment", 1, 0 );
 //  lexem_t lexem_brack_left = lexem_new( "brack::left", "[", 0, 0 );
 //  lexem_t lexem_dir_consts = lexem_new( "dir::consts", "const", 0, 1 );
 //  lexem_t lexem_brack_right = lexem_new( "brack::right", "]", 1, 0 );
 //  lexem_t lexem_integer_dec = lexem_new( "integer::dec", "10", 1, 1 );
 //  lexem_t lexem_set_version_pyvm = lexem_new( "set::version_pyvm", "version_pyvm", 0, 1 );
 //  lexem_t lexem_set_name = lexem_new( "set::name", "name", 0, 1 );
 //  lexem_t lexem_dir_interned = lexem_new( "dir::interned", "intern", 0, 0 );
 //  lexem_t lexem_integer_hex = lexem_new( "integer::hex", "10", 0, 0 );
 //  lexem_t lexem_number_float = lexem_new( "number::float", "10.95", 0, 0 );
 //  lexem_t lexem_complex_float = lexem_new( "complex::float", "10", 0, 0 );
 //  lexem_t lexem_paren_left = lexem_new( "paren::left", "(", 0, 0 );
 //  lexem_t lexem_paren_right = lexem_new( "paren::right", ")", 1, 0 );
 //  lexem_t lexem_dir_varnames = lexem_new( "dir::varnames", "nom", 0, 0 );
 //  lexem_t lexem_dir_names = lexem_new( "dir::names", "nom", 0, 0 );
 //  lexem_t lexem_dir_freevars = lexem_new( "dir::freevars", "freevars", 0, 0 );
 //  lexem_t lexem_dir_cellvars = lexem_new( "dir::cellvars", "cellvars", 0, 0 );
 //  lexem_t lexem_symbol = lexem_new( "symbol", "+", 0, 0 );
 //  lexem_t lexem_colon = lexem_new( "colon", ":", 0, 1 );
 //  lexem_t lexem_dir_line = lexem_new( "dir::line", "\n", 0, 0 );
 //  lexem_t lexem_insn_0 = lexem_new( "insn::0", "STOP_CODE", 0, 0 );
 //  lexem_t lexem_insn_1 = lexem_new( "insn::1", "DELETE_NAME", 0, 0 );
 //  lexem_t lexem_skip_comment = lexem_new( "skip::comment", "#k", 1, 1 );
 //  lexem_t lexem_newline = lexem_new( "newline", "/n", 0, 1 );
 //  lexem_t lexem_source_size = lexem_new( "set::source_size", "10", 0, 1 );
 //  lexem_t lexem_stack_size = lexem_new( "set::stack_size", "11", 0, 1 );
 //  lexem_t lexem_arg_count = lexem_new( "set::arg_count", "5", 0, 1 );
 //  lexem_t lexem_posonly_arg_count = lexem_new( "set::posonly_arg_count", "5", 0, 1 );
 //  lexem_t lexem_kwonly_arg_count = lexem_new( "set::kwonly_arg_count", "5", 0, 1 );
 //  lexem_t lexem_set_flags= lexem_new( "set::flags", "flags", 0, 1 );
 //  lexem_t lexem_dir_text=lexem_new( "dir::text", "filename", 0, 1 );
 //  lexem_t lexem_pycst=lexem_new( "pycst", "None", 0, 1 );
 //
 // list_t list = list_new();
 // int i = 0;
 // py_codeblock codeblock = codeblock_new();
 //
 // // //〈interned-strings〉 : := {‘dir::interned’} 〈eol〉 ( {‘string’} 〈eol〉 )*
 // // list = list_add_last (list, lexem_dir_interned);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_string);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_string);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_string2);
 // // list = list_add_last (list, lexem_newline);
 //
 // // // 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
 // // list = list_add_last (list, lexem_dir_set);
 // // list = list_add_last (list, lexem_skip_blank);
 // // list = list_add_last (list, lexem_set_name);
 // // list = list_add_last (list, lexem_skip_blank);
 // // list = list_add_last (list, lexem_string);
 // // list = list_add_last (list, lexem_newline);
 //
 // // 〈set-stack-size〉 : := {‘dir::set’} {‘blank’} {‘stack_size’} {‘blank’}{‘integer::dec’} 〈eol〉
 // // list = list_add_last (list, lexem_dir_set);
 // // list = list_add_last (list, lexem_skip_blank);
 // // list = list_add_last (list, lexem_stack_size);
 // // list = list_add_last (list, lexem_skip_blank);
 // // list = list_add_last (list, lexem_integer_dec);
 // // list = list_add_last (list, lexem_newline);
 //
 // // 〈names〉 : := {‘dir::names’} 〈eol〉 ( {‘string’} 〈eol〉 )*
 // // list = list_add_last (list, lexem_dir_names);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_string);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_skip_blank);
 // // list = list_add_last (list, lexem_string);
 // // list = list_add_last (list, lexem_newline);
 //
 // // 〈constants〉 : := {‘dir::consts’} 〈eol〉 ( 〈constant〉 〈eol〉 )*
 // // list = list_add_last (list, lexem_dir_consts);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_integer_hex);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_string);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_pycst);
 // // list = list_add_last (list, lexem_newline);
 // // list = list_add_last (list, lexem_number_float);
 // // list = list_add_last (list, lexem_newline);
 //
 // // 〈set-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘arg_count’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
 // list = list_add_last (list, lexem_dir_set);
 // list = list_add_last (list, lexem_skip_blank);
 // list = list_add_last (list, lexem_arg_count);
 // list = list_add_last (list, lexem_skip_blank);
 // list = list_add_last (list, lexem_integer_dec);
 // list = list_add_last (list, lexem_newline);
 //
 // list_t* lexems = &list;
 // list_print (list, lexem_print);
 //
 // i = fill_set_arg_count ( lexems, &codeblock );
 // if (i == 0)
 // {
 //   print_codeblock (codeblock);
 //   printf("detection ok\n");
 //   codeblock_delete(codeblock);
 //   exit( EXIT_SUCCESS );
 // }
 //
 // else
 // {
 //   print_codeblock (codeblock);
 //   printf("detection fail\n");
 //   codeblock_delete(codeblock);
 //   exit( EXIT_FAILURE );
 // }
}
