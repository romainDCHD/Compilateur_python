
/**
 * @file queue.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 19:02:34 2021
 * @brief Queue.
 *
 * Queue.
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#ifdef __cplusplus  //what is it??
extern "C" {
#endif

#include <pyas/list.h>

  typedef struct link_t *queue_t;

  queue_t queue_new( void );
  int     queue_empty( queue_t q );
  queue_t enqueue( queue_t q, void* object );
  list_t  queue_to_list( queue_t q );
  void* queue_peek(queue_t f);
  queue_t dequeue(queue_t q);
  int queue_print(queue_t q, action_t print );
  int     char_print( void * c );
  int queue_length(queue_t q);
  int    queue_visit( queue_t l, action_t action );
  queue_t queue_next( queue_t q );
void   queue_delete( queue_t l, action_t delete);




#ifdef __cplusplus
}
#endif

#endif /* _QUEUE_H_ */
