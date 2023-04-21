
/**
 * @file list.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 18:07:23 2021
 * @brief define funtions to manipulate lists
 *
 */

#include <assert.h>
#include <../include/pyas/all.h>


struct link_t {
  void *content;
  struct link_t *next;
};

list_t list_new( void ) {
  return NULL;
}

int    list_empty( list_t l ) {
  return list_new() == l;
}

void*  list_first( list_t l ) {

  assert( !list_empty( l ) );
  return l->content;
}

list_t list_next( list_t l ) {

  assert( !list_empty( l ) );

  return l->next;
}

list_t list_add_first( list_t l, void* object ) {
  struct link_t *new = malloc( sizeof( *new ) );

  assert( new );

  new->content = object;
  new->next    = l;

  return new;
}

list_t list_add_last(list_t l, void* object )
{
  list_t new=l;
  if (list_empty(l))
  {
    return list_add_first(l, object);
  }

  while(!list_empty(l->next))
  {
    l=l->next;
  }
  l->next=list_add_first(l->next, object);
  return new;
}


list_t list_del_first( list_t l, action_t delete ) {
  list_t next;

  assert( !list_empty( l ) );

  next = l->next;

  if ( delete ) delete( l->content );

  free( l );

  return next;
}

size_t list_length( list_t l ) {
  size_t len = 0;

  for ( ; !list_empty( l ) ; l = list_next( l ), len++ );

  return len;
}

int    list_print( list_t l, action_t print ) {
  int ret = printf( "(%s", list_empty( l ) ? "" : " " );

  for ( ; !list_empty( l ) ; l = list_next( l ) ) {
    ret += print( list_first( l ) );
    ret += printf( " " );
  }

  ret += printf( ")" );

  return ret;
}

int list_print_first(list_t l, action_t print)
{
  int ret=print( list_first( l ) );
  return ret;
}

void   list_delete( list_t l, action_t  delete ) {

  for ( ; !list_empty( l ) ; l = list_del_first( l, delete ) );
}

//Fonction pour tester le livrable 3
int list_compare_lexem(list_t l1, list_t l2)
{
lexem_t lex1 = lexem_peek( &l1 );
lexem_t lex2 = lexem_peek( &l2 );
  while (!list_empty(l1))
  {

    if (lexem_compare(lex1, lex2)==-1)
    {
      return -1;
    }

    l1=list_next(l1);
    l2=list_next(l2);

    lex1 = lexem_peek( &l1 );
    lex2 = lexem_peek( &l2 );
  }
  return 0;
}
