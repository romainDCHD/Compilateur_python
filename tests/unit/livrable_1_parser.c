

#include "../include/pyas/all.h"

int main (int argc, char* argv[]) {

  if(argc < 2){
    printf("Too few arguments. Put: \n");
    printf("./bin/unit/test-parse.exe  expression_a_parser  \n");
    return(EXIT_FAILURE);
  }

  char* data = argv[1];
  // printf("data: %s\n", data);

  queue_t queuecg = queue_new ();

  queuecg = re_read( data );
  // queue_print (queuecg, char_group_print);
  // char_group_print(queue_peek(queuecg));
  if(queue_empty(queuecg) == 0)
  {
    queue_visit (queuecg, char_group_print);
    queue_delete(queuecg, delete_char_group);//liberation de memoire.
    exit( EXIT_SUCCESS );
  }

  else
  {
    queue_delete(queuecg, delete_char_group);//liberation de memoire.
    exit( EXIT_FAILURE );
  }

}
