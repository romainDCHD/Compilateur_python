

#include <../include/pyas/all.h>




data_t data_new( char* type, char* def) {
  data_t d = calloc( 1, sizeof( *d ) );
  assert( d );

  if ( type  && *type  ) d->type  = strdup( type );
  if ( def && *def ) d->def = strdup( def );

  return d;
}

int data_delete( void* data_in){
  data_t data = data_in;
  if(data)
  {
    free( data->type);
    free(data->def);
  }
  free( data );
  return 0;
}


int print_data_t( void * dat) {
  data_t data = dat;
  return printf( "[type: '%s', def: '%s']\n", data->type, data->def);
}



queue_t read_database (char* file_name){

  FILE *fp = fopen( file_name, "rt" );
  queue_t q = queue_new();
  char blank[256];
  char blank_1[256];
  char blank_2[256];
  char type[256];
  char def[256];

  if (fp==NULL) {
    puts("Error : cannot open file");
    exit(EXIT_FAILURE);}
  else
  {


    fscanf(fp, "%s %s %s",blank,blank_1,blank_2);
    /*concatinate blank_1 and blank_2:*/
    strcat(blank_1," ");
    strcat(blank_1,blank_2);
    data_t reg_blank = data_new(blank,blank_1);
    q = enqueue(q,reg_blank);



     while(fscanf(fp,"%s  %s",type,def)==2){

      data_t reg = data_new(type,def);
      q = enqueue(q,reg);
    }
  }


  fclose(fp);
  return q;
}
