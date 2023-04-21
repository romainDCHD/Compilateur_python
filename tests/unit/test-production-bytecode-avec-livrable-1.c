/*
author: Laura 12/11
tested and compiling correctly
*/

#include "../include/pyas/all.h"


 int main (int argc, char* argv[]) {
    //calling lexer Fonction
    if(argc < 3){
      printf("Too few arguments. Put: \n");
      printf("./bin/unit/test-lexer.exe  data_base.txt   nom_fichier_a_lire  \n");
      return(EXIT_FAILURE);
    }

    char* file_name;
    char* data_base;
    data_base = argv[1];
    file_name = argv[2];

    list_t list = list_new();
    pyobj_t code=pyobj_new();
    code->py.codeblock=codeblock_new();

    list = find_regexp( data_base, file_name);
    list_t save = list; //pour faire ma fonction après avoir affiché au préalable la liste

    int valeur_retour=pyasm(code, save);
    printf("valeur de retour pyasm : %d", valeur_retour);
    print_pyobj(code->py.codeblock->binary.content.bytecode);
    print_pyobj(code->py.codeblock->binary.trailer.lnotab);

    printf("valeur de first_lineno : %d", code->py.codeblock->binary.trailer.firstlineno);

    //Libération de la mémoire
    list_delete(save, lexem_delete);
    pyobj_delete(code->py.codeblock->binary.trailer.lnotab);
    pyobj_delete(code->py.codeblock->binary.content.bytecode);

    codeblock_delete(code->py.codeblock);
    free(code);
    return(EXIT_SUCCESS);

  }
