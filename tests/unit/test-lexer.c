/*
 @file lexer.c
 @author Romain DUCHADEAU
 @date 21/09
 @brief final function. Two arguments: the assembler file and the name of the file wich is created and fill with info
 @progression: 0
 */

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

     printf(" you entered: DATABASE: %s, FILENAME: %s\n", data_base, file_name); //to see if test is ok
     printf("\n" );
     list = find_regexp( data_base, file_name);
     list_t save=list;
     printf("end of programm:\n" );
     list_print ( list, lexem_print );
     list_delete(save, lexem_delete);


     exit( EXIT_SUCCESS );
  }
