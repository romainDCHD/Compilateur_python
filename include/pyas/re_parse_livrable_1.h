#ifndef _PARSE_2_H_
#define _PARSE_2_H_

#ifdef __cplusplus
extern "C" {
#endif

int re_read_2(char *data_in, queue_t* queue);
int read_crochet_2(char *data_in, char_group *chargroup );
queue_t fillchargroup_2 (queue_t queue,char_group *chargroup);

#ifdef __cplusplus
}
#endif

#endif /* _PARSE_H_ */
