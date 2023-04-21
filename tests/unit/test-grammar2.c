//fonction a tester

#include "../include/pyas/all.h"


int main ( void) {

//   // lexem_t lexem1 = lexem_new( "dir::set", ".set", 0, 0 );
//   // lexem_t lexem2 = lexem_new( "skip::blank", " ", 1, 0 );
//   // lexem_t lexem3 = lexem_new( "filename", "nom_fichier", 0, 1 );
//   // lexem_t lexem4 = lexem_new( "string", "random_string", 1, 1 );
//   // lexem_t lexem5 = lexem_new( "skip::comment", "random_comment", 1, 0 );
//   // lexem_t lexem6 = lexem_new( "brack::left", "[", 0, 0 );
//   // lexem_t lexem8 = lexem_new( "dir::consts", "const", 0, 1 );
//   // lexem_t lexem9 = lexem_new( "brack::right", "]", 1, 0 );
//
//   lexem_t lexem_dir_set = lexem_new( "dir::set", ".set", 0, 0 );
//   lexem_t lexem_skip_blank = lexem_new( "skip::blank", " ", 1, 0 );
//   lexem_t lexem_filename = lexem_new( "filename", "nom_fichier", 0, 1 );
//   lexem_t lexem_string = lexem_new( "string", "randomstring", 1, 1 );
//   lexem_t lexem_comment = lexem_new( "skip::comment", "#random_comment", 1, 0 );
//   lexem_t lexem_brack_left = lexem_new( "brack::left", "[", 0, 0 );
//   lexem_t lexem_dir_consts = lexem_new( "dir::consts", "const", 0, 1 );
//   lexem_t lexem_brack_right = lexem_new( "brack::right", "]", 1, 0 );
//   lexem_t lexem_integer_dec = lexem_new( "integer::dec", "10", 1, 1 );
//   lexem_t lexem_set_version_pyvm = lexem_new( "set::version_pyvm", "version_pyvm", 0, 1 );
//   lexem_t lexem_set_name = lexem_new( "set::name", "name", 0, 1 );
//   lexem_t lexem_dir_interned = lexem_new( "dir::interned", "intern", 0, 0 );
//   lexem_t lexem_integer_hex = lexem_new( "integer::hex", "10", 0, 0 );
//   lexem_t lexem_number_float = lexem_new( "number::float", "10", 0, 0 );
//   lexem_t lexem_complex_float = lexem_new( "complex::float", "10", 0, 0 );
//   lexem_t lexem_paren_left = lexem_new( "paren::left", "(", 0, 0 );
//   lexem_t lexem_paren_right = lexem_new( "paren::right", ")", 1, 0 );
//   lexem_t lexem_dir_varnames = lexem_new( "dir::varnames", "nom", 0, 0 );
//   lexem_t lexem_dir_names = lexem_new( "dir::names", "nom", 0, 0 );
//   lexem_t lexem_dir_freevars = lexem_new( "dir::freevars", "freevars", 0, 0 );
//   lexem_t lexem_dir_cellvars = lexem_new( "dir::cellvars", "cellvars", 0, 0 );
//   lexem_t lexem_symbol = lexem_new( "symbol", "+", 0, 0 );
//   lexem_t lexem_colon = lexem_new( "colon", ":", 0, 1 );
//   lexem_t lexem_dir_line = lexem_new( "dir::line", "\n", 0, 0 );
//   lexem_t lexem_insn_0 = lexem_new( "insn::0", "STOP_CODE", 0, 0 );
//   lexem_t lexem_insn_1 = lexem_new( "insn::1", "DELETE_NAME", 0, 0 );
//   lexem_t lexem_skip_comment = lexem_new( "skip::comment", "#k", 1, 1 );
//   lexem_t lexem_newline = lexem_new( "newline", "/n", 0, 1 );
//   lexem_t lexem_source_size = lexem_new( "set::source_size", "10", 0, 1 );
//   lexem_t lexem_stack_size = lexem_new( "set::stack_size", "11", 0, 1 );
//   lexem_t lexem_arg_count = lexem_new( "set::arg_count", "5", 0, 1 );
//   lexem_t lexem_posonly_arg_count = lexem_new( "set::posonly_arg_count", "5", 0, 1 );
//   lexem_t lexem_kwonly_arg_count = lexem_new( "set::kwonly_arg_count", "5", 0, 1 );
//   lexem_t lexem_set_flags= lexem_new( "set::flags", "flags", 0, 1 );
//   lexem_t lexem_dir_text=lexem_new( "dir::text", "filename", 0, 1 );
//
//
// //fonction testée:
//
//   //〈set-filename〉 : := {‘dir::set’} {‘skip::blank’} {‘filename’} {‘skip::blank’} {‘string’} 〈eol〉
//   // list_t list = list_new();
//   // list = list_add_last (list, lexem1);
//   // list = list_add_last (list, lexem3);
//   // list = list_add_last (list, lexem2);
//   // list = list_add_last (list, lexem4);
//   // list = list_add_last (list, lexem2);
//   // list = list_add_last (list, lexem5);
//   // list = list_add_last (list, lexem3);
//   //
//   // printf("initial list: \n");
//   // list_print ( list, lexem_print );
//   // printf("\n");
//   // list_t* lexems = &list;
//
//   //<list> : := {‘brack::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘brack::right’}
//   // list_t list2 = list_new();
//   // list2 = list_add_last (list2, lexem6);
//   // list2 = list_add_last (list2, lexem4);
//   // list2 = list_add_last (list2, lexem2);
//   // list2 = list_add_last (list2, lexem4);
//   // list2 = list_add_last (list2, lexem4);
//   // list2 = list_add_last (list2, lexem4);
//   // //list2 = list_add_last (list2, lexem2);
//   // list2 = list_add_last (list2, lexem9);
//
//   list_t list = list_new();
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank);
//   list = list_add_last (list, lexem_set_flags);
//   //list = list_add_last (list, lexem_skip_blank);
//   list = list_add_last (list, lexem_integer_hex);
//   list = list_add_last (list, lexem_newline);
//   // list = list_add_last (list, lexem_skip_blank);
//
//   printf("initial list: \n");
//   list_print ( list, lexem_print );
//   printf("\n");
//   list_t* lexems = &list;
//
//
//   //parse_set_filename ( lexems ) == 0
//   if (parse_set_flags ( lexems ) == 0){
//     printf("working!!\n");
//     exit( EXIT_SUCCESS );
//   }
//
//   else {
//     printf("not working\n");
//     exit( EXIT_FAILURE );
//   }

exit( EXIT_FAILURE );
}
