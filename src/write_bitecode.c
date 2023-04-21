
/**
 * @file write_bitecode.c
 * @author Melissa AKIKI
 * @date Wed Oct  19
 * @brief define funtions to serialisation
 *
 */

#include <assert.h>
#include <../include/pyas/all.h>



//fonction that writes on file the  marker of each type
void parsing_type(FILE *fp, pyobj_t obj)
{
  /* creation of all the variable I will need*/
  int i;//counter
  int size;// to fill in a size
  int ii;//variable of type int that I will need to fill
  int z=0;//variable I need to be set to zero
  uint j;//unsigned counter
  uint s;//unsigned size

  /*switch case to know where I am*/
switch (obj->type){
case PYOBJ_NULL: fwrite(&z,4,1,fp);break;

case PYOBJ_NONE :fwrite("N",1,1,fp);break;

case PYOBJ_TRUE:fwrite("T",1,1,fp);break;

case PYOBJ_FALSE:fwrite("F",1,1,fp);break;

case PYOBJ_INT:
fwrite("i",1,1,fp);
ii= obj->py.number.integer;
 fwrite(&ii,4,1,fp);
 break;

 case PYOBJ_INT64:
 fwrite("i",1,1,fp);
 ii=obj->py.number.integer64;
 fwrite(&ii,4,1,fp);



case PYOBJ_TUPLE:
fwrite("(",1,1,fp);
size=obj->py.list.size;
fwrite(&size,4,1,fp);

for(i=0;i<size;i++){
  //recursion
  parsing_type(fp,obj->py.list.value[i]);
}
break;


case PYOBJ_STRING:
fwrite("s",1,1,fp);
int length=(obj->py.string.length);//review this line
fwrite(&length,4,1,fp);
uint i;
for(i=0; i<strlen(obj->py.string.buffer);i++){
  fwrite(&(obj->py.string.buffer[i]),1,1,fp);
}
break;

case PYOBJ_FLOAT:
fwrite("g",1,1,fp);
double d=obj->py.number.real;
fwrite(&d,8,1,fp);
break;

case PYOBJ_COMPLEX:
fwrite("y",1,1,fp);
fwrite(&(obj->py.number.complex.real),8,1,fp);//write real part first
fwrite(&(obj->py.number.complex.real),8,1,fp);//write imaginary part next
break;


case PYOBJ_LIST://[
s=obj->py.list.size;
fwrite(&s,4,1,fp);

for(j=0;j<s;j++){
  //recursion
  parsing_type(fp,obj->py.list.value[j]);
}
break;



int test;
case PYOBJ_CODE:// codeblock- sometimes list can be filled by a codeblock instead of string for example
//uint i;

//arg_count-c bon
test=(obj)->py.codeblock->header._1.arg_count;
//long argcount=(long)test;
fwrite(&test,4,1,fp);

//local count-c bon
test=(obj)->py.codeblock->header._1.local_count;
fwrite(&test,4,1,fp);

//stack_size-c bon
test=(obj)->py.codeblock->header._1.stack_size;
fwrite(&test,4,1,fp);

//flags-c bon
test=(obj)->py.codeblock->header._1.flags;
fwrite(&test,4,1,fp);


// to fill lnotab and remaining pyobj ".text"
// a partir d'ici pyasm doit avoir ete remplie (pyasm(obj);)
fwrite("s",1,1,fp);
long bytecode_length=(obj->py.codeblock->binary.content.bytecode)->py.string.length;
fwrite(&bytecode_length,4,1,fp);

for(i=0;i<bytecode_length;i++){
  fwrite(&((obj->py.codeblock->binary.content.bytecode)->py.string.buffer[i]),1,1,fp);
}

// //on veut maintenant lire les tuples
/*consts*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.consts);//coresponding fonction to know what it contains

/*names*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.names);

/*varnames*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.varnames);


/*freevars*/
fwrite("(",1,1,fp);parsing_type(fp,obj->py.codeblock->binary.content.freevars);


/*cellvars*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.cellvars);


/*filename*/
parsing_type(fp,obj->py.codeblock->binary.trailer.filename);

/*name*/
parsing_type(fp,obj->py.codeblock->binary.trailer.name);

/*lineno*/
test=(obj)->py.codeblock->binary.trailer.firstlineno;
fwrite(&test,4,1,fp);


/*lnotab*/
fwrite("s",1,1,fp);
int ii;
int l=obj->py.codeblock->binary.trailer.lnotab->py.string.length;
fwrite(&(l),4,1,fp);
for(ii=0;ii<l;ii++){
  fwrite(&(obj->py.codeblock->binary.trailer.lnotab->py.string.buffer[ii]),1,1,fp);
}

 break;
}
}






// ______________________fonction finale de serialisation____________________
int pyobj_write( FILE *fp, pyobj_t obj)
{
  /*code de serialisation */
  //ecrire a tour de role l'equivalent binaire du fichier .pys
  //en-tete n'est pas un tuple


/*variables I will need */
uint i;//unsigned counter
int test;//variable of type int I will need to fill


//version-c bon
test=(obj)->py.codeblock->version_pyvm;
// int version=atoi(testtt);
 fwrite(&test,2,1,fp);

 //0x0d0a-c bon
 int a=2573;
 fwrite(&a,2,1,fp);



//time time_stamp- faudrait remplir ca en premier
time_t t=(obj)->py.codeblock->binary.header._2.timestamp;
fwrite(&t,4,1,fp);

//write of marker code 'c'-c bon
fwrite("c",1,1,fp);

//arg_count-c bon
test=(obj)->py.codeblock->header._1.arg_count;
fwrite(&test,4,1,fp);

//local count-c bon
test=(obj)->py.codeblock->header._1.local_count;
fwrite(&test,4,1,fp);

//stack_size-c bon
test=(obj)->py.codeblock->header._1.stack_size;
fwrite(&test,4,1,fp);

//flags-c bon
test=(obj)->py.codeblock->header._1.flags;
fwrite(&test,4,1,fp);


// to fill lnotab and remaining pyobj ".text"
// a partir d'ici pyasm doit avoir ete remplie (pyasm(obj);)
fwrite("s",1,1,fp);
long bytecode_length=(obj->py.codeblock->binary.content.bytecode)->py.string.length;
fwrite(&bytecode_length,4,1,fp);

for(i=0;i<bytecode_length;i++){
  fwrite(&((obj->py.codeblock->binary.content.bytecode)->py.string.buffer[i]),1,1,fp);
}

// //on veut maintenant lire les tuples
/*consts*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.consts);

/*names*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.names);

/*varnames*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.varnames);


/*freevars*/
fwrite("(",1,1,fp);parsing_type(fp,obj->py.codeblock->binary.content.freevars);


/*cellvars*/
fwrite("(",1,1,fp);
parsing_type(fp,obj->py.codeblock->binary.content.cellvars);


/*filename*/
parsing_type(fp,obj->py.codeblock->binary.trailer.filename);

/*name*/
parsing_type(fp,obj->py.codeblock->binary.trailer.name);

/*lineno*/
test=(obj)->py.codeblock->binary.trailer.firstlineno;
fwrite(&test,4,1,fp);


/*lnotab*/
fwrite("s",1,1,fp);
int ii;
int l=obj->py.codeblock->binary.trailer.lnotab->py.string.length;
fwrite(&(l),4,1,fp);
for(ii=0;ii<l;ii++){
  fwrite(&(obj->py.codeblock->binary.trailer.lnotab->py.string.buffer[ii]),1,1,fp);
}


return 0;
}
