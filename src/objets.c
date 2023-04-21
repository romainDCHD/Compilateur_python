#include <../include/pyas/all.h>
#include <../include/pyas/objets.h>

//manque les free

pyobj_t pyobj_new(){
  pyobj_t pyobj = calloc( 1, sizeof( *pyobj ));
  pyobj->refcount = 0;
  pyobj->type = PYOBJ_NULL;
  return pyobj;
}

void pyobj_delete( pyobj_t pyobj){

  if (pyobj->type == PYOBJ_LIST)
  {
    int i = 0;
    for ( i = 0; i < pyobj->py.list.size; i++)
    {
      pyobj_delete( pyobj->py.list.value[i] );
    }
    free( pyobj->py.list.value);
    free( pyobj );
  }

  else if (pyobj->type == PYOBJ_STRING || pyobj->type == PYOBJ_BITECODE_LNOTAB)
  {
    free (pyobj->py.string.buffer);
    free( pyobj );
  }


  else
  {
    free(pyobj);
  }
}

//--------------------------------------------------

py_codeblock* codeblock_new(){
  py_codeblock* codeblock = calloc (1, sizeof(*codeblock) );
  codeblock->version_pyvm = 0;
  //header
  codeblock->header._1.arg_count = 0;
  codeblock->header._1.local_count = 0;
  codeblock->header._1.stack_size = 0;
  codeblock->header._1.flags = 0;
  codeblock->header._1.posonly_arg_count = 0;
  codeblock->header._1.kwonly_arg_count = 0;
  //parent
  codeblock->parent = pyobj_new();
  //binary
    //header (_1)
    codeblock->binary.header._1.magic = 0;
    fill_timestamp( codeblock );
    codeblock->binary.header._1.source_size = 0;
    //content
    codeblock->binary.content.interned  = pyobj_new();
    // codeblock->binary.content.bytecode  = pyobj_new();
    codeblock->binary.content.consts  = pyobj_new();
    codeblock->binary.content.names  = pyobj_new();
    codeblock->binary.content.varnames  = pyobj_new();
    codeblock->binary.content.freevars  = pyobj_new();
    codeblock->binary.content.cellvars  = pyobj_new();
    //trailer
    codeblock->binary.trailer.filename  = pyobj_new();
    codeblock->binary.trailer.name  = pyobj_new();
    codeblock->binary.trailer.firstlineno = 0;
    // codeblock->binary.trailer.lnotab  = pyobj_new();
    return codeblock;
}

void codeblock_delete( py_codeblock* codeblock){
  pyobj_delete(codeblock->parent);
  //binary
    //content
    pyobj_delete(codeblock->binary.content.interned);
    // pyobj_delete(codeblock->binary.content.bytecode);
    pyobj_delete(codeblock->binary.content.consts);
    pyobj_delete(codeblock->binary.content.names);
    pyobj_delete(codeblock->binary.content.varnames);
    pyobj_delete(codeblock->binary.content.freevars);
    pyobj_delete(codeblock->binary.content.cellvars);
    //trailer
    pyobj_delete(codeblock->binary.trailer.filename);
    pyobj_delete(codeblock->binary.trailer.name);
    // pyobj_delete(codeblock->binary.trailer.lnotab);
    free(codeblock);
}
//-----------------------------------------------------------

void print_pyobj ( pyobj_t pyobj ){
  printf("\nprint py_obj:\n");
  printf("\tpyobj_type: %c\n", pyobj->type);
  printf("\trefcount: %d\n", pyobj->refcount);
  switch ( pyobj->type )
  {
    case PYOBJ_LIST:
      //printf("test2 %c\n",(pyobj->py.list.value[0])->type );
      printf("\tlist-size: %d\n",pyobj->py.list.size );
      int i = 0;
      int a;
      for ( i = 0; i < pyobj->py.list.size; i++)
      {
        printf("\t\t" );
        //printf("value: %c\n",(pyobj->py.list.value[i])->type );
        print_pyobj ( pyobj->py.list.value[i] );
      }
    break;

    case PYOBJ_STRING:
      printf("\tstring-length: %d   string-buffer: %s\n",pyobj->py.string.length, pyobj->py.string.buffer );
    break;

    case PYOBJ_COMPLEX:
      printf("\tcomplex-real: %lf   complex-imag: %lf\n",pyobj->py.number.complex.real, pyobj->py.number.complex.imag );
    break;

    case PYOBJ_INT:
      printf("\tint: %" PRIi32 "\n",pyobj->py.number.integer );
    break;

    case PYOBJ_INT64:
      printf("\tint64: %" PRIi64 "\n",pyobj->py.number.integer64 );
    break;

    case PYOBJ_FLOAT:
      printf("\treal: %lf\n",pyobj->py.number.real );
    break;

    case PYOBJ_CODE:
      print_codeblock ( (pyobj->py.codeblock) );
    break;

    case PYOBJ_BITECODE_LNOTAB:
      for (a=0; a<pyobj->py.string.length; a++)
      {
       printf("\tstring-length: %d    buffer: 0x%hhx\n",pyobj->py.string.length, pyobj->py.string.buffer[a]);
      }
    break;

    case PYOBJ_NONE:
      printf("\tnone\n");
    break;


    default: printf("\tpy empty\n");
  }
}

void print_codeblock ( py_codeblock* codeblock ){
  printf("\nprint py_codeblock:\n");
  //version_pyvm
  printf("version_pyvm: %d\n", codeblock->version_pyvm);
  //header (_1)
  printf("header:\n\t arg_count: ""%" PRIu32 "\n", codeblock->header._1.arg_count);
  printf("\t local_count: ""%" PRIu32 "\n", codeblock->header._1.local_count);
  printf("\t stack_size: ""%" PRIu32 "\n", codeblock->header._1.stack_size);
  printf("\t flags: ""%" PRIu32 "\n", codeblock->header._1.flags);
  printf("\t posonly_arg_count: ""%" PRIu32 "\n", codeblock->header._1.posonly_arg_count);
  printf("\t kwonly_arg_count: ""%" PRIu32 "\n", codeblock->header._1.kwonly_arg_count);
  //parent
  printf("parent:");
  print_pyobj (codeblock->parent);
  //binary
  printf("\nbinary:\n");
    //header (_1)
    printf("\t header\n");
    printf("\t \t magic: ""%" PRIu32 "\n", codeblock->binary.header._1.magic);
    printf("\t \t timestamp: %s \n", ctime(&codeblock->binary.header._1.timestamp) );
    printf("\t \t source_size: ""%" PRIu32 "\n", codeblock->binary.header._1.source_size);
    //content
    printf("\n\t content:");
    printf("\n\t \t.interned:");
    print_pyobj( codeblock->binary.content.interned );
    printf("\n\t \t.bytecode:");
    // print_pyobj( codeblock->binary.content.bytecode );
    printf("\n\t \t.consts:");
    print_pyobj( codeblock->binary.content.consts );
    printf("\n\t \t.names:");
    print_pyobj( codeblock->binary.content.names );
    printf("\n\t \t.varnames:");
    print_pyobj( codeblock->binary.content.varnames );
    printf("\n\t \t.freevars:");
    print_pyobj( codeblock->binary.content.freevars );
    printf("\n\t \t.cellvars:");
    print_pyobj( codeblock->binary.content.cellvars );
    //trailer
    printf("\n\t trailer:\n");
    printf("\t \tfilename:");
    print_pyobj( codeblock->binary.trailer.filename );
    printf("\n\t \tname:");
    print_pyobj( codeblock->binary.trailer.name );
    printf("\n\t firstlineno: ""%" PRIu32 "\n", codeblock->binary.trailer.firstlineno);
    printf("\t \tlnotab:\n");
    // print_pyobj( codeblock->binary.trailer.lnotab );
}


void string_print (void* string){
  char* strg = string;
  printf("%s\n",strg );
}

int char_print_2 (void* test){
  char* strg = (char*) test;
  printf("%c\n", *strg );
  return 0;
}

int char_delete (void* char_){
  free (char_);
  return 0;
}

char* str_sans_guillemets (char* string){
  unsigned int i;
  char* new_string = calloc (strlen(string) - 1, sizeof(char));
  for ( i = 1; i < strlen(string)-1; i++) {
    new_string[i-1] = string[i];
  }
  free (string);
  return new_string;
}
//-------------------------------------------------------------

int fill_pyobj_list (pyobj_t pyobj_list, list_t* list, list_t* type ){

  int i = 0;
  pyobj_list->type = PYOBJ_LIST;
  pyobj_list->py.list.size = (int32_t) list_length( *list );; //nombres d'éléments de type string

  //allouer un tableau pour placer les constantes
  pyobj_t * pyobj_tab = calloc(pyobj_list->py.list.size, sizeof(*pyobj_tab));

  for ( i = 0; i < (int) pyobj_list->py.list.size; i++)
  {
    pyobj_tab[i] = pyobj_new();
    // printf("tableau de type: %d\n", (int) *((char*) list_first( *type )) );
    // printf("tableau de type: %c\n",  (char) *((char*) list_first( *type )) );

    switch ( (int) *((char*) list_first( *type )) )
    {
    case (int) PYOBJ_STRING:
      pyobj_tab[i]->py.string.buffer = strdup ( list_first( *list ) );  //contenu de la chaine de caractère
      pyobj_tab[i]->py.string.length = strlen( list_first( *list ) );  //longueur de la chaine de caractère (+1 pour le \0)
      pyobj_tab[i]->type = PYOBJ_STRING;
    break;

    case (int) PYOBJ_INT:
      pyobj_tab[i]->type = PYOBJ_INT;
      sscanf( list_first( *list ), "%" SCNi32, &pyobj_tab[i]->py.number.integer);
    break;

    case (int) PYOBJ_INT64:
      pyobj_tab[i]->type = PYOBJ_INT64;
      sscanf( list_first( *list ), "%" SCNi64, &pyobj_tab[i]->py.number.integer64);
    break;

    case (int) PYOBJ_FLOAT:
      pyobj_tab[i]->type = PYOBJ_FLOAT;
      sscanf( list_first( *list ), "%lf", &pyobj_tab[i]->py.number.real);
    break;

    case (int) PYOBJ_NONE:
      pyobj_tab[i]->type = PYOBJ_NONE;
    break;

    //complex a faire

    default: pyobj_tab[i]->type = PYOBJ_NONE;
    }

    *list = list_next( *list );
    *type = list_next( *type );
  }

  pyobj_list->py.list.value = pyobj_tab;  //mettre le tableau de pyobj dans le champ value de la liste
  return 1;
}

//-------------------------------------------------------------

int fill_timestamp ( py_codeblock* codeblock ){
  time_t t;
  time(&t);
  //printf("\n current time is : %s",  ctime(&t));
  codeblock->binary.header._1.timestamp = t;
  return 1;
}

//-----------start_fill_functions---------------------------------------

// // 〈eol〉 : := ( [{skip::‘skip::blank’}] [{‘skip::comment’}] {‘newline’} )* [{’skip::blank’}]
int fill_eol ( list_t * lexems) {
  //printf ( " filling eol \n " ) ;
  list_t lex = *lexems;

  //si ça n'est ni un blank ni un tab ni un espace ni un comment
  if ( next_lexem_is ( &lex , "skip::blank" ) == 0 && next_lexem_is ( &lex , "skip::comment" ) == 0 && next_lexem_is( &lex, "newline" ) == 0 )
  {
    return -1;
  }

  while ( next_lexem_is ( &lex , "skip::blank" ) == 1 || next_lexem_is ( &lex , "skip::comment" ) == 1 || next_lexem_is( &lex, "newline" ) == 1 )
  {
    lexem_advance ( &lex ) ;
  }

  *lexems = lex;
  return 0;
}

//〈interned-strings〉 : := {‘dir::interned’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int fill_interned_strings ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling interned strings \n " ) ;
  list_t lex = *lexems;


  if ( next_lexem_is ( &lex , "dir::interned" ) == 0 )
  {
    print_parse_error("lack .interned", lex);
    return -1;
  }

  lexem_advance ( &lex ) ;

  //on fait les allocations une fois qu'on sait qu'il y a quelque chose à remplir
  list_t list = list_new();
  list_t type = list_new();
  char* type_du_pyobj = malloc( sizeof( char ) );
  *type_du_pyobj = PYOBJ_STRING;
  char* value;


  if ( fill_eol ( &lex ) == -1 ) return -1;


  while ( next_lexem_is ( &lex , "string" ) == 1 )
  {
    // printf("lexem print:" );
    // lexem_print( lexem_peek( &lex ) );
    value = strdup ( (lexem_peek( &lex ) )->value );
    value = str_sans_guillemets(value);
    list = list_add_last( list, value );  //mettre la valeur du string dans la liste
    type = list_add_last( type, type_du_pyobj );
    // list_print(list, string_print);
    // list_print(type, char_print_2);
    lexem_advance ( &lex ) ;
    if (fill_eol( &lex) == -1)
    {
      return -1;
    }
  }

  list_t list_save = list;
  list_t type_save = type;
  fill_pyobj_list( codeblock->binary.content.interned, &list, &type);
  list_delete(list_save, char_delete);
  list_delete(type_save, NULL);
  free(type_du_pyobj);
  *lexems = lex;
  return 0 ;
}


// 〈names〉 : := {‘dir::names’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int fill_names ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling names \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::names" ) == 0 )
  {
    print_parse_error("lack .names", lex);
    return -1;
  }
  lexem_advance ( &lex );

  //on fait les allocations une fois qu'on sait qu'il y a quelque chose à remplir
  list_t list = list_new();
  list_t type = list_new();
  char* type_du_pyobj = malloc( sizeof( char ) );
  char* buffer;
  *type_du_pyobj = PYOBJ_STRING;

  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  while ( next_lexem_is ( &lex , "string" ) == 1 )
  {
    buffer = strdup( lexem_peek( &lex )->value );
    buffer = str_sans_guillemets(buffer);
    list = list_add_last( list, buffer);  //mettre la valeur du string dans la liste
    type = list_add_last( type, type_du_pyobj );
    lexem_advance ( &lex ) ;

    if ( fill_eol ( &lex ) == -1 )
    {
      return -1;
    }
  }

  list_t list_save = list;
  list_t type_save = type;
  fill_pyobj_list( codeblock->binary.content.names, &list, &type);
  list_delete(list_save, char_delete);
  list_delete(type_save, NULL);
  free(type_du_pyobj);
  *lexems = lex;
  return 0 ;
}


// 〈varnames〉 : := {‘dir::varnames’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int fill_varnames ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling varnames \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::varnames" ) == 0 )
  {
    return -1;
  }
  lexem_advance ( &lex ) ;

  //on fait les allocations une fois qu'on sait qu'il y a quelque chose à remplir
  list_t list = list_new();
  list_t type = list_new();
  char* type_du_pyobj = malloc( sizeof( char ) );
  char* buffer;
  *type_du_pyobj = PYOBJ_STRING;


  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  while ( next_lexem_is ( &lex , "string" ) == 1 )
  {
    buffer = strdup( lexem_peek( &lex )->value );
    buffer = str_sans_guillemets(buffer);
    list = list_add_last( list, buffer);  //mettre la valeur du string dans la liste
    type = list_add_last( type, type_du_pyobj );
    lexem_advance ( &lex ) ;

    if ( fill_eol ( &lex ) == -1 )
    {
      return -1;
    }
  }

  list_t list_save = list;
  list_t type_save = type;
  fill_pyobj_list( codeblock->binary.content.varnames, &list, &type);
  list_delete(list_save, char_delete);
  list_delete(type_save, NULL);
  free(type_du_pyobj);

  *lexems = lex;
  return 0 ;
}


// 〈freevars〉 : := {‘dir::freevars’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int fill_freevars ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling freevars \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::freevars" ) == 0 )
  {
    return -1;
  }
  lexem_advance ( &lex ) ;

  //on fait les allocations une fois qu'on sait qu'il y a quelque chose à remplir
  list_t list = list_new();
  list_t type = list_new();
  char* type_du_pyobj = malloc( sizeof( char ) );
  char* buffer;
  *type_du_pyobj = PYOBJ_STRING;

  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  while ( next_lexem_is ( &lex , "string" ) == 1 )
  {
    buffer = strdup( lexem_peek( &lex )->value );
    buffer = str_sans_guillemets(buffer);
    list = list_add_last( list, buffer);  //mettre la valeur du string dans la liste
    type = list_add_last( type, type_du_pyobj );
    lexem_advance ( &lex ) ;

    if ( fill_eol ( &lex ) == -1 )
    {
      return -1;
    }
  }

  list_t list_save = list;
  list_t type_save = type;
  fill_pyobj_list( codeblock->binary.content.freevars, &list, &type);
  list_delete(list_save, char_delete);
  list_delete(type_save, NULL);
  free(type_du_pyobj);
  *lexems = lex;
  return 0 ;
}

// 〈cellvars〉 : := {‘dir::cellvars’} 〈eol〉 ( {‘string’} 〈eol〉 )*
int fill_cellvars ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling cellvars \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::cellvars" ) == 0 )
  {
    return -1;
  }
  lexem_advance ( &lex ) ;

  //on fait les allocations une fois qu'on sait qu'il y a quelque chose à remplir
  list_t list = list_new();
  list_t type = list_new();
  char* type_du_pyobj = malloc( sizeof( char ) );
  char* buffer;
  *type_du_pyobj = PYOBJ_STRING;


  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  while ( next_lexem_is ( &lex , "string" ) == 1 )
  {
    buffer = strdup( lexem_peek( &lex )->value );
    buffer = str_sans_guillemets(buffer);
    list = list_add_last( list, buffer);  //mettre la valeur du string dans la liste
    type = list_add_last( type, type_du_pyobj );
    lexem_advance ( &lex ) ;

    if ( fill_eol ( &lex ) == -1 )
    {
      return -1;
    }
  }

  list_t list_save = list;
  list_t type_save = type;
  fill_pyobj_list( codeblock->binary.content.cellvars, &list, &type);
  list_delete(list_save, char_delete);
  list_delete(type_save, NULL);
  free(type_du_pyobj);
  *lexems = lex;
  return 0 ;
}



//-----------------------------------------------------------



// // 〈set-version-pyvm〉 : := {‘dir::set’} {‘skip::blank’} {‘version_pyvm’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int fill_set_version_pyvm ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set version pyvm \n " ) ;
  int value;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 )
  {
    print_parse_error("lack .set", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::version_pyvm" ) == 0 )
  {
    print_parse_error("lack version_pyvm", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 )
  {
    print_parse_error("lack integer next to version_pyvm", lex);
    return -1;
  }
  sscanf((lexem_peek ( &lex ))->value, "%d", &value);
  lexem_advance ( &lex ) ;

  //Fonctions parse avancent
  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  codeblock->version_pyvm = value;
  *lexems = lex;
  return 0 ;
}



// // 〈set-flags〉 : := {‘dir::set’} {‘skip::blank’} {‘flags’} {‘skip::blank’} {‘integer::hex’} 〈eol〉
int fill_set_flags ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set flags \n " ) ;
  unsigned int flags;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 )
  {
    print_parse_error("lack .set", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::flags" ) == 0 )
  {
    print_parse_error("lack flags", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::hex" ) == 0 )
  {
    print_parse_error("lack hex next to flags", lex);
    return -1;
  }
  sscanf((lexem_peek ( &lex ))->value, "%X", &flags);

  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  codeblock->header._1.flags = (uint32_t) flags;
  *lexems = lex;
  return 0 ;
}

// // 〈set-filename〉 : := {‘dir::set’} {‘skip::blank’} {‘set::filename’} {‘skip::blank’} {‘string’} 〈eol〉
int fill_set_filename ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set filename \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 )
  {
    print_parse_error("lack .set", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::filename" ) == 0 )
  {
    print_parse_error("lack filename", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "string" ) == 0 )
  {
    print_parse_error("lack string", lex);
    return -1;
  }
  codeblock->binary.trailer.filename->type = PYOBJ_STRING;
  codeblock->binary.trailer.filename->refcount = 0;
  codeblock->binary.trailer.filename->py.string.buffer = strdup ( (lexem_peek ( &lex ))->value );
  codeblock->binary.trailer.filename->py.string.buffer = str_sans_guillemets(codeblock->binary.trailer.filename->py.string.buffer);
  codeblock->binary.trailer.filename->py.string.length = strlen (codeblock->binary.trailer.filename->py.string.buffer);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) {
    return -1;
  }

  *lexems = lex;
  return 0 ;
}

// // 〈set-name〉 : := {‘dir::set’} {‘skip::blank’} {‘name’} {‘skip::blank’} {‘string’} 〈eol〉
int fill_set_name ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set name \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    print_parse_error("lack .set", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::name" ) == 0 ) {
    print_parse_error("lack name", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "string" ) == 0 ) {
    print_parse_error("lack string", lex);
    return -1;
  }
  codeblock->binary.trailer.name->type = PYOBJ_STRING;
  codeblock->binary.trailer.name->refcount = 0;
  codeblock->binary.trailer.name->py.string.buffer = strdup ( (lexem_peek ( &lex ))->value );
  codeblock->binary.trailer.name->py.string.buffer = str_sans_guillemets(codeblock->binary.trailer.name->py.string.buffer);
  codeblock->binary.trailer.name->py.string.length = strlen (codeblock->binary.trailer.name->py.string.buffer);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) {
    return -1;
  }

  *lexems = lex;
  return 0 ;
}


// // 〈set-source-size〉 : := {‘dir::set’} {‘skip::blank’} {‘source_size’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int fill_set_source_size ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set source size \n " ) ;
  uint32_t source_size;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::source_size" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integer", lex);
    return -1;
  }
  //source_size = (uint32_t)(lexem_peek ( &lex ))->value;
  sscanf((lexem_peek ( &lex ))->value, "%" SCNu32, &source_size);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == 0 ) {
    return -1;
  }

  codeblock->binary.header._1.source_size = source_size;
  *lexems = lex;
  return 0 ;
}


// // 〈set-stack-size〉 : := {‘dir::set’} {‘skip::blank’} {‘stack_size’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int fill_set_stack_size ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set stack size \n " ) ;
  uint32_t stack_size;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    print_parse_error("lack .set", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::stack_size" ) == 0 ) {
    print_parse_error("lack stack size", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integer", lex);
    return -1;
  }
  //stack_size = (uint32_t)(lexem_peek ( &lex ))->value;
  sscanf((lexem_peek ( &lex ))->value, "%" SCNu32, &stack_size);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) {
    return -1;
  }

  codeblock->header._1.stack_size = stack_size;
  *lexems = lex;
  return 0 ;
}


// // 〈set-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘arg_count’} {‘skip::blank’}{‘integer::dec’} 〈eol〉
int fill_set_arg_count ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set arg count \n " ) ;
  uint32_t arg_count;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    print_parse_error("lack .set", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::arg_count" ) == 0 ) {
    print_parse_error("lack arg_count", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integred", lex);
    return -1;
  }
  //arg_count = (uint32_t)(lexem_peek ( &lex ))->value;
  sscanf((lexem_peek ( &lex ))->value, "%" SCNu32, &arg_count);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  codeblock->header._1.arg_count = arg_count;
  *lexems = lex;
  return 0 ;
}


// // 〈set-kwonly-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘kwonly_arg_count’}{‘skip::blank’} {‘integer::dec’} 〈eol〉
int fill_set_kwonly_arg_count ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set kwonly arg count \n " ) ;
  uint32_t kwonly_arg_count;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::kwonly_arg_count" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integer", lex);
    return -1;
  }
  //kwonly_arg_count = (uint32_t)(lexem_peek ( &lex ))->value;
  sscanf((lexem_peek ( &lex ))->value, "%" SCNu32, &kwonly_arg_count);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) {
    return -1;
  }

  codeblock->header._1.kwonly_arg_count = kwonly_arg_count;
  *lexems = lex;
  return 0 ;
}


// // 〈set-posonly-arg-count〉 : := {‘dir::set’} {‘skip::blank’} {‘posonly_arg_count’}{‘skip::blank’} {‘integer::dec’} 〈eol〉
int fill_set_posonly_arg_count ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set posonly arg count \n " ) ;
  uint32_t posonly_arg_count;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::set" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "set::posonly_arg_count" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integer", lex);
    return -1;
  }
  //posonly_arg_count = (uint32_t)(lexem_peek ( &lex ))->value;
  sscanf((lexem_peek ( &lex ))->value, "%" SCNu32, &posonly_arg_count);
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) {
    return -1;
  }

  codeblock->header._1.posonly_arg_count = posonly_arg_count;
  *lexems = lex;
  return 0 ;
}


//remplissage au livrable 3
// // 〈insn〉 : := {‘insn::0’} | {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} )
int fill_insn ( list_t * lexems ) {
  //printf ( " filling insn \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "insn::0" ) || next_lexem_is ( &lex , "insn::1" ) )
  {

    lexem_advance ( &lex );
    if( next_lexem_is ( &lex , "integer::dec" ) || next_lexem_is ( &lex , "symbol" ) )
    {
      *lexems = lex;
      return 0 ;
    }
    else  return -1;
  }

return -1;
}


//<constant> : := {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} |<tuple> | <function>
int fill_constant ( list_t * lexems, list_t* constant_list, list_t* type ) {
  //printf ( " filling constant \n " ) ;
  list_t lex = *lexems;
  char* type_du_pyobj = malloc( sizeof( char ) );
  // char* buffer;


  if ( next_lexem_is ( &lex , "integer" ))
  {
    char* buffer = strdup( lexem_peek( &lex )->value );
    *constant_list = list_add_last( *constant_list, buffer );
    *type_du_pyobj = PYOBJ_INT;
    *type = list_add_last( *type, type_du_pyobj);
    lexem_advance ( &lex );
    *lexems = lex;
    return 0 ;
  }

  else if (next_lexem_is ( &lex , "number::float" ))
  {
    char* buffer = strdup( lexem_peek( &lex )->value );
    *constant_list = list_add_last( *constant_list, buffer );
    *type_du_pyobj = PYOBJ_FLOAT;
    *type = list_add_last( *type, type_du_pyobj);
    lexem_advance ( &lex );
    *lexems = lex;
    return 0 ;
  }

  // else if (next_lexem_is ( &lex , "complex::float" ))
  // {
  //   *constant_list = list_add_last( constant_list, ( lexem_peek( &lex ) )->value );
  //   *type = list_add_last( type, PYOBJ_FLOAT);
  //   lexem_advance ( &lex );
  //   *lexems = lex;
  //   return 0 ;
  // }

  else if (next_lexem_is ( &lex , "string" ))
  {
    char* buffer = strdup( lexem_peek( &lex )->value );
    buffer = str_sans_guillemets(buffer);
    *constant_list = list_add_last( *constant_list, buffer );
    *type_du_pyobj = PYOBJ_STRING;
    *type = list_add_last( *type, type_du_pyobj);
    lexem_advance ( &lex );
    *lexems = lex;
    return 0 ;
  }

  else if (next_lexem_is ( &lex , "pycst" ) )
  {
    char* buffer = strdup( lexem_peek( &lex )->value );
    *constant_list = list_add_last( *constant_list, buffer );
    *type_du_pyobj = PYOBJ_NONE;
    *type = list_add_last( *type, type_du_pyobj);
    lexem_advance ( &lex );
    *lexems = lex;
    return 0 ;
  }


  else if (fill_tuple( &lex, constant_list, type ) == 0 )
  {
    *lexems = lex;
    return 0;
  }

  py_codeblock* codeblock = codeblock_new();
  if (fill_function( &lex, codeblock) == 0 )
  {
    pyobj_t pyobj = pyobj_new();
    pyobj->type = PYOBJ_CODE;
    pyobj->py.codeblock = codeblock;
    *constant_list = list_add_last( *constant_list, pyobj );
    *type_du_pyobj = PYOBJ_CODE;
    *type = list_add_last( *type, type_du_pyobj);
    lexem_advance ( &lex );
    *lexems = lex;
    return 0;
  }

  free( type_du_pyobj );
  codeblock_delete(codeblock);
  return -1;
}



//<list> : := {‘brack::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘brack::right’}
int fill_list ( list_t * lexems, list_t* constant_list, list_t* type ) {
  //printf ( " filling list \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "brack::left" ) == 0)
  {
    print_parse_error("lack brack left", lex);
    return -1;
  }
  lexem_advance ( &lex );

  while ( fill_constant ( &lex, constant_list, type  ) == 0 ){;}


  if ( next_lexem_is ( &lex , "brack::right" ) == 0)
  {
    print_parse_error("lack brack right", lex);
    return -1;
  }
  lexem_advance ( &lex );

  *lexems = lex;
  return 0;
}


//<tuple> : := {‘paren::left’} ({’skip::blank’} <constant>)* [{’skip::blank’}] {‘paren::right’}
int fill_tuple ( list_t * lexems, list_t* constant_list, list_t* type  ) {
  //printf ( " filling tuple \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "paren::left" ) == 0 )
  {
    return -1;
  }

  lexem_advance ( &lex ) ;

  while ( fill_constant ( &lex, constant_list, type ) == 0 ){;}

    if ( next_lexem_is ( &lex , "paren::right" ) == 0)
    {
      return -1;
    }

    lexem_advance ( &lex );
    *lexems = lex;
    return 0;
}


// 〈constants〉 : := {‘dir::consts’} 〈eol〉 ( 〈constant〉 〈eol〉 )*
int fill_constants ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling constants \n " ) ;
  list_t lex = *lexems;
  list_t constant_list = list_new();
  list_t type = list_new();


  if ( next_lexem_is ( &lex , "dir::consts" ) == 0 )
  {
    print_parse_error("lack .consts", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;


  if ( fill_eol ( &lex ) == -1 )
  {
    return -1;
  }

  while ( fill_constant ( &lex, &constant_list, &type  ) == 0 )
  {
    if (fill_eol( &lex) == -1)
    {
      return -1;
    }
  }

  list_t type_save = type;
  list_t constant_list_save = constant_list;
  fill_pyobj_list( codeblock->binary.content.consts, &constant_list, &type);
  *lexems = lex;
  list_delete (constant_list_save, char_delete);
  list_delete (type_save, char_delete);
  *lexems = lex;
  return 0 ;
}


//remplissage au livrable 3
// 〈code〉 : := {‘dir::text’} 〈eol〉 ( 〈assembly-line〉 〈eol〉 )*
int fill_code ( list_t * lexems ) {
  //printf ( " filling code \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::text" ) == 0 ) {
    print_parse_error("lack .text", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) {
    return -1;
  }

  while ( fill_assembly_line( &lex ) == 0)
  {
    lexem_advance ( &lex ) ;

    if ( fill_eol ( &lex ) == -1 )
    {
      return -1;
    }
  }

  *lexems = lex;
  return 0 ;
}


// // 〈assembly-line〉 : := 〈insn〉 | 〈source-lineno〉 | 〈label〉
int fill_assembly_line ( list_t * lexems ) {
  //printf ( " filling assembly line \n " ) ;
  list_t lex = *lexems;

  if ( fill_insn ( &lex ) == 0)
  {
    *lexems = lex;
    return 0 ;
  }

  else if ( fill_source_lineno( &lex ) == 0 )
  {
    *lexems = lex;
    return 0 ;
  }

  else if ( fill_label( &lex ) == 0)
  {
    *lexems = lex;
    return 0 ;
  }

  return -1;
}

// remlissage au livrable 3
// // 〈label〉 : := {‘symbol’} {‘skip::blank’} {‘colon’}
int fill_label ( list_t * lexems ) {
  //printf ( " filling label \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "symbol" ) == 0 ) {
    return -1;
  }

  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "colon" ) == 0 ) {
    print_parse_error("error colon", lex);
    return -1;
  }

  *lexems = lex;
  return 0 ;
}

// livrable 3
// // 〈source-lineno〉 : := {‘dir::line’} {‘skip::blank’} {‘integer::dec’}
int fill_source_lineno ( list_t * lexems) {
  //printf ( " filling source lineno \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::line" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integer", lex);
    return -1;
  }
  *lexems = lex;
  return 0 ;
}


// // 〈set-directives〉 : := 〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉] 〈set-stack-size〉 〈set-arg-count〉 [set-kwonly-arg-count] [set-posonly-arg-count]
int fill_set_directives ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling set directives \n " ) ;
  list_t lex = *lexems;

  if ( -1 == fill_set_version_pyvm ( &lex, codeblock  ) ) {
    return -1;
  }

  if ( -1 == fill_set_flags ( &lex, codeblock  ) ) {
    return -1;
  }

  if ( -1 == fill_set_filename ( &lex, codeblock  ) ) {
    return -1;
  }

  if ( -1 == fill_set_name ( &lex, codeblock  ) ) {
    return -1;
  }

  //Les fonctions parse avancent toute seule
  // if ( fill_set_source_size ( &lex ) == 0 ){}
  fill_set_source_size ( &lex, codeblock  );

  if ( -1 == fill_set_stack_size ( &lex, codeblock  ) ) {
    return -1;
  }

  if ( -1 == fill_set_arg_count ( &lex, codeblock  ) ) {
    return -1;
  }

  // if (fill_set_kwonly_arg_count ( &lex ) == 0 ) {}
  fill_set_kwonly_arg_count ( &lex, codeblock  );
  // if (fill_set_posonly_arg_count ( &lex ) == 0 ) {}
  fill_set_posonly_arg_count ( &lex, codeblock  );
  *lexems = lex;
  return 0 ;
}


//<prologue> : := <set-directives> <interned-strings> <constants> <names> [<varnames> <freevars> <cellvars>]
int fill_prologue ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling prologue \n " ) ;
  list_t lex = *lexems;

  if ( -1 == fill_set_directives ( &lex, codeblock  ) ) return -1;

  fill_interned_strings ( &lex, codeblock  ) ;

  if ( -1 == fill_constants ( &lex, codeblock  ) ) return -1;

  fill_names ( &lex, codeblock );


  // if ( 0 == fill_varnames( &lex ) ){}
  fill_varnames( &lex, codeblock  );
  // if ( 0 == fill_freevars ( &lex )){}
  fill_freevars ( &lex, codeblock  );
  // if ( 0 == fill_cellvars( &lex ) ){}
  fill_cellvars( &lex, codeblock  );

  *lexems = lex;
  return 0 ;
}

// <pys> : := <eol>* <prologue> <code>
int fill_pys ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling pys \n " ) ;
  list_t lex = *lexems;

  while( fill_eol ( &lex ) == 0 ){}

  if ( fill_prologue ( &lex, codeblock  ) == -1 ) return -1;

  if ( fill_code ( &lex ) == -1 ) return -1;

  *lexems = lex;
  return 0 ;
}

// <function> : := {‘dir::code_start’} {’integer’} <eol> <pys> {‘dir::code_end’}
int fill_function ( list_t * lexems, py_codeblock* codeblock ) {
  //printf ( " filling function \n " ) ;
  list_t lex = *lexems;

  if ( next_lexem_is ( &lex , "dir::code_start" ) == 0 ) {
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( next_lexem_is ( &lex , "integer::dec" ) == 0 ) {
    print_parse_error("lack integer", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;

  if ( fill_eol ( &lex ) == -1 ) return -1;

  if ( fill_pys ( &lex, codeblock ) == -1 ) return -1;

  if ( next_lexem_is ( &lex , "dir::code_end" ) == 0 ) {
    print_parse_error("lack .code_end", lex);
    return -1;
  }
  lexem_advance ( &lex ) ;
  *lexems = lex;
  return 0 ;
}
