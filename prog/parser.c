
#include "../include/pyas/all.h"

/* le programme parser qui réalise l’analyse syntaxique d’un fichier .pys passé en argument
sur la ligne de commande*/

 int main (int argc, char* argv[]) {

   if(argc < 3){
     printf("Too few arguments. Put: \n");
     printf("./bin/perser.exe  data_base.txt   nom_fichier_a_lire  \n");
     return(EXIT_FAILURE);
   }

   char* file_name;
   char* data_base;
   data_base = argv[1];
   file_name = argv[2];

   list_t list = list_new();
   list = find_regexp( data_base, file_name);
   list_t save = list;// pointer to delete list at the end



   py_codeblock* codeblock = codeblock_new();
   pyobj_t obj=pyobj_new();


   list_t* lexems = &list;

   int i=fill_pys( lexems, codeblock );
   (obj)->py.codeblock = codeblock;

   //find_the_part_instruction(&list);
   int j=pyasm(obj,save);

     if (  i== 0 && j==0 )
     {
       print_pyobj(obj);
       print_codeblock(codeblock);
       printf("\nparsing ok\n");
       list_delete(save, lexem_delete);
       pyobj_delete(obj->py.codeblock->binary.trailer.lnotab);
       pyobj_delete(obj->py.codeblock->binary.content.bytecode);

       codeblock_delete(obj->py.codeblock);
       free(obj);
       exit( EXIT_SUCCESS );
     }

     else
     {
       printf("\nparsing error\n");
       list_delete(save, lexem_delete);
       pyobj_delete(obj->py.codeblock->binary.trailer.lnotab);
       pyobj_delete(obj->py.codeblock->binary.content.bytecode);
       codeblock_delete(obj->py.codeblock);
       free(obj);
       exit( EXIT_FAILURE );
     }
   }
