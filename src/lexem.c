

#define _POSIX_C_SOURCE 200809L /* strdup(3) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <../include/pyas/all.h>



lexem_t lexem_new( char *type, char *value, int line, int column ) {
  lexem_t lex = calloc( 1, sizeof( *lex ) );

  assert( lex );

  if ( type  && *type  ) lex->type  = strdup( type );
  if ( value && *value ) lex->value = strdup( value );

  lex->line   = line;
  lex->column = column;

  return lex;
}

int     lexem_print( void *_lex ) {
  lexem_t lex = _lex;

  return printf( "[%d:%d:%s] %s",
		 lex->line,
		 lex->column,
		 lex->type,
		 lex->value );
}

int     lexem_delete( void *_lex ) {
  lexem_t lex = _lex;

  if ( lex ) {
    free( lex->type );
    free( lex->value );
  }

  free( lex );

  return 0;
}


//renvoie le prochain lexem interressant SANS l'enlever de la liste
lexem_t lexem_peek(list_t *lexems)
{
  if (list_length ( *lexems ) == 0)
  {
    //printf("lexem_peek too far!!\n");
    //lexem_print (false_lex);
    return NULL;
//    return lexem_new ( "error", "error", 0, 0 );
  }

  lexem_t lex = list_first( *lexems );

  while (lexem_type( lex , "skip::blank" )==1 || lexem_type( lex , "skip::comment" )==1 || lexem_type( lex , "skip::comment2" )==1)
  {
    // lexem_delete(lex);
    *lexems = list_next( *lexems );

    if (list_empty(*lexems) == 1)
    {
      return NULL;
//      lex = lexem_new ( "error", "error", 0, 0 );
    }
    else lex = list_first( *lexems );

  }

  return lex;
}



//renvoie le prochain lexem interressant SANS l'enlever de la liste
lexem_t lexem_peek_pass_new_line(list_t *lexems)
{
  if (list_length ( *lexems ) == 0)
  {
    //printf("lexem_peek too far!!\n");
    //lexem_print (false_lex);
    return NULL;
//    return lexem_new ( "error", "error", 0, 0 );
  }

  lexem_t lex = list_first( *lexems );

  while (lexem_type( lex , "skip::blank" )==1 || lexem_type( lex , "skip::comment" )==1 || lexem_type( lex , "skip::comment2" )==1 || lexem_type( lex , "newline" )==1 || lexem_type( lex , "colon" )==1)
  {
    // lexem_delete(lex);
    *lexems = list_next( *lexems );

    if (list_empty(*lexems) == 1)
    {
      return NULL;
//      lex = lexem_new ( "error", "error", 0, 0 );
    }
    else lex = list_first( *lexems );

  }

  return lex;
}


//renvoie le prochain lexem interressant en l'enlevant de la liste
lexem_t lexem_advance(list_t *lexems)
{

  if (list_length ( *lexems ) == 0)
  {
    //printf("lexem_advance too far!!\n");
    return lexem_new ( "error", "error", 0, 0 );
  }

  lexem_t lex = lexem_peek( lexems );
  // *lexems=list_del_first(*lexems, lexem_delete);
  *lexems = list_next( *lexems );
  return lex;
}


//for next_lexem_is
int lexem_type ( lexem_t lex , char * type )
{
  return lex ? ( lex->type == strstr ( lex-> type , type ) ) : 0 ;
}

//determine si le prochain lexeme utile est bien du type demandee
int next_lexem_is(list_t *lexems, char *type)
{
  if ( lexem_type( lexem_peek( lexems ), type ) )
  {
    return 1;
  }
  return 0;
}

//afficher le message d’erreur msg et les coordonnees du lexeme en tete de *lexems.--> pour dire à l'utilisateur quel lexem est non valide
int print_parse_error(char *msg, list_t lexems)
{
  printf("%s\n", msg);
  return list_print_first(lexems, lexem_print);
}

//Compare le type et la valeur de deux lexem, renvoie 0 si pareil, -1 sinon
int lexem_compare(lexem_t lex1, lexem_t lex2)
{

  if ( (strcmp((lex1->type),(lex2->type))==0) && (strcmp((lex1->value),(lex2->value))==0) )
  {
    return 0;
  }
  return -1;
}

int lexem_compare_also_column_and_line(lexem_t lex1, lexem_t lex2)
{

  if ( (strcmp((lex1->type),(lex2->type))==0) && (strcmp((lex1->value),(lex2->value))==0) && (lex1->line==lex2->line) && (lex1->column==lex2->column))
  {
    return 0;
  }
  return -1;
}
