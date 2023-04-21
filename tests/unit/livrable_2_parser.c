
#include "../include/pyas/all.h"


 int main (int argc, char* argv[]) {

    if(argc < 3){
      printf("Too few arguments. Put: \n");
      printf("./bin/unit/test-lexer.exe  data_base.txt   nom_fichier_a_lire  \n");
      return(EXIT_FAILURE);
    }

    char* file_name;
    char* data_base;
    list_t list = list_new();
    data_base = argv[1];
    file_name = argv[2];


    list = find_regexp( data_base, file_name);
    list_t save = list;
    list_print ( list, lexem_print );

    printf("\n------------------------------------------------\n" );

    py_codeblock* codeblock = codeblock_new();
    list_t* lexems = &list;


     if (fill_pys( lexems, codeblock ) == 0)
     {
       printf("version_pyvm: %d\n", codeblock->version_pyvm);
       print_codeblock (codeblock);
       printf("detection ok\n");
       //codeblock_delete(codeblock);
       list_delete(save, lexem_delete);

       exit( EXIT_SUCCESS );
     }

     else
     {
       print_codeblock (codeblock);
       printf("detection fail\n");
       //codeblock_delete(codeblock);
       list_delete(save,lexem_delete);
       exit( EXIT_FAILURE );
     }
   }
