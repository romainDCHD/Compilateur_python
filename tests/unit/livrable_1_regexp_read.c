/**
 * @file regexp.c
 * @author Melissa AKIKI
 * @date Sun Aug  7 21:22:53 2022
 * @brief Unit tests for regexps.
 *
 * Unit tests for regexps.
 */

#include <pyas/regexp.h>
#include <unitest/unitest.h>
#include <../include/pyas/all.h>


int main (int argc, char *argv[]) {

if(argc < 3){
  //printf("Too few arguments. Put: \n");
  //printf("./bin/unit/test-parse.exe     data_in     end \n");
  printf("Error parsing regexp.\n");
  return(EXIT_FAILURE);
}

char* data_in=argv[1];


if(*data_in=='\0'){
  printf("Error parsing regexp.\n");
  return(EXIT_FAILURE);
}

queue_t queue = queue_new();

queue = re_read(data_in);

list_t l = queue_to_list( queue );
list_t save=l;
//char* source=".interned  klz";

char * end=argv[2];
//char *source="\n";
//printf("source:%sendsource\n",source);
//printf("list print :\n" );
//list_print (l, char_group_print );

int is_match=re_match_cg( l, argv[2], &end );

if ( is_match ) {
  printf( "The start of '%s' is %s, %s: '%s'.\n", argv[2], argv[ 1 ], *end ? "next" : "END", end );

}

else {
  if(argv[2]==NULL){
    printf( "The start of '%s' is *NOT* %s.\n", argv[2], argv[ 1 ] );
  }
  else{
    printf( "The start of '%s' is *NOT* %s.\n", argv[2], argv[ 1 ] );
  }


}

list_delete(save, delete_char_group); //il ne faut libérer que liste car queue et elle ont les mes éléments
exit( EXIT_SUCCESS );

}
