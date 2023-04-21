/**
 * @file test-list.c
 * @author RASCOL Laura
 * @date Sat Oct  29
 * @brief Driver for list of lexems.
 *
 * Tests unitaires pour les "liste_ compare de lexems"
 */
#include <unitest/unitest.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/pyas/list.h"
#include "../include/pyas/lexem.h"


static void list_basics( void ) {
  test_suite( "Basic test of list_compare" );

  list_t l = list_new();
  list_t l2 = list_new();
  list_t l3 = list_new();

  l = list_add_first( l, lexem_new( "int", "42", 1, 8 ) );
  l = list_add_first( l, lexem_new( "str", "ficelle", 1, 0 ) );
  l = list_add_first( l, lexem_new( "int", "43", 2, 9 ) );

  list_t liste=l;

  l2 = list_add_first( l2, lexem_new( "int", "42", 1, 8 ) );
  l2 = list_add_first( l2, lexem_new( "str", "ficelle", 1, 0 ) );
  l2 = list_add_first( l2, lexem_new( "int", "43", 2, 9 ) );

  list_t liste2=l2;

  l3 = list_add_first( l3, lexem_new( "int", "42", 1, 8 ) );
  l3 = list_add_first( l3, lexem_new( "str", "lol", 1, 0 ) );
  l3 = list_add_first( l3, lexem_new( "int", "43", 2, 9 ) );

  list_t liste3=l3;

  test_assert( list_compare_lexem(l, l2) == 0,
	       "list_compare ok when same list" );

   test_assert( list_compare_lexem(l, l3) == -1,
  	       "list_compare ok when not same list" );

  // free memory
  list_delete( liste, lexem_delete );
  list_delete( liste2, lexem_delete );
  list_delete( liste3, lexem_delete );

}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  list_basics();
  exit( EXIT_SUCCESS );
}
