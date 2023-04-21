/*
author: Laura
tested and compiling correctly
*/
#include <unitest/unitest.h>
#include "../include/pyas/all.h"

static void cg_basics( void ) {
   test_suite( "Basic test of char_group module, (new_char_group, delete_char_group, char_group_print)" );

 char_group *cg = new_char_group();
  printf("impression d'une new char_group\n");
  char_group_print(cg);


   test_oracle( char_group_print(cg), "One in '' one time.\n",
 	       "Good initialisation of char_group");

   cg->group[33] = 1; //33 -> 3
   cg->op=OP_ONE_OR_MORE;

   test_oracle( char_group_print(cg), "One in '!,' one or more time.\n",
 	       "Can print a char_group with OP_ONE_OR_MORE");

   char_group_print(cg);
   cg->group[109] = 1;  //109 -> m
   cg->op=OP_ZERO_OR_MORE;

   char_group_print(cg);

   test_oracle( char_group_print(cg), "One in '!,m,' zero or more time.\n",
 	       "Can print a char_group with OP_ZERO_OR_MORE");

   cg->group[109] = 0;
   cg->op=OP_ZERO_OR_ONE;

   test_oracle( char_group_print(cg), "One in '!,' zero or one time.\n",
          "Can print a char_group with OP_ONE_OR_ONE");

  cg->group[86] = 1;  //V
  cg->op=OP_ZERO;

  test_oracle( char_group_print(cg), "One in '!,V,' zero time.\n",
        "Can print a char_group with OP_ZERO");

  //free memory
  delete_char_group(cg);

 }
int main ( int argc, char *argv[] ) {
  unit_test( argc, argv );

  cg_basics();
  exit( EXIT_SUCCESS );
}
