/*
author: Laura 05/11
tested and compiling correctly
*/
#include <pyas/all.h>

static void lenght_lnotab_basics( void ) {
  test_suite( "Basic test of lenght_lnotab module");
  list_t lnotab=list_new();
  list_t lnotab2=list_new();

  lnotab=list_add_last(lnotab, lexem_new( "dir::line", ".line", 0, 0 ) );
  lnotab=list_add_last(lnotab, lexem_new( "integer::dec", "1", 0, 0 ));
  lnotab=list_add_last(lnotab, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

  lnotab=list_add_last(lnotab, lexem_new( "dir::line", ".line", 0, 0 ) );
  lnotab=list_add_last(lnotab, lexem_new( "integer::dec", "1", 0, 0 ));
  lnotab=list_add_last(lnotab, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

  lnotab=list_add_last(lnotab, lexem_new( "dir::line", ".line", 0, 0 ) );
  lnotab=list_add_last(lnotab, lexem_new( "integer::dec", "3", 0, 0 ));
  lnotab=list_add_last(lnotab, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

  lnotab=list_add_last(lnotab, lexem_new( "dir::line", ".line", 0, 0 ) );
  lnotab=list_add_last(lnotab, lexem_new( "integer::dec", "4", 0, 0 ));
  lnotab=list_add_last(lnotab, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

  lnotab=list_add_last(lnotab, lexem_new( "dir::line", ".line", 0, 0 ) );
  lnotab=list_add_last(lnotab, lexem_new( "integer::dec", "5", 0, 0 ));
  lnotab=list_add_last(lnotab, lexem_new( "symbol", "label", 0, 0 ) );

  list_t save=lnotab;

  test_assert( lenght_lnotab(lnotab) == 8,
         "test lenght lnotab working\n" );

   lnotab2=list_add_last(lnotab2, lexem_new( "dir::line", "1", 0, 0 ) );
   lnotab2=list_add_last(lnotab2, lexem_new( "integer::dec", "1", 0, 0 ));
   lnotab2=list_add_last(lnotab2, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

   lnotab2=list_add_last(lnotab2, lexem_new( "dir::line", "2", 0, 0 ) );
   lnotab2=list_add_last(lnotab2, lexem_new( "integer::dec", "1", 0, 0 ));
   lnotab=list_add_last(lnotab2, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

   lnotab2=list_add_last(lnotab2, lexem_new( "dir::line", "3", 0, 0 ) );
   lnotab2=list_add_last(lnotab2, lexem_new( "integer::dec", "1", 0, 0 ));
   lnotab=list_add_last(lnotab2, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

   lnotab2=list_add_last(lnotab2, lexem_new( "dir::line", "4", 0, 0 ) );
   lnotab2=list_add_last(lnotab2, lexem_new( "integer::dec", "1", 0, 0 ));
   lnotab2=list_add_last(lnotab2, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

   lnotab2=list_add_last(lnotab2, lexem_new( "dir::line", "5", 0, 0 ) );
   lnotab2=list_add_last(lnotab2, lexem_new( "integer::dec", "1", 0, 0 ));
   lnotab2=list_add_last(lnotab2, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ) );

   lnotab2=list_add_last(lnotab, lexem_new( "symbol", "label", 0, 0 ) );

   list_t save2=lnotab2;

   test_assert( lenght_lnotab(lnotab) == 8,
          "test lenght lnotab working\n" );

  //lIBÉRATION MÉMOIRE
  list_delete(save, lexem_delete);
  list_delete(save2, lexem_delete);
}

int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  lenght_lnotab_basics();


  exit( EXIT_SUCCESS );
}
