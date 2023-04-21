/*
 @filetest-treatAss
 @author Romain DUCHADEAU
 @date 21/09
 @brief Unit tests for treatAss
 @progression: lack some function, not finish at all
 */


 #include <pyas/regexp.h>
 #include <unitest/unitest.h>
 #include "../include/pyas/all.h"


 int main (int argc, char* argv[]) {

   if(argc < 2){
     printf("Too few arguments. Put: \n");
     printf("./bin/unit/test-database2.exe  nom_fichier_a_lire  \n");
     return(EXIT_FAILURE);
   }


   queue_t queue = read_database(argv[1]);  //ouvre le fichier et le met dans un queue
   queue_print(queue, print_data_t );
   queue_delete(queue, data_delete);

   exit( EXIT_SUCCESS );
 }
