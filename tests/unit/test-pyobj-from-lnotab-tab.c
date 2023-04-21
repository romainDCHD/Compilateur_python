/*
author: Laura 05/11
tested and compiling correctly
*/
#include <pyas/all.h>

int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  // string_from_bytelist_basics();
  char lnotab[6];
  int taille=6;
  lnotab[0]=1;
  lnotab[1]=2;
  lnotab[2]=3;
  lnotab[3]=4;
  lnotab[4]=5;
  lnotab[5]=6;

  pyobj_t objet=pyobj_new();
  objet=pyobj_from_lnotab_tab(lnotab, taille);
  print_pyobj(objet);

  //Libération émmoire
  pyobj_delete(objet);
  exit( EXIT_SUCCESS );
}
