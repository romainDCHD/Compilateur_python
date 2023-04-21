/*
author: Laura 03/11
tested and compiling correctly
*/
#include <pyas/all.h>

int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  list_t bytecode=list_new();
  pyobj_t objet;
  bytecode=list_add_first(bytecode, lexem_new( "integer::dec", "1", 0, 0 ));
  bytecode=list_add_first(bytecode, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
  //Imaginons qu'il yest un label et donc 00 00
  bytecode=list_add_first(bytecode, lexem_new( "integer::dec", "0", 0, 0 ));
  bytecode=list_add_first(bytecode, lexem_new( "insn::0::0x59", "END_FINALLY", 0, 0 ) );

  bytecode = list_add_first( bytecode, lexem_new( "skip::blank", "", 1, 1 ) );
  bytecode=list_add_first(bytecode, lexem_new( "integer::dec", "1", 0, 0 ));
  bytecode=list_add_first(bytecode, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );
  list_t save=bytecode;

  objet=pyobj_from_bytecode_list( save);

  //Impression de l'objet
  print_pyobj(objet);

  //libération de la mméoire
  list_delete(save, lexem_delete);
  pyobj_delete(objet);
  exit( EXIT_SUCCESS );
}
