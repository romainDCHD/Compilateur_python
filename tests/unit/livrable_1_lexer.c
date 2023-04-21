

#include "../include/pyas/all.h"


int main (int argc, char* argv[]) {

  if(argc < 3){
    printf("Too few arguments. Put: \n");
    printf("./bin/unit/test-lexer.exe    data_base.txt   nom_du_.pys_a_lire(dans le repertoire functions)  \n");
    return(EXIT_FAILURE);
  }

  char* file_name;
  char* data_base;
  list_t list = list_new();
  data_base = argv[1];
  file_name = argv[2];

  list = find_regexp( data_base, file_name);
  list_t save=list;
  list_print ( list, lexem_print );

     list_delete(save, lexem_delete);//liberation de memoire
     exit( EXIT_FAILURE );





}
