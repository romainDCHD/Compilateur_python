#ifndef _OBJETS_H_
#define _OBJETS_H_

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------
typedef char pyobj_type;

#define PYOBJ_NULL '0'
#define PYOBJ_NONE 'N'
#define PYOBJ_FALSE 'F'
#define PYOBJ_TRUE 'T'
#define PYOBJ_INT 'i'
#define PYOBJ_INT64 'I'
#define PYOBJ_FLOAT 'f'
#define PYOBJ_BINARY_FLOAT 'g'
#define PYOBJ_COMPLEX 'x'
#define PYOBJ_BINARY_COMPLEX 'y'
#define PYOBJ_STRING 's'
#define PYOBJ_REF 'r'
#define PYOBJ_STRINGREF 'R'
#define PYOBJ_TUPLE '('
#define PYOBJ_SMALL_TUPLE ')'
#define PYOBJ_LIST '['
#define PYOBJ_DICT '{'
#define PYOBJ_SET '<'
#define PYOBJ_ASCII 'a'
#define PYOBJ_ASCII_INTERNED 'A'
#define PYOBJ_SHORT_ASCII 'z'
#define PYOBJ_SHORT_ASCII_INTERNED 'Z'
#define PYOBJ_CODE 'c'
#define PYOBJ_BITECODE_LNOTAB 'b'
#define PYOBJ_STOP_ITER 'S'
#define PYOBJ_ELLIPSIS '.'
#define PYOBJ_LONG 'l'
#define PYOBJ_UNICODE 'u'
#define PYOBJ_INTERNED 't'
#define PYOBJ_UNKNOWN '?'
#define PYOBJ_FROZENSET '>'

//-------------------------------------------------

struct py_codeblock;

struct pyobj_t ;
typedef struct pyobj * pyobj_t ;


typedef struct {
  int version_pyvm ;
  union {
    struct {
      uint32_t arg_count ;
      uint32_t local_count ;
      uint32_t stack_size ;
      uint32_t flags ;
    } _0 ; /* Up to 3.7 (2.7 , etc .) */
    struct {
      uint32_t arg_count ;
      uint32_t posonly_arg_count ;
      uint32_t kwonly_arg_count ;
      uint32_t local_count ;
      uint32_t stack_size ;
      uint32_t flags ;
    } _1 ; /* From 3.8 onwards */
  } header ;


  pyobj_t parent ;
  struct {
    union {
      struct {
        uint32_t magic ;
        time_t timestamp ;
      } _0 ;
      struct {
        uint32_t magic ;
        time_t timestamp ;
        uint32_t source_size ;
      } _1 ;
      struct {
        uint32_t magic ;
        uint32_t bitfield ;
        time_t timestamp ;
        uint32_t source_size ;
        uint64_t hash ;
      } _2 ;
    } header ;
    struct {
      pyobj_t interned ;
      pyobj_t bytecode ;
      pyobj_t consts ;
      pyobj_t names ;
      pyobj_t varnames ;
      pyobj_t freevars ;
      pyobj_t cellvars ;
    } content ;
    struct {
      pyobj_t filename ;
      pyobj_t name ;
      uint32_t firstlineno ;
      pyobj_t lnotab ;
    } trailer ;
  } binary ;
} py_codeblock ;

//-------------------------------------------------

struct pyobj {
  pyobj_type type;
  unsigned int refcount;

  union {
    struct {
      pyobj_t *value;
      int32_t size;
    }list;

    struct {
      char *buffer;
      int length;
    }string;

    py_codeblock *codeblock;

    union {
      int32_t integer;
      int64_t integer64;
      double real;
      struct {
        double real;
        double imag;
      }complex;
    }number;
  }py;
};

//-------------------------------------------------
pyobj_t pyobj_new();
void pyobj_delete( pyobj_t pyobj);
py_codeblock* codeblock_new();
void codeblock_delete( py_codeblock* codeblock);
void print_codeblock ( py_codeblock* codeblock );
void print_pyobj ( pyobj_t pyobj );

void string_print (void* string);
int fill_pyobj_list (pyobj_t pyobj_list, list_t* list, list_t* type );
int char_delete (void* char_);
int char_print_2 (void* test);
int fill_timestamp ( py_codeblock* codeblock );
char* str_sans_guillemets (char* string);

// int fill_eol ( list_t * lexems );
// int fill_interned_strings ( list_t * lexems, py_codeblock* codeblock );
// int fill_names ( list_t * lexems, py_codeblock* codeblock );
// int fill_varnames ( list_t * lexems, py_codeblock* codeblock );
// int fill_freevars ( list_t * lexems, py_codeblock* codeblock );
// int fill_cellvars ( list_t * lexems, py_codeblock* codeblock );

// <pys> : := <eol>* <prologue> <code>
int fill_pys ( list_t * lexems, py_codeblock* codeblock );

//<prologue> : := <set-directives> <interned-strings> <constants> <names> [<varnames> <freevars> <cellvars>] teste
int fill_prologue ( list_t * lexems, py_codeblock* codeblock );

//<set-version-pyvm> : := {‘dir::set’} {‘integer::dec’} <eol> {‘blank’} {‘version_pyvm’} {‘blank’} TESTE
int fill_set_version_pyvm ( list_t * lexems, py_codeblock* codeblock );

//<set-flags> : := {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’} <eol> TESTE
int fill_set_flags ( list_t * lexems, py_codeblock* codeblock );

//<set-filename> : := {‘dir::set’} {‘blank’} {‘filename’} {‘blank’} {‘string’} <eol> TESTE
int fill_set_filename ( list_t * lexems, py_codeblock* codeblock );

//<set-name> : := {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’} <eol> TESTE
int fill_set_name ( list_t * lexems, py_codeblock* codeblock );

//〈interned-strings〉 : := {‘dir::interned’} 〈eol〉 ( {‘string’} 〈eol〉 )* TESTE
int fill_interned_strings ( list_t * lexems, py_codeblock* codeblock );

// 〈constants〉 : := {‘dir::consts’} 〈eol〉 ( 〈constant〉 〈eol〉 )* TESTE
int fill_constants ( list_t * lexems, py_codeblock* codeblock );

//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} | <tuple> teste sans tuple
int fill_constant ( list_t * lexems, list_t* constant_list, list_t* type );

///<list> : := {‘brack::left’} ({’blank’} <constant>)* [{’blank’}] {‘brack::right’} TESTE
int fill_list ( list_t * lexems, list_t* constant_list, list_t* type );

//<tuple> : := {‘paren::left’} ({’blank’} <constant>)* [{’blank’}] {‘paren::right’} teste
int fill_tuple ( list_t * lexems, list_t* constant_list, list_t* type );

// 〈names〉 : := {‘dir::names’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int fill_names ( list_t * lexems, py_codeblock* codeblock );

// 〈varnames〉 : := {‘dir::varnames’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int fill_varnames ( list_t * lexems, py_codeblock* codeblock );

// 〈freevars〉 : := {‘dir::freevars’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int fill_freevars ( list_t * lexems, py_codeblock* codeblock );

// 〈cellvars〉 : := {‘dir::cellvars’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int fill_cellvars ( list_t * lexems, py_codeblock* codeblock );

// 〈code〉 : := {‘dir::text’} 〈eol〉 ( 〈assembly-line〉 〈eol〉 )* teste
int fill_code ( list_t * lexems );

// // 〈assembly-line〉 : := 〈insn〉 | 〈source-lineno〉 | 〈label〉 teste
int fill_assembly_line ( list_t * lexems);

// // 〈label〉 : := {‘symbol’} {‘blank’} {‘colon’}  TESTE
int fill_label ( list_t * lexems );

// // 〈source-lineno〉 : := {‘dir::line’} {‘blank’} {‘integer::dec’}TESTE
int fill_source_lineno ( list_t * lexems);

// // 〈insn〉 : := {‘insn::0’} | {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} ) TESTE
int fill_insn ( list_t * lexems );

// // 〈eol〉 : := ([{‘blank’}] [{‘comment’}] {‘newline’} [{’blank’}])* TESTE
int fill_eol ( list_t * lexems );

// // 〈set-directives〉 : := 〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉] 〈set-stack-size〉 〈set-arg-count〉 [set-kwonly-arg-count] [set-posonly-arg-count] TESTE
int fill_set_directives ( list_t * lexems, py_codeblock* codeblock );

// // 〈set-source-size〉 : := {‘dir::set’} {‘blank’} {‘source_size’} {‘blank’}{‘integer::dec’} 〈eol〉   TESTE
int fill_set_source_size ( list_t * lexems, py_codeblock* codeblock );

// // 〈set-stack-size〉 : := {‘dir::set’} {‘blank’} {‘stack_size’} {‘blank’}{‘integer::dec’} 〈eol〉TESTE
int fill_set_stack_size ( list_t * lexems, py_codeblock* codeblock );

// // 〈set-arg-count〉 : := {‘dir::set’} {‘blank’} {‘arg_count’} {‘blank’}{‘integer::dec’} 〈eol〉TESTE
int fill_set_arg_count ( list_t * lexems, py_codeblock* codeblock );

// // 〈set-kwonly-arg-count〉 : := {‘dir::set’} {‘blank’} {‘kwonly_arg_count’}{‘blank’} {‘integer::dec’} 〈eol〉TESTE
int fill_set_kwonly_arg_count ( list_t * lexems, py_codeblock* codeblock );

// // 〈set-posonly-arg-count〉 : := {‘dir::set’} {‘blank’} {‘posonly_arg_count’}{‘blank’} {‘integer::dec’} 〈eol〉TESTE
int fill_set_posonly_arg_count ( list_t * lexems, py_codeblock* codeblock );

// <function> : := {‘dir::code_start’} {’integer’} <eol> <pys> {‘dir::code_end’}
int fill_function ( list_t * lexems, py_codeblock* codeblock );

#ifdef __cplusplus
}
#endif

#endif /* _OBJETS_H_ */
