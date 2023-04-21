/*
author: Laura
tested and compiling correctly
*/
#include "../include/pyas/all.h"

//Ce test permet d'afficher la strcuture label_adress_t et avec valgrind voir si elle est bien supprimée
int main (void) {

char* name = "label_0";
int address = 32;
int ad=92;

label_address_t label = label_address_new( name, address, ad );
label_address_print( label);
label_address_delete( label);


exit( EXIT_SUCCESS );
}
