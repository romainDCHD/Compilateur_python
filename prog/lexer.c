


#include "../include/pyas/all.h"

/*le programme lexer qui réalise l’analyse lexicale d’un fichier .pys passé en argument sur la
ligne de commande*/
int main (int argc, char* argv[]) {

  if(argc < 3){
    printf("Too few arguments. Put: \n");
    printf("./bin/lexer.exe    data_base.txt   nom_du_.pys_a_lire(dans le repertoire functions)  \n");
    exit(EXIT_FAILURE);
  }

  char* file_name;
  char* data_base;
  list_t list = list_new();
  data_base = argv[1];
  file_name = argv[2];

  list = find_regexp( data_base, file_name);
  list_t save=list;
  list_print ( list, lexem_print );
  if (list == NULL)
   {
     list_delete(save, lexem_delete);//liberation de memoire
     exit( EXIT_FAILURE );
   }

  else
  {
    list_delete(save,lexem_delete);//liberation de memoire
    exit( EXIT_SUCCESS );
  }


}
