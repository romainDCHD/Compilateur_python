


#ifndef _PARSE_H_
#define _PARSE_H_

#ifdef __cplusplus
extern "C" {
#endif

queue_t re_read(char *data_in);
void read_crochet(char *data_in, char_group *chargroup );
queue_t fillchargroup (queue_t queue,char_group *chargroup);

#ifdef __cplusplus
}
#endif

#endif /* _PARSE_H_ */
