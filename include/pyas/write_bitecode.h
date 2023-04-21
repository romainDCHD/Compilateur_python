// /**
//  * @file write_bitecode.h
//  * @author Melissa AKIKI
//  * @date Wed Oct  19
//  * @brief General include for serialisation
//  *
//  * General include for serialisation, as in the project's pdf document
//  */
//
#ifndef _SERIALISATION_H_
#define _SERIALISATION_H_


#ifdef __cplusplus
extern "C" {
#endif

void parsing_type(FILE *fp, pyobj_t obj);
int pyobj_write( FILE *fp, pyobj_t obj);

#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
