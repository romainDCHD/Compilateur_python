

#include "../include/pyas/all.h"


int main (int argc, char* argv[]) {

  if(argc < 2){
    printf("Too few arguments. Put: \n");
    printf("./bin/unit/test-parse.exe  database.txt.test  \n");
    return(EXIT_FAILURE);
  }

  printf("you entered : %s\n", argv[1] );

  queue_t queuedb = read_database( argv[1] );

  int lenghtdb = queue_length (queuedb );
  int i = 0;

  data_t data = queue_peek(queuedb);
  // data_t data = dataptr;


  for ( i = 0; i < lenghtdb; i++)
  {
    printf("---------------------------------------------\n" );
    printf("data->type: %s     data->def: %s\n", data->type, data->def);
    queue_t queuecg = queue_new ();
    queuecg = re_read( data->def );
    queue_print (queuecg, char_group_print );
    queuedb = queue_next(queuedb);
    data = queue_peek(queuedb);
    // data = dataptr;
    queue_delete( queuecg, delete_char_group );
  }

  queue_delete(queuedb, data_delete);



  exit( EXIT_SUCCESS );
}
