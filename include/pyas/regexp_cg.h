/**
 * @file regexp.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  28 09:56:03 2022
 * @brief General include for regexp
 *
 * General include for regexp, as in the project's pdf document
 */

#ifndef _REGEXP_CG_H_
#define _REGEXP_CG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <pyas/char_group.h>

int re_match( char *regexp , char *source , char **end );//fonction initiale readapter pour lire des char_group
int re_match_cg( queue_t regexp, char *source, char **end);//fonction pour comparer des char_group avec la source
char *asci( int cg[256]);
#ifdef __cplusplus
}
#endif

#endif
