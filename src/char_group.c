//----------------------------------
//definition of funtions for char_group_print
//----------------------------------

#include <../include/pyas/all.h>


//create and alloc a new char_group
char_group* new_char_group(){
  char_group *chargroup = calloc( 1, sizeof( char_group ) );

  int i =0;
  for ( i = 0; i < 256; i++) {
    chargroup->group[i] = 0;
  }

  chargroup->op = OP_ONE;
  return chargroup;
}

void char_group_initialize( char_group *chargroup){
  int i =0;
  for ( i = 0; i < 256; i++) {
    chargroup->group[i] = 0;
  }

  chargroup->op = OP_ONE;
}


//delete a char_group type

int delete_char_group ( void *cg ){
  free( cg );
  return 0;
}


//print a char_goup type
int char_group_print( void *cgx ) {
  char_group *cg = cgx ;
  int i = 0;

  printf( "One in \"" );
  for ( i = 0; i < 256; i++) {
    if( cg->group[i] == 1 ){
      printf("%c",(char) i );
    }
    else if( cg->group[i] != 0 ){
      printf( "error\n");
    }
  }

  printf( "\", ");

  switch( cg->op ) {
    case OP_ONE :
    printf( "one time" );
    break;
    case OP_ONE_OR_MORE :
    printf( "one or more times" );
    break;
    case OP_ZERO_OR_MORE :
    printf( "zero or more times" );
    break;
    case OP_ZERO_OR_ONE :
    printf( "zero or one time" );
    break;
    case OP_ZERO :
    printf( "zero time" );
    break;
  }
  printf( ".\n" );
  return 1;
}
