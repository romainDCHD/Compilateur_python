/*
author: Laura 3/11
tested and compiling correctly
*/
#include <pyas/all.h>


static void opcode_is_basics( void ) {
  test_suite( "Basic test of the function argument_yes_or_no");

  lexem_t lex_opcode_1=lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 );
  lexem_t lex_opcode_2=lexem_new( "insn::0::0x01", "POP_TOP", 0, 0 );


  test_assert( argument_yes_or_no(lex_opcode_1) == 1,
         "test 1 argument_yes_or_no working\n" );


  test_assert( argument_yes_or_no(lex_opcode_2) == 0,
         "test 2 argument_yes_or_no working\n" );

//Libération mémoire
  lexem_delete(lex_opcode_1);
  lexem_delete(lex_opcode_2);


}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );
  opcode_is_basics();

  exit( EXIT_SUCCESS );
}
