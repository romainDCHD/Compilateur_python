/**
 * @file test-grammar.c
 * @author Laura
 * @date Wed Oct  12
 * @brief Driver for grammar.
 *
 * Tests unitaires pour les "fonctions de grammar"
 */

#include "../include/pyas/all.h"

static void grammar_basics( void ) {
  test_suite( "Basic test of grammar module");
  list_t list = list_new();
  list_t liste; //Pour libérer mémoire

  lexem_t lexem_dir_set = lexem_new( "dir::set", ".set", 0, 0 );
  lexem_t lexem_skip_blank = lexem_new( "skip::blank", " ", 1, 0 );
  lexem_t lexem_filename = lexem_new( "set::filename", "nom_fichier", 0, 1 );
  lexem_t lexem_string = lexem_new( "string", "randomstring", 1, 1 );
  lexem_t lexem_comment = lexem_new( "skip::comment", "#random_comment", 1, 0 );
  lexem_t lexem_brack_left = lexem_new( "brack::left", "[", 0, 0 );
  lexem_t lexem_dir_consts = lexem_new( "dir::consts", "const", 0, 1 );
  lexem_t lexem_brack_right = lexem_new( "brack::right", "]", 1, 0 );
  lexem_t lexem_integer_dec = lexem_new( "integer::dec", "10", 1, 1 );
  lexem_t lexem_set_version_pyvm = lexem_new( "set::version_pyvm", "version_pyvm", 0, 1 );
  lexem_t lexem_set_name = lexem_new( "set::name", "name", 0, 1 );
  lexem_t lexem_dir_interned = lexem_new( "dir::interned", "intern", 0, 0 );
  lexem_t lexem_integer_hex = lexem_new( "integer::hex", "10", 0, 0 );
  lexem_t lexem_number_float = lexem_new( "number::float", "10", 0, 0 );
  lexem_t lexem_complex_float = lexem_new( "complex::float", "10", 0, 0 );
  lexem_t lexem_paren_left = lexem_new( "paren::left", "(", 0, 0 );
  lexem_t lexem_paren_right = lexem_new( "paren::right", ")", 1, 0 );
  lexem_t lexem_dir_varnames = lexem_new( "dir::varnames", "nom", 0, 0 );
  lexem_t lexem_dir_names = lexem_new( "dir::names", "nom", 0, 0 );
  lexem_t lexem_dir_freevars = lexem_new( "dir::freevars", "freevars", 0, 0 );
  lexem_t lexem_dir_cellvars = lexem_new( "dir::cellvars", "cellvars", 0, 0 );
  lexem_t lexem_symbol = lexem_new( "symbol", "+", 0, 0 );
  lexem_t lexem_colon = lexem_new( "colon", ":", 0, 1 );
  lexem_t lexem_dir_line = lexem_new( "dir::line", "\n", 0, 0 );
  lexem_t lexem_insn_0 = lexem_new( "insn::0", "STOP_CODE", 0, 0 );
  lexem_t lexem_insn_1 = lexem_new( "insn::1", "DELETE_NAME", 0, 0 );
  lexem_t lexem_skip_comment = lexem_new( "skip::comment", "#k", 1, 1 );
  lexem_t lexem_newline = lexem_new( "newline", "/n", 0, 1 );
  lexem_t lexem_source_size = lexem_new( "set::source_size", "10", 0, 1 );
  lexem_t lexem_stack_size = lexem_new( "set::stack_size", "11", 0, 1 );
  lexem_t lexem_arg_count = lexem_new( "set::arg_count", "5", 0, 1 );
  lexem_t lexem_posonly_arg_count = lexem_new( "set::posonly_arg_count", "5", 0, 1 );
  lexem_t lexem_kwonly_arg_count = lexem_new( "set::kwonly_arg_count", "5", 0, 1 );
  lexem_t lexem_set_flags= lexem_new( "set::flags", "flags", 0, 1 );
  lexem_t lexem_dir_text=lexem_new( "dir::text", "filename", 0, 1 );
  lexem_t lexem_pycst=lexem_new( "pycst", "None", 0, 1 );
  //fonction testées :

    //TEST DE set-filename


  //〈set-filename〉 : := {‘dir::set’} {‘skip::blank’} {‘set::filename’} {‘skip::blank’} {‘string’} 〈eol〉
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_filename);
  list = list_add_last (list, lexem_string);
  list = list_add_last (list, lexem_comment);
  list = list_add_last (list, lexem_newline);
  liste=list;
  list_t* lexems = &list;
  test_assert( parse_set_filename ( lexems ) == 0,
         "test de parse set filename quand tout est bon = 0" );
  list_delete( liste, NULL );



  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_string);
  list = list_add_last (list, lexem_filename);
  list = list_add_last (list, lexem_comment);
  liste=list;
  lexems = &list;
  test_assert( parse_set_filename ( lexems ) == -1,
         "test de parse set filename quand tout n'est pas dans le bon ordre = 0" );
           list_delete( liste, NULL );




    //TEST DE list
  //<list> : := {‘brack::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘brack::right’}  // list = list_add_last (list, lexem1);
  //<list> : := {‘brack::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘brack::right’}
  list = list_new();
  list = list_add_last (list, lexem_brack_left);
  list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_number_float);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_brack_right);
  liste=list;
  lexems = &list;
  test_assert( parse_list ( lexems ) == 0,
         "test de parse list quand tout est bon = 0" );
         list_delete( liste, NULL );



  list = list_new();
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_dir_consts);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_dir_consts);
  list = list_add_last (list, lexem_brack_right);
  liste=list;
  lexems = &list;
  test_assert( parse_list ( lexems ) == -1,
         "test de parse list quand il manque [" );
  list_delete( liste, NULL );

   list = list_new();
   list = list_add_last (list, lexem_brack_left);
   list = list_add_last (list, lexem_dir_consts);
   list = list_add_last (list, lexem_skip_blank);
   list = list_add_last (list, lexem_dir_consts);
   liste=list;
   lexems = &list;
   test_assert( parse_list ( lexems ) == -1,
          "test de parse list quand il manque ]" );
   list_delete( liste, NULL );





   //TEST DE set-parse_set_version_pyvm
// 〈set-version-pyvm〉 : := {‘dir::set’} {‘skip::blank’} {‘version_pyvm’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_set_version_pyvm);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_version_pyvm ( lexems ) == 0,
         "test de parse version pyvm quand tout est bon = 0" );
  list_delete( liste, NULL );

  list = list_new();
//<set-version-pyvm> : := {‘dir::set’} {‘integer::dec’} <eol> {‘blank’} {‘version_pyvm’} {‘blank’}
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_set_version_pyvm);
 list = list_add_last (list, lexem_skip_blank);
 liste=list;
 lexems = &list;
 test_assert( parse_set_version_pyvm ( lexems ) == -1,
        "test de parse version pyvm quand il manque dir::set" );
 list_delete( liste, NULL );

 list = list_new();
//<set-version-pyvm> : := {‘dir::set’} {‘integer::dec’} <eol> {‘blank’} {‘version_pyvm’} {‘blank’}
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_set_version_pyvm);
list = list_add_last (list, lexem_skip_blank);
liste=list;
lexems = &list;
test_assert( parse_set_version_pyvm ( lexems ) == -1,
       "test de parse version pyvm quand il manque interger::dec" );
list_delete( liste, NULL );


list = list_new();
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_integer_dec);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_skip_blank);
liste=list;
lexems = &list;
test_assert( parse_set_version_pyvm ( lexems ) == -1,
      "test de parse version pyvm quand il manque version_pyvm" );
list_delete( liste, NULL );




//TEST DE set flags
list = list_new();
//<set-flags> : := {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’} <eol> TESTE
// // 〈set-flags〉 : := {‘dir::set’} {‘skip::blank’} {‘flags’} {‘skip::blank’} {‘integer::hex’} 〈eol〉
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_set_flags);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_flags ( lexems ) == 0,
       "test de parse set flags quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
//<set-flags> : := {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’} <eol> TESTE
// // 〈set-flags〉 : := {‘dir::set’} {‘skip::blank’} {‘flags’} {‘skip::blank’} {‘integer::hex’} 〈eol〉
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_set_flags);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_flags ( lexems ) == -1,
       "test de parse set flags quand il manque dir::set" );
list_delete( liste, NULL );

list = list_new();
//<set-flags> : := {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’} <eol> TESTE
// // 〈set-flags〉 : := {‘dir::set’} {‘skip::blank’} {‘flags’} {‘skip::blank’} {‘integer::hex’} 〈eol〉
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_flags ( lexems ) == -1,
       "test de parse set flags quand il manque set::flags" );
      //list_delete( list, lexem_delete );
list_delete( liste, NULL );


list = list_new();
//<set-flags> : := {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’} <eol> TESTE
// // 〈set-flags〉 : := {‘dir::set’} {‘skip::blank’} {‘flags’} {‘skip::blank’} {‘integer::hex’} 〈eol〉
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_set_flags);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_flags ( lexems ) == -1,
      "test de parse set flags quand il manque integer_hex" );
list_delete( liste, NULL );




//TEST DE set name
list = list_new();
//<set-name> : := {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’} <eol>
// // 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_set_name);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_name ( lexems ) == 0,
       "test de parse set name quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
//<set-name> : := {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’} <eol>
// // 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_set_name);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_name ( lexems ) == -1,
       "test de parse set name quand il manque dir::set" );
list_delete( liste, NULL );

list = list_new();
//<set-name> : := {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’} <eol>
// // 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_name ( lexems ) == -1,
       "test de parse set name quand il manque set::name" );
list_delete( liste, NULL );

list = list_new();
//<set-name> : := {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’} <eol>
// // 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
list = list_add_last (list, lexem_dir_set);
list = list_add_last (list, lexem_set_name);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_set_name ( lexems ) == -1,
       "test de parse set name quand il manque string" );
list_delete( liste, NULL );




//TEST de interned strings
list = list_new();
//〈interned-strings〉 : := {‘dir::interned’} 〈eol〉 ( {‘string’} 〈eol〉 )*
list = list_add_last (list, lexem_dir_interned);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_interned_strings ( lexems ) == 0,
       "test de parse INTERNED STRINGS quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_interned_strings ( lexems ) == -1,
       "test de parse INTERNED STRINGS quand il manque dir::interned" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_dir_interned);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_interned_strings ( lexems ) == 0,
       "test de parse INTERNED STRINGS quand il manque string" );
list_delete( liste, NULL );




// //TSST DE CONSTANTS
// list = list_new();
// 〈constants〉 : := {‘dir::consts’} 〈eol〉 ( 〈constant〉 〈eol〉 )*
list = list_new();
list = list_add_last (list, lexem_dir_consts);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_constants ( lexems ) == 0,
       "test de parse constants quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_constants ( lexems ) == -1,
       "test de parse constants quand il manque dir_consts" );
list_delete( liste, NULL );


//TEST DE CONSTANT
//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} | <tuple>
list = list_new();
list = list_add_last (list, lexem_integer_hex);
liste=list;
lexems = &list;
test_assert( parse_constant ( lexems ) == 0,
       "test de parse constant quand il ya integer" );
list_delete( liste, NULL );


//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} | <tuple>
list = list_new();
list = list_add_last (list, lexem_number_float);
liste=list;
lexems = &list;
test_assert( parse_constant ( lexems ) == 0,
       "test de parse constant quand il ya number::float" );
list_delete( liste, NULL );

//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} | <tuple>
list = list_new();
list = list_add_last (list, lexem_complex_float);
liste=list;
lexems = &list;
test_assert( parse_constant ( lexems ) == 0,
       "test de parse constant quand il ya complex::float" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_string);
liste=list;
lexems = &list;
test_assert( parse_constant ( lexems ) == 0,
       "test de parse constant quand il ya string" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_pycst);
liste=list;
lexems = &list;
test_assert( parse_constant ( lexems ) == 0,
       "test de parse constant quand il ya pycst" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_paren_left);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
// list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_paren_right);
liste=list;
lexems = &list;
test_assert( parse_constant ( lexems ) == -1,
       "test de parse constant quand il ya tuple cad quelque chose pas compris dnas les possibilités traitées" );
list_delete( liste, NULL );




//TEST DE TUPLE
//<tuple> : := {‘paren::left’} ({’blank’} <constant>)* [{’blank’}] {‘paren::right’}
list = list_new();
list = list_add_last (list, lexem_paren_left);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
// list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_paren_right);
liste=list;
lexems = &list;
test_assert( parse_tuple ( lexems ) == 0,
       "test de parse tuple quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
// list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_paren_right);
liste=list;
lexems = &list;
test_assert( parse_tuple ( lexems ) == -1,
       "test de parse tuple quand il manque paren_left" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_hex);
// list = list_add_last (list, lexem_skip_blank);
liste=list;
lexems = &list;
test_assert( parse_tuple ( lexems ) == -1,
       "test de parse tuple quand il manque paren_right" );
list_delete( liste, NULL );




//TEST DE names
// 〈names〉 : := {‘dir::names’} 〈eol〉 ( {‘string’} 〈eol〉 )*
list = list_new();
list = list_add_last (list, lexem_dir_names);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_names ( lexems ) == 0,
      "test de parse names quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_names ( lexems ) == -1,
      "test de parse names quand il manque dir_names" );
list_delete( liste, NULL );




//TEST DE varnames
// 〈varnames〉 : := {‘dir::varnames’} 〈eol〉 ( {‘string’} 〈eol〉 )*
list = list_new();
list = list_add_last (list, lexem_dir_varnames);
// list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_varnames ( lexems ) == 0,
       "test de parse varnames quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
// list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_varnames ( lexems ) == -1,
       "test de parse varnames quand il manque dir_varnames" );
list_delete( liste, NULL );




//TEST DE freevars
// 〈freevars〉 : := {‘dir::freevars’} 〈eol〉 ( {‘string’} 〈eol〉 )*
list = list_new();
list = list_add_last (list, lexem_dir_freevars);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_freevars ( lexems ) == 0,
       "test de parse freevars quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_freevars ( lexems ) == -1,
       "test de parse freevars quand il manque dir_freevars" );
list_delete( liste, NULL );




//TEST DE cellvars
// 〈cellvars〉 : := {‘dir::cellvars’} 〈eol〉 ( {‘string’} 〈eol〉 )*
list = list_new();
list = list_add_last (list, lexem_dir_cellvars);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_cellvars ( lexems ) == 0,
       "test de parse cellvars quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;
lexems = &list;
test_assert( parse_cellvars ( lexems ) == -1,
       "test de parse cellvars quand il manque dir_cellvars" );
list_delete( liste, NULL );




//TEST DE LABEL
// 〈label〉 : := {‘symbol’} {‘blank’} {‘colon’}
list = list_new();
list = list_add_last (list, lexem_symbol);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_colon);
liste=list;
lexems = &list;
test_assert( parse_label ( lexems ) == 0,
       "test de parse label quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_colon);
liste=list;
lexems = &list;
test_assert( parse_label ( lexems ) == -1,
       "test de parse label quand il manque symbol" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_symbol);
list = list_add_last (list, lexem_skip_blank);
liste=list;
lexems = &list;
test_assert( parse_label ( lexems ) == -1,
       "test de parse label quand il manque colon" );
list_delete( liste, NULL );




//TEST DE SOURCE lineno
// 〈source-lineno〉 : := {‘dir::line’} {‘blank’} {‘integer::dec’}
list = list_new();
list = list_add_last (list, lexem_dir_line);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_dec);
liste=list;
lexems = &list;
test_assert( parse_source_lineno ( lexems ) == 0,
       "test de parse source_lineno quand tout est bon = 0" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_dec);
liste=list;
lexems = &list;
test_assert( parse_source_lineno ( lexems ) == -1,
       "test de parse source_lineno quand il manque dir::line" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_dir_line);
list = list_add_last (list, lexem_skip_blank);
liste=list;
lexems = &list;
test_assert( parse_source_lineno ( lexems ) == -1,
       "test de parse source_lineno quand il manque integer_dec" );
list_delete( liste, NULL );




//TEST DE insn
  // // 〈insn〉 : := {‘insn::0’} | {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} )
  list = list_new();
  list = list_add_last (list, lexem_insn_0);
  list = list_add_last (list, lexem_integer_dec);
  liste=list;
  lexems = &list;
  test_assert( parse_insn ( lexems ) == 0,
         "test de parse_insn quand tout est bon = 0" );

  list_delete( liste, NULL );

  // // 〈insn〉 : := {‘insn::0’} | {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} )
  list = list_new();
  list = list_add_last (list, lexem_insn_0);
  list = list_add_last (list, lexem_symbol);
  liste=list;
  lexems = &list;
  test_assert( parse_insn ( lexems ) == 0,
         "test de parse_insn quand tout est bon = 0" );

  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_insn_1);
  list = list_add_last (list, lexem_symbol);
  liste=list;
  lexems = &list;
  test_assert( parse_insn ( lexems ) == 0,
         "test de parse_insn quand tout est bon = 0" );

  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_insn_1);
  list = list_add_last (list, lexem_integer_dec);
  liste=list;
  lexems = &list;
  test_assert( parse_insn ( lexems ) == 0,
         "test de parse_insn quand tout est bon = 0" );

  list_delete( liste, NULL );




//TEST DE eol
  // // 〈eol〉 : := ([{‘blank’}] [{‘comment’}] {‘newline’} [{’blank’}])*
  list = list_new();
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_comment);
  list = list_add_last (list, lexem_newline);
  list = list_add_last (list, lexem_skip_blank);
  liste=list;
  lexems = &list;
  test_assert( parse_eol ( lexems ) == 0,
         "test de parse eol quand tout est bon = 0" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_eol ( lexems ) == 0,
         "test de parse eol quand il n'y a que new_line" );
  list_delete( liste, NULL );




//TEST DE SOURCE SIZE
  // // 〈set-source-size〉 : := {‘dir::set’} {‘blank’} {‘source_size’} {‘blank’}{‘integer::dec’} 〈eol〉
  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_source_size);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  liste=list;
  lexems = &list;
  test_assert( parse_set_source_size ( lexems ) == 0,
         "test de parse_set_source_size quand tout est bon = 0" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_source_size);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  liste=list;
  lexems = &list;
  test_assert( parse_set_source_size ( lexems ) == -1,
         "test de parse_set_source_size il manque dir_set" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  liste=list;
  lexems = &list;
  test_assert( parse_set_source_size ( lexems ) == -1,
         "test de parse_set_source_size il manque source_size" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_source_size);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  liste=list;
  lexems = &list;
  test_assert( parse_set_source_size ( lexems ) == -1,
         "test de parse_set_source_size il manque integer_hex" );
  list_delete( liste, NULL );




//TEST DE STACK SIZE
  // // 〈set-stack-size〉 : := {‘dir::set’} {‘blank’} {‘stack_size’} {‘blank’}{‘integer::dec’} 〈eol〉
  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_stack_size);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_stack_size ( lexems ) == 0,
         "test de parse_set_stack_size eol quand tout est bon = 0" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_stack_size);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_stack_size ( lexems ) == -1,
         "test de parse_set_stack_size eol quand il manque dir_set" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_stack_size ( lexems ) == -1,
         "test de parse_set_stack_size eol quand il manque stack_size" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_stack_size);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_stack_size ( lexems ) == -1,
         "test de parse_set_stack_size eol quand il manque integer_dec" );
  list_delete( liste, NULL );




//TEST DE ARG COUNT
  // // 〈set-arg-count〉 : := {‘dir::set’} {‘blank’} {‘arg_count’} {‘blank’}{‘integer::dec’} 〈eol〉
  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_arg_count ( lexems ) == 0,
         "test de parse_set_arg_count quand tout est bon = 0" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_arg_count ( lexems ) == -1,
         "test de parse_set_arg_count quand il manque dir_set" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_arg_count ( lexems ) == -1,
         "test de parse_set_arg_count quand il manque arg_count" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_arg_count ( lexems ) == -1,
         "test de parse_set_arg_count quand il manque integer_hex" );
  list_delete( liste, NULL );




//TEST DE KNOWLY ARG COUNT
  // // 〈set-kwonly-arg-count〉 : := {‘dir::set’} {‘blank’} {‘kwonly_arg_count’}{‘blank’} {‘integer::dec’} 〈eol〉
  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_kwonly_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_kwonly_arg_count ( lexems ) == 0,
         "test de parse_set_kwonly_arg_count quand tout est bon = 0" );
  list_delete( liste, NULL );

 list = list_new();
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_kwonly_arg_count);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_integer_dec);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);
 liste=list;
 lexems = &list;
 test_assert( parse_set_kwonly_arg_count ( lexems ) == -1,
        "test de parse_set_kwonly_arg_count quand il manque dir_set" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_kwonly_arg_count ( lexems ) == -1,
         "test de parse_set_kwonly_arg_count quand il manque kwonly_arg_count" );
  list_delete( liste, NULL );

 list = list_new();
 list = list_add_last (list, lexem_dir_set);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_kwonly_arg_count);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_skip_blank);
 list = list_add_last (list, lexem_newline);
 liste=list;
 lexems = &list;
 test_assert( parse_set_kwonly_arg_count ( lexems ) == -1,
        "test de parse_set_kwonly_arg_count quand il manque integer_dec" );
  list_delete( liste, NULL );




//TEST DE posonly_arg_count
  // // 〈set-posonly-arg-count〉 : := {‘dir::set’} {‘blank’} {‘posonly_arg_count’}{‘blank’} {‘integer::dec’} 〈eol〉
  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_posonly_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_posonly_arg_count ( lexems ) == 0,
         "test de parse_set_posonly_arg_count quand tout est bon = 0" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_posonly_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_posonly_arg_count ( lexems ) == -1,
         "test de parse_set_posonly_arg_count quand il manque dir_set" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_integer_dec);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_posonly_arg_count ( lexems ) == -1,
         "test de parse_set_posonly_arg_count quand il manque posonly_arg_count" );
  list_delete( liste, NULL );

  list = list_new();
  list = list_add_last (list, lexem_dir_set);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_posonly_arg_count);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_skip_blank);
  list = list_add_last (list, lexem_newline);
  liste=list;
  lexems = &list;
  test_assert( parse_set_posonly_arg_count ( lexems ) == -1,
         "test de parse_set_posonly_arg_count quand il manque integer_dec" );
  list_delete( liste, NULL );




//TEST DE SET DIRECTIVES
// // 〈set-directives〉 : := 〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉] 〈set-stack-size〉 〈set-arg-count〉 [set-kwonly-arg-count] [set-posonly-arg-count]
list = list_new();
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
list = list_add_last (list, lexem_skip_blank);
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
liste=list;

lexems = &list;
test_assert( parse_set_directives ( lexems ) == 0,
       "test de parse SET DIRECTIVES quand tout est bon = 0 (avec tous les ou)" );
list_delete( liste, NULL );




//TEST DE SET DIRECTIVES
// // 〈set-directives〉 : := 〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉] 〈set-stack-size〉 〈set-arg-count〉 [set-kwonly-arg-count] [set-posonly-arg-count]
list = list_new();
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
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_newline);
liste=list;

lexems = &list;
test_assert( parse_set_version_pyvm ( lexems ) == 0,
       "test de parse set directives quand tout est bon = 0 (sans les ou)" );
list_delete( liste, NULL );




  //TEST DE prologue
//<prologue> : := <set-directives> <interned-strings> <constants> <names>
list = list_new();
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
list = list_add_last (list, lexem_skip_blank);
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
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);

//names
list = list_add_last (list, lexem_dir_names);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_string);
list = list_add_last (list, lexem_newline);
liste=list;

lexems = &list;
test_assert( parse_prologue ( lexems ) == 0,
       "test de parse prologue  quand tout est bon = 0 (sans les ou)" );
list_delete( liste, NULL );

list = list_new();
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
list = list_add_last (list, lexem_skip_blank);
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
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
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
liste=list;

lexems = &list;
test_assert( parse_prologue ( lexems ) == 0,
       "test de parse prologue  quand tout est bon = 0 (avec les ou)" );
list_delete( liste, NULL );




//TEST ASSEMBLY LINE
// // 〈assembly-line〉 : := 〈insn〉 | 〈source-lineno〉 | 〈label〉
list = list_new();
list = list_add_last (list, lexem_insn_0);
list = list_add_last (list, lexem_integer_dec);
liste=list;
lexems = &list;
test_assert( parse_assembly_line ( lexems ) == 0,
       "test de parse_assembly_line quand tout est bon = 0 (insn)" );
list_delete( liste, NULL );


list = list_new();
list = list_add_last (list, lexem_dir_line);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_integer_dec);
liste=list;
lexems = &list;
test_assert( parse_assembly_line ( lexems ) == 0,
       "test de parse_assembly_line quand tout est bon = 0 (source_lineno)" );
list_delete( liste, NULL );

list = list_new();
list = list_add_last (list, lexem_symbol);
list = list_add_last (list, lexem_skip_blank);
list = list_add_last (list, lexem_colon);
liste=list;
lexems = &list;
test_assert( parse_assembly_line ( lexems ) == 0,
       "test de parse_assembly_line quand tout est bon = 0 (label)" );
list_delete( liste, NULL );




//TEST CODE
// 〈code〉 : := {‘dir::text’} 〈eol〉 ( 〈assembly-line〉 〈eol〉 )*
list = list_new();
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
liste=list;

lexems = &list;
test_assert( parse_code ( lexems ) == 0,
       "test de parse_code quand tout est bon = 0" );
list_delete( liste, NULL );




 //TEST PYS
 //// <pys> : := <eol>* <prologue> <code>
 list = list_new();
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
list = list_add_last (list, lexem_skip_blank);
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
list = list_add_last (list, lexem_integer_hex);
list = list_add_last (list, lexem_newline);
list = list_add_last (list, lexem_integer_hex);
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

liste=list;
 lexems = &list;
 test_assert( parse_pys ( lexems ) == 0,
        "test de parse_pys quand tout est bon = 0" );
list_delete( liste, NULL );

//lIBÉRATION MÉMOIRE LEXEM
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

}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  grammar_basics();

  exit( EXIT_SUCCESS );
}
