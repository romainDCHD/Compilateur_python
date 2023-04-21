/* le programme pyas qui réalise l’assemblage d’un fichier .pys passé en argument sur la
ligne de commande et génère le fichier binaire pyas.pyc correspondant

* step 1: fill pyobj_test
* step 2: generate bitecode from terminal which will be the true one
* step 3: call write_bitecode and compare with original

*/

#include "../include/pyas/all.h"

 int main (int argc, char* argv[]) {

   //calling lexer Fonction
    if(argc < 4){
      printf("Too few arguments. Put: \n");
      printf("./bin/pyas.exe  data_base.txt   nom_fichier_a_lire  nom_fichier_destination\n");
      return(EXIT_FAILURE);
    }


    char* file_name;
    char* data_base;
    data_base = argv[1];
    file_name = argv[2];

    list_t list = list_new();
    list = find_regexp( data_base, file_name);
    list_t save = list;// pointer to delete list at the end

    // now livrable 2-3
    FILE *fp=NULL;
    fp=fopen(argv[3],"w");

    if(fp==NULL){
      printf("failed to create file\n");
      exit( EXIT_FAILURE );
    }


    py_codeblock* codeblock = codeblock_new();
    pyobj_t obj=pyobj_new();


    list_t* lexems = &list;

    int i=fill_pys( lexems, codeblock );
    (obj)->py.codeblock = codeblock;

    //find_the_part_instruction(&list);
    int j=pyasm(obj,save);

    if (  i== 0 && j==0 )
    {
      pyobj_write(fp,obj);
      list_delete(save, lexem_delete);
      pyobj_delete(obj->py.codeblock->binary.trailer.lnotab);
      pyobj_delete(obj->py.codeblock->binary.content.bytecode);

      codeblock_delete(obj->py.codeblock);
      free(obj);
      fclose(fp);
      //codeblock_delete(codeblock);
      exit( EXIT_SUCCESS );
    }

    else
    {
      //print_codeblock (codeblock);
      printf("Failed to fill\n");
      //codeblock_delete(codeblock);
      list_delete(save, lexem_delete);
      pyobj_delete(obj->py.codeblock->binary.trailer.lnotab);
      pyobj_delete(obj->py.codeblock->binary.content.bytecode);

      codeblock_delete(obj->py.codeblock);
      free(obj);
      fclose(fp);
      exit( EXIT_FAILURE );
    }
 }
