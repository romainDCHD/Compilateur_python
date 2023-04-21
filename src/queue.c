/**
 * @file queue.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr> and RASCOL LAURA
 * @date Fri Jul  2 19:02:17 2021
 * @brief define functions to manipulate queues
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> /* NULL */
#include <pyas/queue.h>
#include <pyas/all.h>


struct link_t {
  void* content;
  struct link_t* next;
};


/*
 *
 *      Fonction which create an empty queue
 *
 * @return                     a queue
 */
queue_t queue_new( void ) {
  return NULL;
}


/*
 *
 *      Fonction which test if the queue is empty
 *
 * @param q                    queue de type queue_t
 * @return                     1 if it's empty
 * @return                     0 sinon
 */
int     queue_empty( queue_t q ) {
  return queue_new() == q;
}


/*
 *
 *      Fonction which create a new queue from an old one + one element
 *
 * @param q                    queue de type queue_t
 * @param object               address of the value we want to add
 * @return                     1 if it's empty
 * @return                     queue de type queue_t
 */
queue_t enqueue( queue_t q, void* object ) {
  // TODO : ajoute le client a la queue de la file
  queue_t new=calloc(1, sizeof(*new));
  assert(new);
  //on attribue la valeur e a cette nouvelle liste
  new->content=object;
  //on se debrouille pour traiter le cas de la liste vide
  //donc le pointeur pointe sur lui même

  if (queue_empty(q))
  {
    new->next=new;
  }
  // se debrouiller pour que le nouvel elment pointe sur le plus a gauche
else{
  new->next=q->next;
   //ajouter a la fin
   q->next=new;
}
  return new;
}


/*
 *
 *      Fonction which return the element on top of the queue withou supress it
 *
 * @param q                    queue de type queue_t
 * @return                     the content on top of the queue
 */
void* queue_peek(queue_t f)
{
  assert(!queue_empty(f));
  void* el=(f)->content;
  return el;
}


/*
 *
 *      Fonction which return the first content ans supress it from the queue
 *
 * @param q                    queue de type queue_t
 * @return                     the last content
 */
queue_t dequeue(queue_t q)
{
  //retourne le client en tete de file ET le supprime de la file.
  //traiter le cas de liste vide
  assert(!queue_empty(q));
  //le cas ou 1 seul element
  if ((q)->next==q)
  {
    free(q);
    //on le libere
    q=queue_new();
    //on renvoit une file vide
  }
  else
  {
    //on cree une nouvelle file qui prend l element le plus a gauche
    queue_t q_bis=q->next;
    //le pointeur pointe sur le deuxieme element en partant de la gauche
    q->next=q_bis->next;
    //On libere le premier element
    free(q_bis);
  }
  return q;
}


void   queue_delete( queue_t l, action_t delete) {
  list_t list = queue_to_list ( l );
  list_delete (list, delete);
}


/*
 *
 *      Fonction which print chaine_de_caractere
 *
 * @param c                    pointeur sur chaine de caractère
 * @return                     int
 */
int     char_print( void * c )
{
  char* caractere=c;
  return printf("%s ", caractere);
}


/*
 *
 *      Fonction which print the whole queue
 *
 * @param q                    queue de type queue_t
 * @param print               type action_t c'est à dire une fonction d'impression
 * @return                     nothing
 */
int    queue_print( queue_t l, action_t print ) {
  int ret = printf( "(\n%s", queue_empty( l ) ? "" : " " );

  ret += queue_visit( l, print );
  ret += printf( ")\n" );
  return ret;
}


/*
 *
 *      Fonction which run in the queue and to a action at the time
 *
 * @param l                    queue de type queue_t
 * @param action               type action_t c'est à dire une fonction d'impression
 * @return                     int 0 if empty, else 1
 */
int    queue_visit( queue_t l, action_t action ) {
  int ret = 0;

  queue_t q;

  if ( queue_empty( l ) ) {
    return 0;
  }
  q = queue_next( l );

  do {
    ret += action( queue_peek( q  ) );
    // ret += queue_visit( l, print );
    q = queue_next( q );
  } while ( q != queue_next( l ) );

  return ret;
}


/*
 *
 *      Fonction which return the element on top of the queue withou supress it
 *
 * @param q                    queue de type queue_t
 * @return                     the content next
 */
queue_t queue_next( queue_t q ) {

  assert( !queue_empty( q ) );

  return q->next;
}


/*
 *
 *      Fonction which permits to put 1
 * @param nothing              type void *
 * @return                     1
 */
static int count( __attribute__((unused)) void *thing ) {
  return 1;
}


/*
 *
 *      Fonction which return the lenght of the queue
 *
 * @param q                    queue de type queue_t
 * @return                     tint of the lenght
 */
int queue_length(queue_t q)
{
  return queue_visit( q, count );
}


/*
 *
 *      Fonction which return a list made from a queue
 *
 * @param q                    queue de type queue_t
 * @return                     the list formed with the queue
 */
list_t  queue_to_list(queue_t q )
{
  list_t l=q->next;
  q->next=NULL;
  return l;
}
