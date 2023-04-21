/*
author: Laura 29/10
tested and compiling correctly
*/
#include <pyas/all.h>


static void find_the_part_instruction_basics( void ) {
  test_suite( "Basic test of find the part instruction");
  list_t l = list_new();
  list_t liste;

  l = list_add_last( l, lexem_new( "str", "ficelle", 1, 0 ) );
  l = list_add_last( l, lexem_new( "int", "43", 2, 9 ) );
  l = list_add_last( l, lexem_new( "dir::line", "1", 2, 9 ) );
  l = list_add_last( l, lexem_new( "int", "42", 2, 9 ) );
  l = list_add_last( l, lexem_new( "int", "65", 2, 9 ) );
  liste=l;


  find_the_part_instruction(&l); //pointeur sur le lexems

  test_oracle( list_print(l, lexem_print), "( [2:9:dir::line] 1 [2:9:int] 42 [2:9:int] 65 )",
          "The list begin with the first apparition of dir::line");

  list_delete(liste, lexem_delete);
}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  find_the_part_instruction_basics();

  exit( EXIT_SUCCESS );
}
