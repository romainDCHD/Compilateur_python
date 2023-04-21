//si le end est sur NULL il faut passer à la ligen d'après

#include <../include/pyas/all.h>




list_t find_regexp(char* db, char* source_file)
{
  FILE* fp = fopen(source_file,"r");
  if (fp==NULL)
  {
    puts("Error : impossible to open the file");
    return NULL;
  }


  char* line = calloc(1024,sizeof(char));
  char* word = calloc(256,sizeof(char));
  queue_t data_t_defs = queue_new();
  int counter_line = 0;
  int counter_column = 0;
  list_t final_list = list_new();//la liste final a rendre
  char* copy_type = "";
  char* current = line;
  int database_lenght = 0;
  int i = 0;
  data_t data;
  char* end = NULL;


  data_t_defs = read_database(db);//ranger regexp-file dans une queue de data_t
  database_lenght = queue_length( data_t_defs );

  while (fgets(line,1024,fp)!= NULL) //temps qu'on lit le fichier assembleur
  {
      counter_line ++;
      counter_column = 0;
      current = line;
      // printf("--------------------------------------------------------\n" );
      // printf("new line: line: %d , content: %s \n", counter_line, current);
      //number_car = 0;


   while( *current != 0 ) //tant qu'on est pas au bout de la ligne (ie current != NULL)
   {
      i = 0;

      //printf("database_lenght: %d\n", database_lenght);
      queue_t queue = queue_new();//temporary queue to fill in regexps (cad-> prendre un element de lexem_def qui est de type data_t et le transformer en une queue de regexp a l'aide la fonction re_read)
      data= queue_peek(data_t_defs);

      // printf("data:    ");
      // print_data_t ( data );
      queue = re_read( data->def ); //def de la premiere data en queue de chargroup

      //queue_print ( queue, char_group_print );
      //printf("queue de data initiale:\n" );
      //queue_print( data_t_defs, print_data_t );
      // printf("queue is empty : %s\n", queue_empty(data_t_defs));
      //printf("current: '%s'\n",current );
      list_t l=queue_to_list(queue);// to be able to delete it and free memory

  //_________________________algorithm commence ici_____________________________________________________________
      while( (re_match_cg( l, current , &end)) == 0 && i <= database_lenght )
      {
         // printf("end boucle : '%s'\n", end );
        //queue_delete ( queue );
         // printf("______begin______\n");
        list_delete(l, delete_char_group);//liberer la memoire a chaque fois
        data_t_defs = queue_next(data_t_defs);  //passer à la prochaine data
        data = queue_peek(data_t_defs);
        // data = dataptr;
        queue=re_read( data->def ); //prendre la def et mettre en chargroup
        //queue_print ( queue, char_group_print );
        //list_t t=list_new();
        //data_delete(data);
        l=queue_to_list(queue);//update the list each time


        // printf("queue de data intermediaire:\n" );
        // queue_print( data_t_defs, print_data_t );
        i++;

      }
      list_delete(l, delete_char_group);//liberer la memoire une fois finis
        // printf("end: '%s'\n", end );
        // printf("\n");

        copy_type = data->type ;  //sauvegarder le type trouvé
        // printf("print data :    ");
        // print_data_t (data );

        //In case no match -> syntax error
        if (i > database_lenght )
        {
            printf("Synthaxe error : %s  at : line %d  column %d of %s \n", current, counter_line, counter_column, source_file);
            queue_delete(data_t_defs, data_delete );
            fclose(fp);
            free(line);
            free(word);

            return NULL;
        }

        //matching ok
        else
        {
          //de current jusqu'à end
          int j = 0;
          while (current[j] != *end )
          {
            j++;
          }
          char buffer[j];
          strncpy (buffer, current,j );
          buffer[j] = '\0';
          // printf("buffer :'%s'\n", buffer);
          // printf("counter_line: %d, counter_column: %d, copy_type: %s, word: %s\n",counter_line, counter_column,copy_type  ,buffer);
          lexem_t add_lex = lexem_new(copy_type, buffer, counter_line, counter_column); //stocker les infos sous forme de lexem
          final_list = list_add_last( final_list, add_lex );  //mettre dans une liste
          // printf("final list :\n");
          // list_print ( final_list, lexem_print );

          counter_column = counter_column + strlen ( buffer ); // avancer le compteur colonne pour le suivant
          current = end;
          // printf("current = end : '%s'\n",current );

          //free(buffer);
        }
        //queue_delete ( queue , delete_char_group );

        // data_delete(data);
    }//end while lignes

  }//end while fichier .pys


//____________pour alleger la memoire_________________________

//free(data);

queue_delete(data_t_defs, data_delete );
fclose(fp);
free(line);
free(word);
return final_list;

}
