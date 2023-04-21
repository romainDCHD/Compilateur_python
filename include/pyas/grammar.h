/**
 * @file grammar.h
 * @author Rascol Laura
 * @date Mon Oct  11
 * @brief grammar.
 *
 * grammar.
 */

#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#ifdef __cplusplus
extern "C" {
#endif

// <pys> : := <eol>* <prologue> <code>
int parse_pys ( list_t * lexems );

//<prologue> : := <set-directives> <interned-strings> <constants> <names> [<varnames> <freevars> <cellvars>] teste
int parse_prologue ( list_t * lexems );

//<set-version-pyvm> : := {‘dir::set’} {‘integer::dec’} <eol> {‘blank’} {‘version_pyvm’} {‘blank’} TESTE
int parse_set_version_pyvm ( list_t * lexems );

//<set-flags> : := {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’} <eol> TESTE
int parse_set_flags ( list_t * lexems );

//<set-filename> : := {‘dir::set’} {‘blank’} {‘filename’} {‘blank’} {‘string’} <eol> TESTE
int parse_set_filename ( list_t * lexems );

//<set-name> : := {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’} <eol> TESTE
int parse_set_name ( list_t * lexems );

//〈interned-strings〉 : := {‘dir::interned’} 〈eol〉 ( {‘string’} 〈eol〉 )* TESTE
int parse_interned_strings ( list_t * lexems );

// 〈constants〉 : := {‘dir::consts’} 〈eol〉 ( 〈constant〉 〈eol〉 )* TESTE
int parse_constants ( list_t * lexems );

//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} | <tuple> teste sans tuple
int parse_constant ( list_t * lexems );

///<list> : := {‘brack::left’} ({’blank’} <constant>)* [{’blank’}] {‘brack::right’} TESTE
int parse_list ( list_t * lexems );

//<tuple> : := {‘paren::left’} ({’blank’} <constant>)* [{’blank’}] {‘paren::right’} teste
int parse_tuple ( list_t * lexems );

// 〈names〉 : := {‘dir::names’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int parse_names ( list_t * lexems );

// 〈varnames〉 : := {‘dir::varnames’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int parse_varnames ( list_t * lexems );

// 〈freevars〉 : := {‘dir::freevars’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int parse_freevars ( list_t * lexems );

// 〈cellvars〉 : := {‘dir::cellvars’} 〈eol〉 ( {‘string’} 〈eol〉 )* teste
int parse_cellvars ( list_t * lexems );

// 〈code〉 : := {‘dir::text’} 〈eol〉 ( 〈assembly-line〉 〈eol〉 )* teste
int parse_code ( list_t * lexems );

// // 〈assembly-line〉 : := 〈insn〉 | 〈source-lineno〉 | 〈label〉 teste
int parse_assembly_line ( list_t * lexems );

// // 〈label〉 : := {‘symbol’} {‘blank’} {‘colon’}  TESTE
int parse_label ( list_t * lexems );

// // 〈source-lineno〉 : := {‘dir::line’} {‘blank’} {‘integer::dec’}TESTE
int parse_source_lineno ( list_t * lexems );

// // 〈insn〉 : := {‘insn::0’} | {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} ) TESTE
int parse_insn ( list_t * lexems );

// // 〈eol〉 : := ([{‘blank’}] [{‘comment’}] {‘newline’} [{’blank’}])* TESTE
int parse_eol ( list_t * lexems );

// // 〈set-directives〉 : := 〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉] 〈set-stack-size〉 〈set-arg-count〉 [set-kwonly-arg-count] [set-posonly-arg-count] TESTE
int parse_set_directives ( list_t * lexems );

// // 〈set-source-size〉 : := {‘dir::set’} {‘blank’} {‘source_size’} {‘blank’}{‘integer::dec’} 〈eol〉   TESTE
int parse_set_source_size ( list_t * lexems );

// // 〈set-stack-size〉 : := {‘dir::set’} {‘blank’} {‘stack_size’} {‘blank’}{‘integer::dec’} 〈eol〉TESTE
int parse_set_stack_size ( list_t * lexems );

// // 〈set-arg-count〉 : := {‘dir::set’} {‘blank’} {‘arg_count’} {‘blank’}{‘integer::dec’} 〈eol〉TESTE
int parse_set_arg_count ( list_t * lexems );

// // 〈set-kwonly-arg-count〉 : := {‘dir::set’} {‘blank’} {‘kwonly_arg_count’}{‘blank’} {‘integer::dec’} 〈eol〉TESTE
int parse_set_kwonly_arg_count ( list_t * lexems );

// // 〈set-posonly-arg-count〉 : := {‘dir::set’} {‘blank’} {‘posonly_arg_count’}{‘blank’} {‘integer::dec’} 〈eol〉TESTE
int parse_set_posonly_arg_count ( list_t * lexems );

#ifdef __cplusplus
}
#endif

#endif /* _GRAMMAR_H_ */
