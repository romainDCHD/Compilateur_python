// @brief define the "mathematical" symbol and make the function who permite to know if the enter is a valid lexem



#include <stdio.h>
#include <../include/pyas/all.h>
//#include <../include/pyas/regexp.h>


//creation des chaine de characters
/*
.......
*/



//definition of *
static int re_match_zero_or_more( char c, char *regexp, char * source , char ** end ) {


  char *t = source;
  while ( '\0' != *t && ( *t == c || '.' == c ) ) {
    t++;
  }
  do {
    if ( re_match( regexp, t, end) ) {
      return 1;
    }
  }
  while( t-- > source );

  return 0;
}

//definition of +
static int re_match_one_or_more( char c, char *regexp, char * source , char ** end ) {


  char *t = source;

  if(t[0]==c )//make sure I have the character at least once
    { while ( '\0' != *t &&  ( *t == c || '.' == c ) ) {
      t++;
    }
  }
else{
  return 0;
}
  do {
    if ( re_match( regexp, t, end) ) {
      return 1;
    }
  }
  while( t-- > source );

  return 0;
}

//definition of ?
static int re_match_zero_or_one( char c, char *regexp, char * source , char ** end ) {

  char *t = source;

  if(t[0]==c  )//if i find the character, all I need to do is jump to the next character
  {
  t++;
  }
 return re_match( regexp, t, end );//a?b is always true this is why I always return rematch and checks the next character
}

//definition of ^
static int re_match_negation( char c, char *regexp, char * source , char ** end ) {


char *s = source;
while('\0' != *s   ){
if(*s==c){
  return 0;
}
s++;
}

  do {
    if ( re_match( regexp, s, end) ) {
      return 1;
    }
  }
  while( s-- > source );

  return 0;
}

//////////////////////////////////////////////////////////
//test if it is matching with our data-base but end is lacling and it is not completed with all the possible case
/////////////////////////////////////////////////////////

//creation of fonction that checks [a-e] abcde ->return 0 or 1
//this fonction calls parse

int re_match( char *regexp, char *source, char **end) {





  //handling in case of blank regexp
  if ( NULL == regexp || '\0' == regexp[ 0 ] ) {
    if ( end ) {
      *end = source;
    }
    return 1;
  }

//traiter les cas null et ""

  if ( NULL == source || strcmp(source,"")==0) {
    if ( regexp && regexp[ 0 ] && '*' == regexp[ 1 ] ) {
      return 1;
    }
    return 0;
  }

  //testing in which character (+,*,?,^) I am
  //testing for '*'

  if (regexp[ 1 ]=='*' ) {
    return re_match_zero_or_more( regexp[ 0 ], regexp+2, source, end) ;
  }
  //testing for '+'
  if(regexp[1]=='+'  )
  {
    return re_match_one_or_more( regexp[ 0 ], regexp+2, source, end) ;
  }

  //testing for '?'
  if(regexp[1]=='?' )
  {
    return re_match_zero_or_one(regexp[ 0 ] , regexp+2, source, end) ;
  }

  //testing for '^'

  if(regexp[1]=='^')
  {
    printf( "character I do not wish to see %c \n", regexp[2]);
    return re_match_negation( regexp[2], regexp+2, source+1, end) ;
  }


  //recursivity

  if ( '\0' != *source && ('.' == regexp[ 0 ] || *source ==regexp[ 0 ]  )) {

    return re_match( regexp+1, source+1, end );
  }

  return 0;

}
