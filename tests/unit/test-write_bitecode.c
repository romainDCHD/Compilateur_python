
// @author Melissa AKIKI
/*
*Fonction pour tester l'ecriture sur un fichier bitecode
*/

#include "../include/pyas/all.h"


 int main (int argc, char* argv[]) {


    /*

    * step 1: fill pyobj_test
    * step 2: generate bitecode from terminal which will be the true one
    * step 3: call write_bitecode and compare with original

    */
    //calling lexer Fonction
    if(argc < 3){
      printf("Too few arguments. Put: \n");
      printf("./bin/unit/test-lexer.exe  data_base.txt   nom_fichier_a_lire  \n");
      return(EXIT_FAILURE);
    }

    char* file_name;
    char* data_base;
    data_base = argv[1];
    file_name = argv[2];

    list_t list = list_new();
    list = find_regexp( data_base, file_name);
    list_t save = list;// pointer to delete list at the end

    // now livrable 2-3
    FILE *fp=NULL;
    fp=fopen("write_bitecode.pyc","w");

    if(fp==NULL){
      printf("failed to create file\n");
      exit( EXIT_FAILURE );
    }


    py_codeblock* codeblock = codeblock_new();
    pyobj_t obj=pyobj_new();


    list_t* lexems = &list;

    int i=fill_pys( lexems, codeblock );
    (obj)->py.codeblock = codeblock;

    //find_the_part_instruction(&list);
    int j=pyasm(obj,save);

      if (  i== 0 && j==0 )
      {
        //print_codeblock (codeblock);
        //(obj)->py.codeblock = codeblock;

        pyobj_write(fp,obj);
        printf("write to file ok\n");


        list_delete(save, lexem_delete);
        pyobj_delete(obj->py.codeblock->binary.trailer.lnotab);
        pyobj_delete(obj->py.codeblock->binary.content.bytecode);

        codeblock_delete(obj->py.codeblock);
        free(obj);
        //codeblock_delete(codeblock);
        exit( EXIT_SUCCESS );
      }

      else
      {
        //print_codeblock (codeblock);
        printf("Failed to fill\n");
        //codeblock_delete(codeblock);
        list_delete(save, lexem_delete);
        pyobj_delete(obj->py.codeblock->binary.trailer.lnotab);
        pyobj_delete(obj->py.codeblock->binary.content.bytecode);

        codeblock_delete(obj->py.codeblock);
        free(obj);
        exit( EXIT_FAILURE );
      }




       exit( EXIT_SUCCESS );





//    //
//    //  //FILLING THE LIST OF LEXEM
//
//    /*dir set*/
//    lexem_t lexem_dir_set = lexem_new( "dir::set", ".set", 0, 0 );
//    lexem_t lexem_dir_interned = lexem_new( " dir::interned", ".interned", 0, 1 );
//    lexem_t lexem_dir_consts = lexem_new( "dir::consts", ".consts", 0, 1 );
//    lexem_t lexem_dir_names = lexem_new( "dir::names", ".names", 0, 0 );
//
//    /* ceux qui se repetent tjrs*/
//     lexem_t lexem_skip_blank_1 = lexem_new( "skip::blank", " ", 1, 0 );
//     lexem_t lexem_skip_blank_2 = lexem_new( "skip::blank", "	 ", 1, 0 );
//     lexem_t lexem_skip_blank_3 = lexem_new( "skip::blank", "		 ", 1, 0 );
//     lexem_t lexem_comment = lexem_new( "skip::comment", "# Start pyc-objdump output", 1, 0 );
//     lexem_t lexem_newline = lexem_new( "newline", '\n', 0, 0 );
//
//   /*set*/
//    lexem_t lexem_set_version_pyvm = lexem_new( "set::version_pyvm", "version_pyvm", 0, 1 );
//    lexem_t lexem_set_flags= lexem_new( "set::flags", "flags", 0, 1 );
//    lexem_t lexem_filename = lexem_new( "set::filename", "filename", 0, 1 );
//    lexem_t lexem_set_name = lexem_new( "set::name", "name", 0, 1 );
//    lexem_t lexem_stack_size = lexem_new( "set::stack_size", "stack_size", 0, 1 );
//    lexem_t lexem_arg_count = lexem_new( "set::arg_count", "arg_count", 0, 1 );
//
//
//    /* valeurs*/
//    lexem_t lexem_integer_dec_5 = lexem_new( "integer::dec", "5", 1, 1 );
//    lexem_t lexem_integer_dec_16 = lexem_new( "integer::dec", "16", 1, 1 );
//    lexem_t lexem_integer_dec_2 = lexem_new( "integer::dec", "2", 1, 1 );
//    lexem_t lexem_integer_dec_0 = lexem_new( "integer::dec", "0", 1, 1 );
//    lexem_t lexem_integer_dec_62211 = lexem_new( "integer::dec", "62211", 1, 1 );
//    lexem_t lexem_string_a = lexem_new( "string", "a", 1, 1 );
//    lexem_t lexem_string_b = lexem_new( "string", "b", 1, 1 );
//    lexem_t lexem_string_m = lexem_new( "string", "<module>", 1, 1 );
//    lexem_t lexem_string_f = lexem_new( "string", "functions/function1.py", 1, 1 );
//    lexem_t lexem_pycst=lexem_new( "pycst", "None", 0, 1 );
//    lexem_t lexem_integer_hex = lexem_new( "integer::hex", "0x00000040", 0, 0 );
//
//
//
//
//
//   //TEST PYS
//   // //headline
//   list = list_add_last (list, lexem_newline);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_comment);
//   list = list_add_last (list, lexem_newline);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank_1);
//   list = list_add_last (list, lexem_set_version_pyvm);
//   list = list_add_last (list, lexem_skip_blank_2);
//   list = list_add_last (list, lexem_integer_dec_62211);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank_1);
//   list = list_add_last (list, lexem_set_flags);
//   list = list_add_last (list, lexem_skip_blank_3);
//   list = list_add_last (list, lexem_integer_hex);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank_1);
//   list = list_add_last (list, lexem_filename);
//   list = list_add_last (list, lexem_skip_blank_3);
//   list = list_add_last (list, lexem_string_f);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank_1);
//   list = list_add_last (list, lexem_set_name);
//   list = list_add_last (list, lexem_skip_blank_3);
//   list = list_add_last (list, lexem_string_m);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank_1);
//   list = list_add_last (list, lexem_stack_size);
//   list = list_add_last (list, lexem_skip_blank_3);
//   list = list_add_last (list, lexem_integer_dec_2);
//   list = list_add_last (list, lexem_newline);
//
//   list = list_add_last (list, lexem_dir_set);
//   list = list_add_last (list, lexem_skip_blank_1);
//   list = list_add_last (list, lexem_arg_count);
//   list = list_add_last (list, lexem_skip_blank_3);
//   list = list_add_last (list, lexem_integer_dec_0);
//   list = list_add_last (list, lexem_newline);
//
// // //.interned
//   list = list_add_last (list, lexem_newline);
//   list = list_add_last (list, lexem_dir_interned);
//   list = list_add_last (list, lexem_newline);
//   list = list_add_last (list, lexem_string_a);
//   list = list_add_last (list, lexem_newline);
//   list = list_add_last (list, lexem_string_b);
//   list = list_add_last (list, lexem_newline);
//   list = list_add_last (list, lexem_string_m);
//   list = list_add_last (list, lexem_newline);
//
//   // //.consts


 }
