/*
author: Laura 21/09
tested and compiling correctly
*/
#include <pyas/all.h>


static void opcode_is_basics( void ) {
  test_suite( "Basic test of the function opcode_is");

  lexem_t lex_opcode_1=lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 );
  lexem_t lex_opcode_2=lexem_new( "insn::0::0x01", "POP_TOP", 0, 0 );


  test_assert( opcode_is(lex_opcode_1) == 0x66,
         "test 1 opcode_is working\n" );


  test_assert( opcode_is(lex_opcode_2) == 0x01,
         "test 2 opcode_is working\n" );

   test_assert( *opcode_is_char(lex_opcode_2) == 0x01,
          "test 2 opcode_is_char working\n" );

  // test_oracle( *opcode_is_char(lex_opcode_2), "01",
  //        "test 2 opcode_is working\n" );

  lexem_delete(lex_opcode_1);
  lexem_delete(lex_opcode_2);


}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );
  opcode_is_basics();

  exit( EXIT_SUCCESS );
}
