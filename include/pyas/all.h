
/**
 * @file all.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 19:08:12 2021
 * @brief General include.
 *
 * General include.
 */

#ifndef _ALL_H_
#define _ALL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h> //not necessary, included by inttypes.h
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unitest/unitest.h>
#include <pyas/macros.h>
#include <pyas/list.h>
#include <pyas/queue.h>
#include <pyas/char_group.h>
#include <pyas/regexp.h>
#include <pyas/regexp_cg.h>
#include <pyas/lexem.h>
#include <pyas/database.h>
#include <pyas/lexer.h>
#include <pyas/grammar.h>
#include <pyas/re_parse.h>
#include <pyas/re_parse_livrable_1.h>
#include <pyas/objets.h>
#include <pyas/write_bitecode.h>
#include <pyas/production_bytecode.h>
//lack callbacks

#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
