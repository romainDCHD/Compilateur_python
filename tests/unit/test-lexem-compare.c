/**
 * @file test-lexem_compare.c
 * @author Laura
 * @date 26/10/2022
 * @brief Driver LEXEM COMPARATION.
 *
 * Tests unitaires pour les "fonctions de lexem"
 */

#include <unitest/unitest.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/pyas/list.h"
#include "../include/pyas/lexem.h"

static void lexem_compare_basics( void ) {
  test_suite( "Basic test of lexem module, (q)");
  lexem_t lex_1=lexem_new( "char", "41", 0, 11 );
  lexem_t lex_2=lexem_new( "int", "41", 0, 25 );

  int i=lexem_compare(lex_1, lex_2);
  test_assert( i==-1,
         "test de lexem_compare quand ce n'est pas les mêmes" );

   lexem_t lex_3=lexem_new( "int", "43", 0, 25 );
   lexem_t lex_4=lexem_new( "int", "43", 5, 25 );
   lexem_t lex_5=lexem_new( "int", "43", 0, 25 );

   i=lexem_compare(lex_3, lex_4);
   test_assert(i==0,
          "test de lexem_compare quand c'est les mêmes" );

   i=lexem_compare(lex_3, lex_2);
   test_assert( i=-1,
         "test de lexem_compare quand ce n'est pas les mêmes" );

   i=lexem_compare(lex_1, lex_3);
   test_assert( i==-1,
         "test de lexem_compare quand ce n'est pas les mêmes" );

   i=lexem_compare_also_column_and_line(lex_3, lex_4);
   test_assert( i==-1,
         "test de lexem_compare_also_column_and_line quand ce ne sont pas exactement les mêmes" );

   i=lexem_compare_also_column_and_line(lex_3, lex_5);
   test_assert( i==0,
         "test de lexem_compare_also_column_and_line quand ce sont exactement les mêmes" );

  lexem_delete(lex_1);
  lexem_delete(lex_2);

  lexem_delete(lex_3);
  lexem_delete(lex_4);

  lexem_delete(lex_5);
  }
  int main ( int argc, char *argv[] ) {

    unit_test( argc, argv );

    lexem_compare_basics();

    exit( EXIT_SUCCESS );
  }
