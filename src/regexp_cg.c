
// @brief define the "mathematical" symbol and make the function who permite to know if the enter is a valid lexem
//@author Melissa AKIKI



#include <stdio.h>
#include <string.h>
#include <../include/pyas/all.h>


/*___________fonction to check if two char* are identical according to our definition________________*/
static int is_equal( char *c, char *s) {

uint i=0;
for(i=0;i<strlen(c);i++)
{
  if(c[i]==*s || (c[i]=='~' && s[i]!='\0')){

    return 1;
  }
}

return 0;
}


/*______________convert int[] to its corresponding asci table________________*/
char *asci( int *cg) {


char *c = calloc( 256, sizeof( char ) );
//initialise
uint i=0;
for(i=0;i<256;i++){
  c[i]=0;
}
//search for characters
int j=0;
for(i=0;i<256;i++)
{
  if(cg[i]==1){
    c[j] = i;
    j++;
  }
  //au cas ou tous les charcters sont allumer, sela signifie un point
  if(j==255){
    j=0;
    c[j]='~';

  }
}
//c[j+1]='\0';
//free(cg);
return c;
}


/*___________________________definition of *___________________________________________*/
static int re_match_zero_or_more( list_t regexpp,char * source , char ** end,char *c  ) {

 //printf("_______________________*\n");
  char *t = source;

  while ( '\0' != *t && is_equal(c,t) ) {
    t++;
  }

//initialize *end pointer to where its supposed to be in all cases a*b*c* : aabbccczyx *end->zyx
  char*tt=t;

        do{  tt--;
          //printf("c bon _______________________%s,%c\n",tt,*c);
        }while(!is_equal(c,tt));
        tt++;
        *end=tt;

        //particuler case of a*
        if(list_next(regexpp)==NULL && !is_equal(c,source)){
        *end=source;
        free(c);
          return 1;
        }
//if i arrive at the end of my regexp and i have a * thus it is always true and my end points where its supposed to be from loop before
  if(list_next(regexpp)==NULL){
    free(c);
    return 1;
  }

  do {
    if( re_match_cg( list_next(regexpp), t, end)){
      free(c);
      return 1;
    }
  }
  while( t-- > source );
free(c);
  return 0;
}



/*_________________________definition of +____________________________________________*/
static int re_match_one_or_more( list_t regexpp, char * source , char ** end,char *c ) {
  //printf("_______________________+\n");
  //   printf("regexp: %c \n",c[0]);
  char *t = source;

  //\t
  if(c[1]=='\t' && c[0]==' '){


    do{  source++;
          //printf("c bon2 _______________________%s,%c\n",source,*c);
          if(source[0]!='\t' ||source[0]!=' '){
            //printf("marhaba\n");
            free(c);
            return 0;
          }

    }while(is_equal(c,source));
}

//\n
if(c[0]=='\n'){
    do{

        //  printf("c bon lal n_______________________%s,%c\n",source,*c);
          if(source[0]!='\n'){
            //printf("marhaba\n");
            free(c);
            return 0;
          }
          source++;

    }while(is_equal(c,source));
    *end=source;
    free(c);
    return 1;
      }

  if(!is_equal(c,t))
  { free(c);
    return 0;
  }

  while(is_equal(c,t) && t!='\0'){
    t++;
  }
  //recursivity

  do {

     if(re_match_cg( list_next(regexpp), t, end)){
      // printf("return\n");
      free(c);
       return 1;
     }
    }
  while( t-- > (source+1) );
  free(c);
  return 0;

}


/*__________________________definition of ?_______________________________________________*/
static int re_match_zero_or_one( list_t regexpp,char * source , char ** end ,char *c) {

 //printf("_______________________?\n");
char *t=source;

if(is_equal(c,t) )//if i find the character, all I need to do is jump to the next character
{
t++;
}
regexpp=list_next(regexpp);
free(c);
return re_match_cg( regexpp, t, end );//a?b is always true this is why I always return rematch and checks the next character
}



/*_________________________________definition of ^_______________________________________*/
static int re_match_negation( list_t regexpp, char * source , char ** end,char *c ) {

//printf("__________^ %s %s\n",source,c);
 char *s = source;
//printf("source: %s , char: %s\n",source,c);
while('\0' != *s  && s!=c ){
if(is_equal(c,s)){
   //printf("fetet bl if__________________\n");
  free(c);
  return 0;
}
s++;
}

  if(list_next(regexpp)!=NULL)
  {
    regexpp=list_next(regexpp);
    free(c);
    return re_match_cg( regexpp, source+1, end);
  }
  *end=source;

free(c);
return 1;


}



/*________________________main fonction_____________________________________*/
int re_match_cg( list_t regexpp, char *source, char **end){

  //printf("started regexp\n");


 //initialisation of my chargroup
  char_group *cg = list_first( regexpp );
  // printf("finished cg\n");

  /*call ascii fonction that finds corresponding character from int[] table*/
  char *c = asci(cg->group);
  //printf("charcter: %s lala\n",c);


  /*   stopping condition   */
  if ( ( NULL == list_next(regexpp) || strcmp(c,"")==0)&& (is_equal(c,source) && cg->op!=OP_ZERO)){

      //in case of any character
      if(c[0]=='~'){

        source="";
        *end=source;
        free(c);
        return 1;
      }

    /*  case for \n  */
    if(c[0]=='\n'){
        do{
              //source++;
              //printf("c bon lal nbl match_______________________%s,%c\n",source,*c);
              if(source[0]!='\n'){
                free(c);
                return 0;
              }
              source++;
        }while(is_equal(c,source));
        *end=source;
        free(c);
        return 1;

    }

    /*  case for \t  */
    if(c[1]=='\t' && c[0]==' '){
      do{
            source++;
            //printf("c bon1 _______________________%s,%c\n",source,*c);
            if(source[0]!='\t'|| source[0]!=' '){
              //printf("marhaba\n");
              free(c);
              return 0;
            }

      }while(is_equal(c,source));
      *end=source;
      free(c);
      return 1;
    }

    /*  case of #  */
    if(c[0]=='#'){
      //printf("source: %s, source[0]: %c\n",source,source[0]);
    do{
      source++;
        //printf("c bon #_______________________%s,%c\n",source,*c);
      //printf("source: %s, source[0]: %c\n",source,source[0]);

    }while(source[0]!='\n' && source[0]!='\0');

      //source=source+1;//skip the '\n' charcters and jump to the next ones

      //source=source+2;
        *end=source;
        free(c);
        return 1;
      }
    //this is for this case a+ aaaaabb -> next=bb
    if(cg->op==OP_ZERO_OR_MORE || cg->op==OP_ONE_OR_MORE  ){

      do{
        source++;
        //printf("c bon _______________________%s,%c\n",source,*c);
      }while(is_equal(c,source));
      *end=source;
      free(c);
      return 1;
    }
    /*else*/

    //printf("stopping condition, %s\n", source);
        source++;
        *end = source;
        free(c);
        return 1;
    }



/*in case of null cases*/
  if ( (NULL == source || strcmp(source,"")==0) && cg->op!=OP_ZERO) {
    if ( NULL == list_next(regexpp) && (c=='\0' || cg->op==OP_ZERO_OR_MORE || cg->op==OP_ONE_OR_MORE)  ) {

      *end=source;
      free(c);
      return 1;
    }
    //return 0;
  }



  /*__________testing in which character (+,*,?,^,one) I am_______________*/
  /*___testing for '*'____ */
  if (cg->op==OP_ZERO_OR_MORE) {
    // printf("ana bl zero or more \n");
    return re_match_zero_or_more( regexpp, source, end,c) ;
  }


   /*_____testing for '+'______*/
  if(cg->op==OP_ONE_OR_MORE  )
  {
    if(strcmp(source,"")==0){
      //printf("_____________bla\n");
      *end=source;
      free(c);
      return 1;
    }
    // printf("source%s\n",source);
    // printf("fetna bl condition\n");
    return re_match_one_or_more(regexpp, source, end, c) ;
  }

  /*______testing for '?'_______*/
 if(cg->op==OP_ZERO_OR_ONE )
  {
    return re_match_zero_or_one(regexpp, source, end,c) ;
  }


  /*_____testing for '^'_________*/
  if(cg->op==OP_ZERO)
  {
    //  printf("negation\n");
    return re_match_negation( regexpp, source, end,c) ;
  }


  /*_______testing for one character________*/
  if(cg->op==OP_ONE)
  {
     //printf("op_one, %s\n",source);
    if(!is_equal(c,source)){
      free(c);
      return 0;
    }

    /* case of # */
    if(c[0]=='#'){
    //  printf("source: %s, source[0]: %c\n",source,source[0]);
    do{
          source++;
          //  printf("c bon #_______________________%s,%c\n",source,*c);
          //printf("source: %s, source[0]: %c\n",source,source[0]);
    }while((source[0]!='\n') && source[0]!='\0');
    source--;

    // to keep pointer where its supposed to be, because after this we will move it up. It will cause problems
    }
  //  printf("source: %s\n",source);

  regexpp=list_next(regexpp);
  free(c);
    return re_match_cg(regexpp, source+1, end );
  }


  /*_______recursivity__________*/
  if ( '\0' != *source && is_equal(c,source)  ) {
    //printf("-------------------next\n");
    return re_match_cg(list_next(regexpp), source+1, end );
  }
  free(c);
  return 0;
}
