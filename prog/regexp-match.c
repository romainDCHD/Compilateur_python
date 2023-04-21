
#include <pyas/regexp.h>
#include <unitest/unitest.h>
#include <../include/pyas/all.h>

/*un programme qui match une expression régulière et une chaîne passées en argument sur la
ligne de commande et affiche le résultat*/

int main (int argc, char *argv[]) {

if(argc < 3){
  printf("Too few arguments. Put: \n");
  printf("./bin/regexp-match.exe   expression_reguliere    reference  \n");
  exit(EXIT_FAILURE);
}

char* data_in=argv[1];


if(*data_in=='\0'){
  printf("Error parsing regexp.\n");
  exit(EXIT_FAILURE);
}

queue_t queue = queue_new();
queue_t *queueptr = &queue;
int a = 0;

a = re_read_2( data_in, queueptr );
if(a == 0)
{
  exit(EXIT_FAILURE);
}

list_t l = queue_to_list( queue );
list_t save=l;
char * end=argv[2];
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
