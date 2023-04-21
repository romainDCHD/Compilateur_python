/*
author: Laura
tested and compiling correctly
*/
#include <pyas/all.h>


int main () {

  list_t l = list_new();
  pyobj_t code=pyobj_new();
  code->py.codeblock=codeblock_new();

  l=list_add_last(l, lexem_new( "dir::line", ".line", 25, 0 ));
  l=list_add_last(l, lexem_new( "skip::blank", "10", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "1", 0, 0 ));
  l=list_add_last(l, lexem_new( "newline", "", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::1::0x70", "JUMP_IF_TRUE_OR_POP", 0, 0 ));
  l=list_add_last(l, lexem_new( "newline", "", 0, 0 ));
  l=list_add_last(l, lexem_new( "symbol", "label_0", 0, 0 ));

  l=list_add_last(l, lexem_new( "dir::line", ".line", 25, 0 ));
  l=list_add_last(l, lexem_new( "skip::blank", "10", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "3", 0, 0 ));
  l=list_add_last(l, lexem_new( "newline", "", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "2", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::0::0x01", "POP_TOP", 0, 0 ));
  l=list_add_last(l, lexem_new( "newline", "", 0, 0 ));

  l=list_add_last(l, lexem_new( "dir::line", ".line", 25, 0 ));
  l=list_add_last(l, lexem_new( "skip::blank", "10", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "6", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::1::0x70", "JUMP_IF_TRUE_OR_POP", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "1", 0, 0 ));
l=list_add_last(l, lexem_new( "insn::1::0x70", "JUMP_IF_TRUE_OR_POP", 0, 0 ));
  l=list_add_last(l, lexem_new( "symbol", "label_1", 0, 0 ));

  l=list_add_last(l, lexem_new( "dir::line", ".line", 25, 0 ));
  l=list_add_last(l, lexem_new( "skip::blank", "10", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "1", 0, 0 ));
  l=list_add_last(l, lexem_new( "newline", "", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "2", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::0::0x01", "POP_TOP", 0, 0 ));

  l=list_add_last(l, lexem_new( "symbol", "label_0", 26, 30 ));
  l=list_add_last(l, lexem_new( "skip::blank", "10", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "2", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::0::0x01", "POP_TOP", 0, 0 ));

  l=list_add_last(l, lexem_new( "symbol", "label_1", 26, 30 ));
  l=list_add_last(l, lexem_new( "insn::1::0x66", "BUILD_TUPLE", 0, 0 ));
  l=list_add_last(l, lexem_new( "integer::dec", "1", 0, 0 ));
  l=list_add_last(l, lexem_new( "insn::0::0x01", "POP_TOP", 15555, 0 ));

  list_t save=l;

  pyasm(code, l);
  //Impression des pyobjs intéressant liés à pyasm soit lnotab et bytecode
  print_pyobj(code->py.codeblock->binary.content.bytecode);
  print_pyobj(code->py.codeblock->binary.trailer.lnotab);

  //Libération mémoire
  list_delete(save, lexem_delete);
  pyobj_delete(code->py.codeblock->binary.trailer.lnotab);
  pyobj_delete(code->py.codeblock->binary.content.bytecode);

  codeblock_delete(code->py.codeblock);
  free(code);




  exit( EXIT_SUCCESS );
}
