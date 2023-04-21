// /**
//  * @file write_bitecode.h
//  * @author Rascol Laura
//  * @date Fri Oct  21
//  * @brief General include for production of bytecode and lnotab
//  *
//  */
//
#ifndef _PRODUCTION_BYTECODE_H_
#define _PRODUCTION_BYTECODE_H_


#ifdef __cplusplus
extern "C" {
#endif


struct label_address {
  char * name;
  int address_first;
  int address_end;
};

typedef struct label_address* label_address_t;

label_address_t label_address_new (char* name, int address, int address2);
int label_address_delete ( void* label1 );
int label_address_print ( void* label1 );

unsigned char opcode_is(lexem_t lex);
unsigned char * opcode_is_char(lexem_t lex);
int argument_yes_or_no(lexem_t lex);
pyobj_t pyobj_new_string(int len);
int length_calculated_for_bytelist(list_t l);
int lenght_lnotab(list_t lexem);
pyobj_t pyobj_from_bytecode_list(list_t l);
pyobj_t pyobj_from_lnotab_tab(char* lnotab, int taille);
void find_the_part_instruction(list_t* lexem);
int pyasm( pyobj_t code, list_t lexem);

#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
