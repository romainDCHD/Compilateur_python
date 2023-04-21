/**
 * @file write_bitecode.c
 * @author Laura Rascol & Romain Duchadeau
 * @brief define funtions to parse list of lexems
 *
 */

#include <../include/pyas/all.h>

// // 〈eol〉 : := ( [{skip::‘skip::blank’}] [{‘skip::comment’}] {‘newline’} )* [{’skip::blank’}]
int parse_eol ( list_t *lexems ) {
  printf ( " Parsing eol \n " ) ;
  list_t lex = *lexems;

  //si ça n'est ni un blank ni un tab ni un espace ni un comment
  if ( next_lexem_is ( &lex , "skip::blank" ) == 0 && next_lexem_is ( &lex , "skip::comment" ) == 0 && next_lexem_is( &lex, "newline" ) == 0 )
  {
    return -1;
  }
  while ( next_lexem_is ( &lex , "skip::blank" ) == 1 || next_lexem_is ( &lex , "skip::comment" ) == 1 || next_lexem_is( &lex, "newline" ) == 1 )
  {
    lexem_advance ( &lex ) ;
  }
  *lexems = lex;
  return 0;
}


// 〈set-version-pyvm〉 : := {‘dir::set’} {‘skip::blank’} {‘version_pyvm’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int parse_set_version_pyvm ( list_t * lexems ) {
  printf ( " Parsing set version pyvm \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::version_pyvm" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  //Fonctions parse avancent
  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-flags〉 : := {‘dir::set’} {‘skip::blank’} {‘flags’} {‘skip::blank’} {‘integer::hex’} 〈eol〉
int parse_set_flags ( list_t * lexems ) {
  printf ( " Parsing set flags \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::flags" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::hex" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-filename〉 : := {‘dir::set’} {‘skip::blank’} {‘set::filename’} {‘skip::blank’} {‘string’} 〈eol〉
int parse_set_filename ( list_t * lexems ) {
  printf ( " Parsing set filename \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ){
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::filename" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "string" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
int parse_set_name ( list_t * lexems ) {
  printf ( " Parsing set name \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::name" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "string" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-source-size〉 : := {‘dir::set’} {‘skip::blank’} {‘source_size’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int parse_set_source_size ( list_t * lexems ) {
  printf ( " Parsing set source size \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::source_size" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == 0 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-stack-size〉 : := {‘dir::set’} {‘skip::blank’} {‘stack_size’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int parse_set_stack_size ( list_t * lexems ) {
  printf ( " Parsing set stack size \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::stack_size" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘arg_count’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int parse_set_arg_count ( list_t * lexems ) {
  printf ( " Parsing set arg count \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::arg_count" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-kwonly-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘kwonly_arg_count’}{‘skip::blank’} {‘integer::dec’} 〈eol〉
int parse_set_kwonly_arg_count ( list_t * lexems ) {
  printf ( " Parsing set kwonly arg count \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::kwonly_arg_count" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-posonly-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘posonly_arg_count’}{‘skip::blank’} {‘integer::dec’} 〈eol〉
int parse_set_posonly_arg_count ( list_t * lexems ) {
  printf ( " Parsing set posonly arg count \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::posonly_arg_count" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈insn〉 : := {‘insn::0’} | {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} )
int parse_insn ( list_t * lexems ) {
  printf ( " Parsing insn \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "insn::0" ) || next_lexem_is ( &lex , "insn::1" ) )
  {

    lexem_advance ( &lex );
    if( next_lexem_is ( &lex , "integer::dec" ) || next_lexem_is ( &lex , "symbol" ) )
    {
      *lexems = lex;
      return 0 ;
    }
    else  return -1;
  }

return -1;
}


//〈interned-strings〉 : := {‘dir::interned’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int parse_interned_strings ( list_t * lexems ) {
  printf ( " Parsing interned strings \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::interned" ) == 0 ) return -1 ;
  lexem_advance ( &lex ) ;
//lexem_advance au sein de eol
  if ( parse_eol ( &lex ) == -1 ) return -1 ;
  while ( next_lexem_is ( &lex , "string" ) == 1 )
  {
    lexem_advance ( &lex ) ;
    if (parse_eol( &lex) == -1 )
    {
      return -1;
    }
  }

  *lexems = lex;
  return 0 ;
}


//attention enlevé: |<tuple>
// || parse_tuple( &lex ) == 0
//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’}
int parse_constant ( list_t * lexems ) {
  printf ( " Parsing constant \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "integer" ) ||
       next_lexem_is ( &lex , "number::float" ) ||
       next_lexem_is ( &lex , "complex::float" ) ||
       next_lexem_is ( &lex , "string" ) ||
       next_lexem_is ( &lex , "pycst" ))
    {

    printf( "found constant: " );
    lexem_print ( lexem_peek ( &lex ) );
    printf("\n");
    lexem_advance ( &lex );
    *lexems = lex;
    return 0 ;
  }
  return -1;
}


//<tuple> : := {‘paren::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘paren::right’}
int parse_tuple ( list_t * lexems ) {
  printf ( " Parsing tuple \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "paren::left" ) == 0 ){
    return -1 ;
  }

  lexem_advance ( &lex ) ;

  while ( parse_constant ( &lex ) == 0 ){;}

        // print_parse_error ( "unexpected input", lexems );

    if ( next_lexem_is ( &lex , "paren::right" ) == 0){

    return -1;
    }

    lexem_advance ( &lex );
    *lexems = lex;
    return 0;
}


// 〈constants〉 : := {‘dir::consts’} 〈eol〉 ( 〈constant〉 〈eol〉 )*
int parse_constants ( list_t * lexems ) {
  printf ( " Parsing constants \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::consts" ) == 0 ) return -1 ;

  lexem_advance ( &lex ) ;

//lexem_advance au sein de eol
  if ( parse_eol ( &lex ) == -1 ) return -1 ;

  while ( parse_constant ( &lex ) == 0 ) {
    if (parse_eol( &lex) == -1) {
      return -1;
    }
    // lexem_advance ( &lex ) ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈names〉 : := {‘dir::names’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int parse_names ( list_t * lexems ) {
  printf ( " Parsing names \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::names" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex );
  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  while ( next_lexem_is ( &lex , "string" ) == 1 ) {
    lexem_advance ( &lex ) ;

    if ( parse_eol ( &lex ) == -1 ) {
      return -1 ;
    }
  }

  *lexems = lex;
  return 0 ;
}


//<list> : := {‘brack::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘brack::right’}
int parse_list ( list_t * lexems ) {
  printf ( " Parsing list \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "brack::left" ) == 0) return -1;
  lexem_advance ( &lex );

  while ( parse_constant ( &lex ) == 0 ){;}


  if ( next_lexem_is ( &lex , "brack::right" ) == 0){
    return -1;
  }
  lexem_advance ( &lex );

  *lexems = lex;
  return 0;
}


// 〈varnames〉 : := {‘dir::varnames’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int parse_varnames ( list_t * lexems ) {
  printf ( " Parsing varnames \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::varnames" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  while ( next_lexem_is ( &lex , "string" ) ) {
    lexem_advance ( &lex ) ;

    if ( parse_eol ( &lex ) == -1 ) {
      return -1 ;
    }
  }

  *lexems = lex;
  return 0 ;
}


// 〈freevars〉 : := {‘dir::freevars’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int parse_freevars ( list_t * lexems ) {
  printf ( " Parsing freevars \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::freevars" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  while ( next_lexem_is ( &lex , "string" ) ==1) {
    lexem_advance ( &lex ) ;

    if ( parse_eol ( &lex ) == -1 ) {
      return -1 ;
    }
  }

  *lexems = lex;
  return 0 ;
}


// 〈cellvars〉 : := {‘dir::cellvars’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int parse_cellvars ( list_t * lexems ) {
  printf ( " Parsing cellvars \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::cellvars" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  while ( next_lexem_is ( &lex , "string" ) == 1) {
    lexem_advance ( &lex ) ;

    if ( parse_eol ( &lex ) == -1 ) {
      return -1 ;
    }
  }

  *lexems = lex;
  return 0 ;
}


// 〈code〉 : := {‘dir::text’} 〈eol〉 ( 〈assembly-line〉 〈eol〉 )*
int parse_code ( list_t * lexems ) {
  printf ( " Parsing code \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::text" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;

  if ( parse_eol ( &lex ) == -1 ) {
    return -1 ;
  }

  while ( next_lexem_is ( &lex , "assembly_line" ) ) {
    lexem_advance ( &lex ) ;

    if ( parse_eol ( &lex ) == -1 ) {
      return -1 ;
    }
  }

  *lexems = lex;
  return 0 ;
}


// // 〈assembly-line〉 : := 〈insn〉 | 〈source-lineno〉 | 〈label〉
int parse_assembly_line ( list_t * lexems ) {
  printf ( " Parsing assembly line \n " ) ;
  list_t lex = *lexems;
  if ( parse_insn ( &lex ) == 0 || parse_source_lineno( &lex ) == 0 || parse_label(&lex) == 0) {
    return 0 ;
  }

  *lexems = lex;
  return -1;
}


// 〈label〉 : := {‘symbol’} {‘skip::blank’} {‘colon’}
int parse_label ( list_t * lexems ) {
  printf ( " Parsing label \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "symbol" ) == 0 ) {
    return -1 ;
  }

  lexem_advance ( &lex ) ;
  if ( next_lexem_is ( &lex , "colon" ) == 0 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈source-lineno〉 : := {‘dir::line’} {‘skip::blank’} {‘integer::dec’}
int parse_source_lineno ( list_t * lexems ) {
  printf ( " Parsing source lineno \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::line" ) == 0 ) {
    return -1 ;
  }
  lexem_advance ( &lex ) ;
  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    return -1 ;
  }

  *lexems = lex;
  return 0 ;
}


// 〈set-directives〉 : := 〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉] 〈set-stack-size〉 〈set-arg-count〉 [set-kwonly-arg-count] [set-posonly-arg-count]
int parse_set_directives ( list_t * lexems ) {
  printf ( " Parsing set directives \n " ) ;
  list_t lex = *lexems;

  if ( -1 == parse_set_version_pyvm ( &lex ) ) {
    return -1 ;
  }

  if ( -1 == parse_set_flags ( &lex ) ) {
    return -1 ;
  }

  if ( -1 == parse_set_filename ( &lex ) ) {
    return -1 ;
  }

  if ( -1 == parse_set_name ( &lex ) ) {
    return -1 ;
  }

  //Les fonctions parse avancent toute seule
  parse_set_source_size ( &lex );

  if ( -1 == parse_set_stack_size ( &lex ) ) {
    return -1 ;
  }

  if ( -1 == parse_set_arg_count ( &lex ) ) {
    return -1 ;
  }
  parse_set_kwonly_arg_count ( &lex );
  parse_set_posonly_arg_count ( &lex );
  *lexems = lex;
  return 0 ;
}


//<prologue> : := <set-directives> <interned-strings> <constants> <names> [<varnames> <freevars> <cellvars>]
int parse_prologue ( list_t * lexems ) {
  printf ( " Parsing prologue \n " ) ;
  list_t lex = *lexems;

  if ( -1 == parse_set_directives ( &lex ) ) return -1 ;

  if ( -1 == parse_interned_strings ( &lex ) ) return -1 ;

  if ( -1 == parse_constants ( &lex ) ) return -1 ;

  if ( -1 == parse_names ( &lex ) ) return -1 ;
  parse_varnames( &lex );
  parse_freevars ( &lex );
  parse_cellvars( &lex );

  *lexems = lex;
  return 0 ;
}


// <pys> : := <eol>* <prologue> <code>
int parse_pys ( list_t * lexems ) {
  printf ( " Parsing pys \n " ) ;
  list_t lex = *lexems;

  while( parse_eol ( &lex ) == 0 ){}

  if ( parse_prologue ( &lex ) == -1 ) return -1 ;

  if ( parse_code ( &lex ) == -1 ) return -1 ;

  *lexems = lex;
  return 0 ;
}
