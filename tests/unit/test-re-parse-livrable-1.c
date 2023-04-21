
#include "../include/pyas/all.h"

/* le programme qui lit (parse) une expression régulière passée en argument sur la ligne de
commande et affiche sa structure */

int main (int argc, char* argv[]) {

  if(argc < 2){
    printf("Too few arguments. Put: \n");
    printf("./bin/unit/test-parse.exe  expression_a_parser  \n");
    exit(EXIT_FAILURE);
  }

  char* data = argv[1];
  printf("data: '%s'\n", data);
  int a = 0;

  queue_t queuecg = queue_new ();
  queue_t *queueptr = &queuecg;

  a = re_read_2( data, queueptr );
  queue_print (queuecg, char_group_print);
  // char_group_print(queue_peek(queuecg));
  if(a == 1)
  {
    queue_visit (queuecg, char_group_print);
    queue_delete(queuecg, delete_char_group);//liberation de memoire.
    exit( EXIT_SUCCESS );
  }

  else
  {
    // queue_delete(queuecg, delete_char_group);//liberation de memoire.
    exit( EXIT_FAILURE );
  }

}
