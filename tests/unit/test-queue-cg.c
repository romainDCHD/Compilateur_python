

#include "../include/pyas/all.h"


 int main (void) {


    queue_t queue = queue_new();
    char_group *cg = new_char_group();
    char_group *cg2 = new_char_group();
    printf("queue vide:\n");
    queue_print (queue, char_group_print );
    printf("chargroup vide:\n");
    char_group_print (cg);
    cg->group[51] = 1;
    cg->op = OP_ZERO;
    printf("--------------------------------------\n");
    printf("chargroup non vide:\n");
    char_group_print (cg);
    queue = enqueue(queue, cg );
    printf("queue non vide\n");
    queue_print (queue, char_group_print );
    printf("--------------------------------------\n");

    cg->group[91] = 1;
    cg->group[71] = 1;
    cg->op = OP_ZERO_OR_ONE;
    printf("chargroup non vide:\n");
    char_group_print (cg);
    printf("--------------------------------------\n");
    queue = enqueue( queue, cg );
    printf("queue non vide\n");
    queue_print (queue, char_group_print );
    printf("--------------------------------------avec cg2:\n");


    cg2->group[81] = 1;
    cg2->op = OP_ONE_OR_MORE;
    printf("chargroup 2 non vide:\n");
    char_group_print (cg2);
    printf("--------------------------------------\n");

    queue = enqueue(queue, cg2 );
    printf("queue non vide\n");
    queue_print (queue, char_group_print );

    cg = new_char_group();
    cg->group[58] = 1;
    cg->group[59] = 1;
    cg->op = OP_ZERO_OR_ONE;
    char_group_print (cg);
    queue = enqueue(queue, cg );
    printf("queue non vide\n");
    queue_print (queue, char_group_print );
    printf("--------------------------------------\n");
    free(cg);

    exit( EXIT_SUCCESS );
 }
