/**
 * @file test-queue.c
 * @author Laura
 * @date Wed Sep  21 17:58:47 2021
 * @brief Driver for list of lexems.
 *
 * Tests unitaires pour les "fonctions de lexem"
 */
#include <../include/pyas/all.h>


static void queue_basics( void ) {
  test_suite( "Basic test of queue module, (queue_new, queue_empty, enqueue, queue_to_list, queue_peek, dequeue, queue_length");


  queue_t unefile=queue_new();

  test_assert( queue_empty(unefile) == 1,
         "An empty queue is noticed by queue_empty\n" );

  test_assert( queue_length(unefile) == 0,
	       "An empty queue has zero-length\n" );

   // test de enfiler 1 élément
    unefile=enqueue(unefile, lexem_new( "int", "42", 1, 8 ) );

    test_oracle( queue_print(unefile, lexem_print), "(\n [1:8:int] 42)\n",
          "Enfile one element\n" );


  // test de enfiler 2 éléments
   unefile=enqueue(unefile, lexem_new( "int", "43", 1, 9 ) );
   test_oracle( queue_print(unefile, lexem_print), "(\n [1:8:int] 42[1:9:int] 43)\n",
         "Enfile two elements\n" );

   // test de enfiler 3 éléments
    unefile=enqueue(unefile, lexem_new( "int", "44", 1, 10 ) );
    test_oracle( queue_print(unefile, lexem_print), "(\n [1:8:int] 42[1:9:int] 43[1:10:int] 44)\n",
          "Enfile three elements\n" );

    // test de queu_peek 1 content
    lexem_t lex;
    lex=queue_peek(unefile);
    test_oracle( lexem_print(lex), "[1:10:int] 44",
           "Queue_peek works with one element\n" );

    test_assert( queue_length(unefile) == 3,
  	       "Queue_lenght with 3 elements, is 3\n" );

//SI ON FAIT CE TEST LA ON PEUT PLUS EN FAIRE D'AUTRE APRÈS
    // // test de queue_to list_t
    // list_t l;
    // l=queue_to_list(unefile);
    // test_oracle( list_print(l, lexem_print), "( [1:8:int] 42 [1:9:int] 43 [1:10:int] 44 )",
    //       "Test queue_to_list\n");


     // test de défiler 1 élément
     unefile=dequeue(unefile);

     test_oracle( queue_print(unefile, lexem_print), "(\n [1:9:int] 43[1:10:int] 44)\n",
           "Defile one element\n");

     // test de défiler 2 éléments
     unefile=dequeue(unefile);

     test_oracle( queue_print(unefile, lexem_print), "(\n [1:10:int] 44)\n",
           "Defile two elements\n");

     queue_delete( unefile, lexem_delete);

}


int main ( int argc, char *argv[] ) {

  unit_test( argc, argv );

  queue_basics();
  exit( EXIT_SUCCESS );
}
