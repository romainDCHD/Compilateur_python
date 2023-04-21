


#ifndef _CHAR_GROUP_H_
#define _CHAR_GROUP_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OP_ONE,
    OP_ONE_OR_MORE,
    OP_ZERO_OR_MORE,
    OP_ZERO_OR_ONE,
    OP_ZERO,
} operator_t;

typedef struct {
  int group [256];
  operator_t op;
} char_group;


int char_group_print( void *cgx );
char_group *new_char_group();
int delete_char_group ( void *cg );
void char_group_initialize( char_group *chargroup);

#ifdef __cplusplus
}
#endif

#endif /* _CHAR_GROUP_H_ */
