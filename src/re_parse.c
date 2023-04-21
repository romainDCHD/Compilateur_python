/*
-------------------------------------------------------
re_read : Take a  char* definition and return a queue of chargroup ( char * authorized_characters , occurence)
goal: thanks to that we can go form a inexploitable data (char* type , char* def ) to a
exploitable data (char* type , queue_t of char_group  {char* authorized caracters , operator_t occurence})
-------------------------------------------------------
*/
#include <../include/pyas/all.h>

//en cas de crochets
void read_crochet(char *data_in, char_group *chargroup ){
  int i = 0;
  int ascii_1 = 0;
  int ascii_2 = 0;
  int count = 0;
  int buffer = 0;

  while (data_in[count] != ']')
  {

    //if '\'
    if (data_in[count] == '\\')
    {
      count ++;
      if (data_in[count] == 't')
      {
        buffer = (int)'\t';
        chargroup->group[buffer] = 1;
      }

      else if (data_in[count] == 'n')
      {
        buffer = (int)'\n';
        chargroup->group[buffer] = 1;
      }
      else if (data_in[count] != 't')
      {
        buffer = (int) data_in[count];
        chargroup->group[buffer] = 1;
      }
    }
//---------------------
    // if '-'
    else if (data_in[count] == '-')
    {
      ascii_1 = data_in[count-1];
      ascii_2 = data_in[count+1];

      if (ascii_2 - ascii_1 < 0)
      {
        printf ("invalid syntax : cannot put '[a-0]' for instance\n");
      }

      for (i = ascii_1 + 1; i < ascii_2 + 1 ; i++)
      {
        buffer = i;
        chargroup->group[buffer] = 1;
      }
    }

//-----------------------
    //in all the other case
    else
    {
      buffer = (int) data_in[count];
      chargroup->group[buffer] = 1;
    }

    count ++;
  } //end while
}//end read_crochet


queue_t fillchargroup (queue_t queue,char_group *chargroup){  //pour remplir la queue correctement

  char_group* cg = new_char_group();

  int i = 0;
  for ( i = 0; i < 256; i++ )
  {
    cg->group[i] = chargroup->group[i];
  }

  cg->op = chargroup->op;
  queue = enqueue( queue, cg );
  free(chargroup);
  return queue;
}


//fonction principale
queue_t re_read(char *data_in){

  queue_t queue = queue_new();
  char *ptr = data_in;
  int buffer = 0;
  int i = 0;
  ptr ++; //le mettre un cran en avant


  while( *data_in != '\0' ) //pour toute la chaine de caratère
  {
    char_group *chargroup = new_char_group(); //creer le nouveau chargroup qu'on veut remplir

//----------------------------------------------------
    //case '\'
    if (*data_in == '\\')
    {
      data_in ++;
      ptr ++;

      if (*data_in == 't')
      {
        buffer = (int)'\t';
        chargroup->group[buffer] = 1;
      }

      else if (*data_in == 'n')
      {
        buffer = (int)'\n';
        chargroup->group[buffer] = 1;
      }

      else if (*data_in != 't')
      {
        buffer = (int) *data_in;
        chargroup->group[buffer] = 1;
      }

      switch( *ptr )
      {
        case '+' :
        chargroup->op = OP_ONE_OR_MORE ;
        break;
        case '*' :
        chargroup->op = OP_ZERO_OR_MORE ;
        break;
        case '?' :
        chargroup->op = OP_ZERO_OR_ONE ;
        break;
        default : chargroup->op = OP_ONE ;
      }
      queue=fillchargroup(queue,chargroup);
      data_in ++; //avancer au prochain caractère
      ptr ++;
    }

//----------------------------------------------------
    //case '['
    else if ( *data_in == '[' )
    {
      data_in ++; //se placer après le crochet

      if (*data_in == '\0' || *ptr == '\0')
      {
        printf ( "sythax error : cannot finish by '['\n" );
      }

      read_crochet( data_in , chargroup );  //fill chargroup->group

      while (*data_in != ']') // se mettre à la fin des crochets
      {
       data_in ++;
       if (data_in == NULL){
         //perror ("sythax error : you must close the []\n");
       }
      }
      ptr = data_in;
      ptr ++;

      //fill chargroup->op
      switch( *ptr )
      {
        case '+' :
        chargroup->op =OP_ONE_OR_MORE ;
        data_in ++;
        ptr ++;
        break;
        case '*' :
        chargroup->op =OP_ZERO_OR_MORE ;
        data_in ++;
        ptr ++;
        break;
        case '?' :
        chargroup->op =OP_ZERO_OR_ONE ;
        data_in ++;
        ptr ++;
        break;
        default : chargroup->op =OP_ONE ;
      }

      queue=fillchargroup(queue,chargroup); //mettre le chargroup rempli dans la queue
      data_in ++; //avancer au prochain caractère
      ptr ++;
    }

//----------------------------------------------------
  //case '^'
    else if (*data_in == '^')
    {
      //se mettre après le ^
      data_in ++;
      ptr ++;

      //si crochets
      if( *data_in == '[' )
      {
        data_in ++;
        read_crochet( data_in , chargroup );

        while (*data_in != ']')
        {
         data_in ++;
         if (data_in == NULL)
         {
           printf ("sythax error : you must close the []\n");
         }
        }
        //data_in ++;
        ptr = data_in;
        ptr ++;
      }

      //error case
      else if ( *data_in == '^' || *data_in == '+' || *data_in == '-' || *data_in == '?' || *data_in == '\\')
      {
       printf ("synthax error : can't put ^+ or ^? for instance");
      }

      //general case
      else
      {
        buffer = (int) *data_in;
        chargroup->group[buffer] = 1;
      }

      chargroup->op =OP_ZERO;
      queue=fillchargroup(queue,chargroup);
      data_in ++;
      ptr ++;
    }

//----------------------------------------------------
    //general case
    else
    {

      //si au bout et signe
      if ( (*data_in == '?' || *data_in == '+' || *data_in == '*') && *ptr == '\0')
      {
       data_in ++;
      }

      else
      {
        //fill chargroup->group
        if( *data_in == '.' )
        {
          for (i = 0; i < 256; i++)
          {
            chargroup->group[i] = 1;
          }
        }

        else
        {
        buffer = (int) *data_in;
        chargroup->group[buffer] = 1;
        }

        //fill chargroup->op
        switch( *ptr )
        {
          case '+' :
          chargroup->op =OP_ONE_OR_MORE ;
          data_in ++;
          ptr ++;
          break;
          case '*' :
          chargroup->op =OP_ZERO_OR_MORE ;
          data_in ++;
          ptr ++;
          break;
          case '?' :
          chargroup->op =OP_ZERO_OR_ONE ;
          data_in ++;
          ptr ++;
          break;
          default : chargroup->op =OP_ONE ;
        }

        queue=fillchargroup(queue,chargroup);
        data_in ++;
        ptr ++;
      }
    }

  }//end while
  return queue;
}//end re_read
