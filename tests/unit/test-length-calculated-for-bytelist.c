/*
author: Laura 03/11
tested and compiling correctly
*/
#include <pyas/all.h>

static void   length_calculated_for_bytelist_basics( void ) {
  test_suite( "Basic test of   length_calculated_for_bytelist module");


  list_t bytecode=list_new();

  bytecode=list_add_first(bytecode, lexem_new( "integer::dec", "1", 0, 0 ));
  bytecode=list_add_first(bytecode, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
  list_t save=bytecode;
  test_assert( length_calculated_for_bytelist(bytecode) == 3,
         "test lenght bytelist working\n" );

 list_t byte=list_new();

 byte=list_add_first(byte, lexem_new( "insn::0::0x66", "BUILD_TUPLE", 0, 0 ) );
 byte=list_add_first(byte, lexem_new( "insn::0::0x66", "BUILD_TUPLE", 0, 0 ) );
 list_t save2=byte;

 test_assert( length_calculated_for_bytelist(byte) == 2,
        "test 2 lenght bytelist working\n" );

  list_t bytec=list_new();
  bytec=list_add_first(bytec, lexem_new( "integer::dec", "1", 0, 0 ));
  bytec=list_add_first(bytec, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
  bytec=list_add_first(bytec, lexem_new( "insn::0::0x66", "BUILD_TUPLE", 0, 0 ) );
  bytec = list_add_first( bytec, lexem_new( "skip::comment", "", 1, 1 ) );
  bytec=list_add_first(bytec, lexem_new( "integer::dec", "1", 0, 0 ));
  bytec=list_add_first(bytec, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
  bytec = list_add_first( bytec, lexem_new( "skip::blank", "", 1, 1 ) );
  bytec=list_add_first(bytec, lexem_new( "integer::dec", "1", 0, 0 ));
  bytec=list_add_first(bytec, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
  bytec=list_add_first(bytec, lexem_new( "insn::0::0x66", "BUILD_TUPLE", 0, 0 ) );
  list_t save3=bytec;

  test_assert( length_calculated_for_bytelist(bytec) == 11,
         "test 3 lenght bytelist working\n" );

 list_t bytec_avec_label=list_new();
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "integer::dec", "1", 0, 0 ));
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
 //Imaginons quil y avaut un label
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "integer::dec", "0", 0, 0 ));
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "insn::0::0x66", "BUILD_TUPLE", 0, 0 ) );

 bytec_avec_label = list_add_first( bytec_avec_label, lexem_new( "skip::comment", "", 1, 1 ) );
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "integer::dec", "1", 0, 0 ));
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
 bytec_avec_label = list_add_first( bytec_avec_label, lexem_new( "skip::blank", "", 1, 1 ) );
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "integer::dec", "1", 0, 0 ));
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
 bytec_avec_label=list_add_first(bytec_avec_label, lexem_new( "insn::0::0x66", "BUILD_TUPLE", 0, 0 ) );
 list_t save4=bytec_avec_label;

 test_assert( length_calculated_for_bytelist(bytec_avec_label) == 13,
        "test 3 lenght bytelist working\n" );

  list_delete(save, lexem_delete);
  list_delete(save2, lexem_delete);
  list_delete(save3, lexem_delete);
  list_delete(save4, lexem_delete);
}

int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  length_calculated_for_bytelist_basics();

  exit( EXIT_SUCCESS );
}
