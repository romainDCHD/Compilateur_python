/**
 * @file test-lexem.c
 * @author Laura
 * @date Fri Jul  2 17:58:47 2021
 * @brief Driver for list of lexems.
 *
 * Tests unitaires pour les "fonctions de lexem"
 */

#include <unitest/unitest.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/pyas/list.h"
#include "../include/pyas/lexem.h"


static void lexem_basics( void ) {
  test_suite( "Basic test of lexem module, (q)");
  list_t l = list_new();
  list_t liste;
  int a;

  l = list_add_first( l, lexem_new( "int", "41", 1, 25 ) );
  l = list_add_first( l, lexem_new( "skip::blank", "", 1, 1 ) );
  l = list_add_first( l, lexem_new( "int", "42", 1, 2 ) );
  l = list_add_first( l, lexem_new( "skip::blank", "#projetinfo", 1, 3 ) );
  l = list_add_first( l, lexem_new( "char", "melissa", 1, 5 ) );
  l = list_add_first( l, lexem_new( "int", "43", 1, 10 ) );
  l = list_add_first( l, lexem_new( "int", "44", 1, 15 ) );
  l = list_add_first( l, lexem_new( "int", "45", 1, 20 ) );


  liste = l;

  lexem_t lex=lexem_peek(&l);
  test_oracle( lexem_print( lex ), "[1:20:int] 45",
	       "Test de lexem peek");

  lex=lexem_advance(&l);


  test_oracle( lexem_print( lex ), "[1:20:int] 45",
	       "Test du renvoie de la fonction lexem advance");

  test_oracle( list_print_first(l, lexem_print), "[1:15:int] 44",
 	       "Test de l'avancée dans la liste avec la fonction lexem advance");

  lex=lexem_advance(&l);


  test_oracle( lexem_print( lex ), "[1:15:int] 44",
	       "Test 2 du renvoie de la fonction lexem advance");

  test_oracle( list_print_first(l, lexem_print), "[1:10:int] 43",
 	       "Test 2 de l'avancée dans la liste avec la fonction lexem advance");


   a=lexem_type ( lex , "int" );
   test_assert( a=1,
          "test de lexem_type quand c'est le bon type" );
   a=lexem_type ( lex , "char" );
   test_assert( a=-1,
          "test de lexem_type quand ce n'est pas le bon type" );

   lex=lexem_advance(&l);


   a=lexem_type ( lex , "char" );
   test_assert( a=1,
          "test 2 de lexem_type quand c'est le bon type" );
   a=lexem_type ( lex , "int" );
   test_assert( a=-1,
          "test 2 de lexem_type quand ce n'est pas le bon type" );
  // lexem_delete(lex);

    a=next_lexem_is(&l, "int");
    test_assert( a=1,
           "test de next_lexem_is quand c'est le bon type" );

    test_oracle( print_parse_error("test", l), "test\n[1:5:char] melissa",
  	        "Test de de print parse error");

    lex=lexem_advance(&l);

    lex=lexem_peek(&l);
    test_oracle( lexem_print( lex ), "[1:2:int] 42",
  	       "Test de lexem peek quand c'est un lexem inutile ici espace");

     lex=lexem_advance(&l);


     lex=lexem_peek(&l);
     test_oracle( lexem_print( lex ), "[1:25:int] 41",
   	       "Test de lexem peek quand c'est un lexem inutile ici commentaire");

  list_delete( liste, lexem_delete );

}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  lexem_basics();

  exit( EXIT_SUCCESS );
}
