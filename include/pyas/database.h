#ifndef _TREATASS_H_
#define _TREATASS_H_

#ifdef __cplusplus
extern "C" {
#endif

struct dat_t {
  char *type;
  char *def;
};

typedef struct dat_t *data_t;


data_t data_new( char *type, char *def);
int data_delete( void* data);
int print_data_t( void * dat);
queue_t read_database(char* nom_fichier_ass);



#ifdef __cplusplus
}
#endif

#endif /* _TREATASS_H_ */
