/**
 * @file write_bitecode.c
 * @author Laura Rascol
 * @date Fri Oct  22
 * @brief define funtions to produce the bYtecode and the lnotab
 *
 */

#include <assert.h>
#include <../include/pyas/all.h>


/*
 *
 *      Fonction which create a new structure label_address_t
 *
 * @return                     a label_adress_t
 */
label_address_t label_address_new (char* name, int address, int address2){
  label_address_t label = malloc( sizeof(*label));
  assert (label);

  label->name = strdup(name);
  label->address_first =  address;
  label->address_end =  address2;
  return label;
}


/*
 *
 *      Fonction which delete the structure label_address_t
 *
 * @return                     a int to tell if it s ok
 */
int label_address_delete ( void* label1 ){

  label_address_t label = label1;
  free(label->name);
  free(label);
  return 0;
}

/*
 *
 *      Fonction which print the structure label_address_t
 *
 */
int label_address_print ( void* label1 ){

  label_address_t label = label1;
  return printf("[name: %s   address_first: %d    address_end: %d]\n",label->name, label->address_first, label->address_end );
}


/*
 *
 *      Fonction which return the opcode from the type which was for exemple insn::1::0x66
 *
 * @return                     a unsigned char wich is the opcode
 */
unsigned char opcode_is(lexem_t lex)
{
  assert( lexem_type(lex, "insn::") );
  unsigned char byte=0x00;
  sscanf(lex->type+9, "%hhx", &byte);
  return byte;
}


/*
 *
 *      Fonction which return the opcode from the type which was for exemple insn::1::0x66
 *
 * @return                     a unsigned char wich is the opcode
 */
unsigned char * opcode_is_char(lexem_t lex)
{
  assert( lexem_type(lex, "insn::") );
  unsigned char * byte=NULL;
  sscanf(lex->type+9, "%hhx", byte);
  return byte;
}


/*
 *
 *      Fonction which return 1 if there is an argument, 0 else
 *
 * @return                     a int
 */
int argument_yes_or_no(lexem_t lex)
{
  assert( lexem_type(lex, "insn::") );
  int arg=0;
  sscanf(lex->type+6, "%d", &arg);
  return arg;
}


/*
 *
 *      Fonction which return the pointer where you can find the first "dir::line"
 *
 * @return                     a pointer on list_t
 */
 void find_the_part_instruction(list_t* lexem){
  list_t lexems = *lexem;
  lexem_t lex = lexem_peek_pass_new_line(&lexems);

  while (strcmp( lex->type, "dir::line" ) != 0)
  {
    *lexem = lexems;
    lex = lexem_advance(&lexems);
  }
}


/*
 *
 *      Fonction which return a new string for pyobj, which is important for bytecode and lnotab
 *
 * @return                     a pyobj_t
 */
pyobj_t pyobj_new_string(int lataillefinaledubytecode)
{
  pyobj_t pyobj_de_type_string=pyobj_new();
  pyobj_de_type_string->type = PYOBJ_BITECODE_LNOTAB;
  pyobj_de_type_string->py.string.buffer = calloc ( lataillefinaledubytecode, sizeof( char ) ) ;
  return pyobj_de_type_string;
}


/*
 *
 *      Fonction which return a new string for pyobj, which is calculated with the previous list of a bytelist
 *
 * @return                     a pyobj_t
 */
int length_calculated_for_bytelist(list_t l)
{
  int lataillefinaledubytecode=0;
  lexem_t lexemOpcode;
  lexem_t suite_opcode;
  while (!list_empty(l))
  {
    lataillefinaledubytecode=lataillefinaledubytecode+1;
    lexemOpcode = lexem_peek_pass_new_line(&l);
    assert(   lexem_type(lexemOpcode, "insn::") );
    lexem_advance(&l);
    suite_opcode = lexem_peek_pass_new_line(&l);
    if (lexem_type(suite_opcode, "integer"))
    {
      lataillefinaledubytecode=lataillefinaledubytecode+2;
      lexem_advance(&l);
    }
  }
  return lataillefinaledubytecode;
}


/*
 *
 *      Fonction which return a int to know the lenth of the tab lnotab
 *
 * @return                     a int
 */
int lenght_lnotab(list_t lexem)
{
  int lenght=-2;//Car le delta line pour la première line ne doit pas être mis
  lexem_t lex=lexem_peek_pass_new_line(&lexem);
  while (!list_empty(lexem))
  {
    if(lexem_type(lex, "dir::line"))
    {
      lenght=lenght+2;
      lexem_advance(&lexem);
      lex=lexem_peek_pass_new_line(&lexem);
    }
    //avancer au prochain lexem
    else
    {
      lexem_advance(&lexem);
      lex=lexem_peek_pass_new_line(&lexem);
    }
  }
  return lenght;
}


/*
 *
 *      Fonction which return the string (type pyobj_t) associate with a list of lexems
 *
 * @return                     a pyobj_t
 */
pyobj_t pyobj_from_bytecode_list(list_t l)
{
  int i=0;
  lexem_t lexemOpcode; //STocker le lexeme de l'opcode pour en extraire largument et son numéro
  lexem_t lexemParametreDeLinstruction;
  unsigned short shortValeurInstruction ; // short <=> entier sur 2 octets
  short * adresseALaquellePlacerLesDEuxOctetsDansLeBuffer;
  unsigned char opcode;
  list_t liste_a_parcourir=l; //permet de stocker la valeur de depart de la liste car elle sera parcouru une premiere fois par length_calculated_for_bytelist

  int lataillefinaledubytecode=0;
  lataillefinaledubytecode=length_calculated_for_bytelist(l);
  pyobj_t out=pyobj_new_string(lataillefinaledubytecode);

  while (!list_empty(liste_a_parcourir))
  {
    lexemOpcode=lexem_peek_pass_new_line(&liste_a_parcourir);
    opcode=opcode_is(lexemOpcode);
    // puis pour écrire la valeur d'un unsigned char dans le tableau de char, ie dans out->py.string.buffer c'et assez simple :
    out->py.string.buffer[i] = opcode ; // ou bien utiser fwrite
    lexem_advance(&liste_a_parcourir);
    lexemParametreDeLinstruction=lexem_peek_pass_new_line(&liste_a_parcourir);
    i = i + 1;

    if (lexem_type(lexemParametreDeLinstruction, "integer"))
    {
      shortValeurInstruction = strtol(lexemParametreDeLinstruction->value, NULL, 16); // ou mieux utiliser strtol()
      // il s'agit maintenant d'écrire shortValeurInstruction en BINAIRE dans le tableau de char, ie d'entiers sur 1 octets, out->py.string.buffer
      // Difficulté : out->py.string.buffer[i] est de type char
      // une solution est d'(utiliser des casts ; il y en a d'autres
      adresseALaquellePlacerLesDEuxOctetsDansLeBuffer=(short*)(out->py.string.buffer + i);
      *adresseALaquellePlacerLesDEuxOctetsDansLeBuffer = shortValeurInstruction;
      i = i + 2 ; // car on vient de remplir 2 octets dans out->py.string.buffer
      lexem_advance(&liste_a_parcourir);
    }
  }
  out->py.string.length=lataillefinaledubytecode;
  return out;
}


/*
 *
 *      Fonction which return the string (type pyobj_t) associate with a list of address of int
 *
 * @return                     a pyobj_t
 */
pyobj_t pyobj_from_lnotab_tab(char* lnotab, int taille)
{
  // pyobj_t out=pyobj_new_string(taille);
  pyobj_t out=pyobj_new();
  out->type = PYOBJ_BITECODE_LNOTAB;
  out->py.string.length=taille;
  out->py.string.buffer = lnotab ;
  return out;
}


/*
 *
 *      Fonction which produce the bytecode and lnotab and tidy it in the pyobj_t
 *
 * @return                     a int
 */
int pyasm( pyobj_t code, list_t lexem)
{
  list_t bytecode=list_new(); //initialisation de la liste de lexem bytecode
  list_t save_bytecode;
  list_t save_lexem=lexem; //Pour calculer la longueur du tableau lntoab

  int taille_lnotab=lenght_lnotab(save_lexem); //Calcul de la taille de lnotab pour pouvoir l'allouer le plus justement posible

  list_t queue_addresse_label=queue_new(); //Allocation de la queue dans laquelle on rangera des label_adress_t dna sle cas où dans  le .pys il y aurait des symbol

  char * lnotab=calloc(taille_lnotab, sizeof(char)); //allocation du tableau lnotab avec la valeur taille aclculée au préalable
  int i_lnotab=0; //Enteir pour parcourir le tableau lnotab

  //initialisation des information à stcoker dans le lnotab
  int delta_line=0;
  int delta_octet=0;

  //deux variables pour stocker les valeurs des lignes et calculer delta_lone
  int line_before; //numéro de ligne avant
  int line_after; //Numéro de ligne après
  int address = 0; //compteur pour savoir à quel adresse on est
  int ad=0; //Int correspondant au delta adress end - adress first
  int saut_absolue=1;//1 si saut absolu 0 sinon 2 si jump_forward
  label_address_t address_label; //stocker information sous forme de label_adress_t pour l'nequeu dans un deuxième temps
  char* char_etoile_address=malloc(sizeof(char*)); //utile pour récupérer un char* à partir d'un int avec ssprintf


  lexem_t lex; //Permet de stocker lors de lexem peek pour tester des types
  lexem_t lex_bis; //Pour créer un lexme sans ligne et colonne

  //Hypothèse qu'on aura le pointeur de lexem qui pointe sur la première line des instructions
  find_the_part_instruction(&lexem);
  list_t save_lexem_second_part=lexem; //Enregistrement du pointeur sur le debut de lexem pour pouvoir la reparcourir dans un deuxième temps pour remplir bytecode

  //récuperer le premier lexem
  lex=lexem_peek_pass_new_line(&lexem);
  assert(lexem_type(lex, "dir::line"));



  //Initialiser la valeur de la première ligne

  //Pour accéder à la valeur de la line
  lexem_advance(&lexem);
  lex=lexem_peek_pass_new_line(&lexem);

  line_before=strtol(lex->value, NULL, 10);
  code->py.codeblock->binary.trailer.firstlineno=strtol(lex->value, NULL, 10);
  line_after=line_before; //Pour initialiser le premier delta_line à 0
  int go=1; //condition pour que ca rentre quand même dans le while suivant car dabord il a fallut faire linitialisation de line before

  //remplir liste pour chaque ligne
  while ((lexem_type(lex, "dir::line") || go==1) && !list_empty(lexem))
  {
    if (i_lnotab!=0) //On ne fait pas le premier deltaline
    {
      lexem_advance(&lexem);
      lex=lexem_peek_pass_new_line(&lexem);
      line_after=strtol(lex->value, NULL, 10);
      delta_line=line_after-line_before;
      lnotab[i_lnotab]=delta_line;
      i_lnotab=i_lnotab+1;
    }

    line_before=line_after;
    delta_octet=0; //reinitialiser delta octet pour chaque line differente

    //avancer au prochain lexem
    lexem_advance(&lexem);
    lex=lexem_peek_pass_new_line(&lexem);

    //tant quon passe pas à une autre ligne on examine les information contenues dans la ligne
    while(lexem_type(lex, "dir::line")==0 && !list_empty(lexem))
    {
      if(!lexem_type(lex, "symbol")) //Ca veut dire que c'est un opcode
      {

      delta_octet=delta_octet+1;
      address=address+1;

      if(lexem_type ( lex , "insn::1::0x5d" )|| lexem_type ( lex , "insn::1::0x8f" )|| lexem_type ( lex , "insn::1::0x78" ) || lexem_type ( lex , "insn::1::0x79" ) || lexem_type ( lex , "insn::1::0x7a" ) ) //|| strcmp(opcode_is_char(lex), "8f") || strcmp(opcode_is_char(lex), "78") || strcmp(opcode_is_char(lex), "79") || strcmp(opcode_is_char(lex), "7a")
      {
        saut_absolue=0;
      }
      else  if (lexem_type ( lex , "insn::1::0x6e" ))
      {
        saut_absolue=2;
      }
      //on avance afin de voir si
      lexem_advance(&lexem);
      lex=lexem_peek_pass_new_line(&lexem);
      }

      if (list_empty(lexem))
      {
        break;
      }

      //CAS DUN ARGUMENT
      if (lexem_type(lex, "integer"))
      {
        //on a donc 3 octets réservés
        delta_octet=delta_octet+2;
        address=address+2;
        lexem_advance(&lexem);
        lex=lexem_peek_pass_new_line(&lexem);
      }

      //CAS DUN LABEL Dans les dir line
      else if(lexem_type(lex, "symbol") && (lex->column!=0))//On arrive à un label
      {
        delta_octet=delta_octet+2;
        address=address+2; //On passe le label quand il est appelé de cette manière pour le lnotab
        int taille=queue_length(queue_addresse_label);
        int a=0; //Compteur lié a la taille de la queue
        if (!queue_empty(queue_addresse_label))
        {
          //On parcourt la liste afin de voir si le label existe pas déja
          while (strcmp(((label_address_t) queue_peek(queue_addresse_label))->name, lex->value)!=0 && a<taille)
          {
            queue_addresse_label=queue_next(queue_addresse_label);
            a++;
          }
        }
        //Si le label n'est pas dans la queue :
        if(a==taille || queue_empty(queue_addresse_label) || saut_absolue==2)
        {
          //si c'est un saut absolue il n'y aura pas besoin de faire de delta donc adress first =0
          if (saut_absolue==1)
          {
            address_label=label_address_new(lex->value, 0, 0);
          }
          //Si ce n'est pas un saut absolue on aura besoin de faire un deltaline
          //Aussi si saut_absolue=2 ca veut dire que c'est un jump forward donc on doit recréer un label associé dans la queue pour stocker son adresse d'appel
          else
          {
            address_label=label_address_new(lex->value, address, 0);
            saut_absolue=1;//reinitialisation
          }
          queue_addresse_label=enqueue(queue_addresse_label, address_label);
        }
        lexem_advance(&lexem);
        lex=lexem_peek_pass_new_line(&lexem);
      } //Fin du cas label pour calcul lnotab

      //CAS DUN LABEL a la fin du .pys
      else if(lexem_type(lex, "symbol") && lex->column == 0)
      {
        int taille=queue_length(queue_addresse_label);
        int a=0; //Compteur lié à la taille de la queue d'adresse label t
        int already_done=0;

        //On avance dans la queue jusqu' a rencontrer le label dont on a besoin ou sinon on le crée
        while (!queue_empty(queue_addresse_label) && a<taille)
        {
          queue_addresse_label=queue_next(queue_addresse_label);
          a++;
          //On assigne la valeur de l'adresse dans adresse end
          if (strcmp(((label_address_t) queue_peek(queue_addresse_label))->name, lex->value)==0)
          {
            ((label_address_t) queue_peek(queue_addresse_label))->address_end = address;
            already_done=1;
          }

          //L'lement de label n'est pas contenu dans la queue on doit donc le créer
          if (a==taille && already_done==0)
          {
            address_label=label_address_new(lex->value, 0, 0);
            queue_addresse_label=enqueue(queue_addresse_label, address_label);
            ((label_address_t) queue_peek(queue_addresse_label))->address_end = address;
          }
        }
        lexem_advance(&lexem);
        lex=lexem_peek_pass_new_line(&lexem);
      }
    }

    if (list_empty(lexem))
    {
      break;
    }
    //On recupere le numero de ligne ssi il ya une autre ligne derriere
    if(!list_empty(lexem))
    {
      //Ranger le delta octet dan sle tableau lnotab
      lnotab[i_lnotab]=delta_octet;
      i_lnotab=i_lnotab+1;
    }
  }

  // remplir lnotab
  code->py.codeblock->binary.trailer.lnotab=pyobj_from_lnotab_tab(lnotab ,  taille_lnotab);

  //recommencer à parcourir la liste pour cette fois ci ranger le bytecode
  lex=lexem_peek_pass_new_line(&save_lexem_second_part);
  int line;
  long int save_line=1000000;

//DEUXIEME ETAPE REMPLIR BYTECODE AVEC LADRESSE DES LABEL
  while ((lexem_type(lex, "dir::line")) && !list_empty(save_lexem_second_part))
  {
    //On avance aprs le dir line au integer corresponcant
    lexem_advance(&save_lexem_second_part);
    lex=lexem_peek_pass_new_line(&save_lexem_second_part);

    //avancer au prochain lexem qui sera un opcode
    lexem_advance(&save_lexem_second_part);
    lex=lexem_peek_pass_new_line(&save_lexem_second_part);
    int jump_forward=0;//qui permet de savoir que c'est l'instrcution jump forward afin de pouvoir gérer le delta label, pour plusieurs occurences dans la queue

    //tant quon passe pas à une autre ligne on examine les information contenues dans la ligne
    while(lexem_type(lex, "dir::line")==0 && !list_empty(save_lexem_second_part))
    {
      if(lexem_type(lex, "symbol"))
      {
        //On avance pour traiter l'opcode qui suit normalement
        lexem_advance(&save_lexem_second_part);
        lex=lexem_peek_pass_new_line(&save_lexem_second_part);
      }
      //On range l'opcode du lexem dans le byecode
      lex_bis=lexem_new(lex->type, lex->value, 0,0);
      bytecode=list_add_last(bytecode, lex_bis);
      save_bytecode=bytecode;

      if (lexem_type ( lex , "insn::1::0x6e" )) //6e seule instruction qui nécessite un jump-forward
      {
        jump_forward=1;
      }

      //on avance afin de voir si
      lexem_advance(&save_lexem_second_part);
      lex=lexem_peek_pass_new_line(&save_lexem_second_part);
      if (list_empty(save_lexem_second_part))
      {
        break;
      }

      //CAS DUN ARGUMENT
      if (lexem_type(lex, "integer"))
      {
        //On insère dans le bytecode les valeurs des octets de l'argument
        lex_bis=lexem_new(lex->type, lex->value, 0,0);
        bytecode=list_add_last(bytecode, lex_bis);
        save_bytecode=bytecode;
        lexem_advance(&save_lexem_second_part);
        lex=lexem_peek_pass_new_line(&save_lexem_second_part);
      }


      //CAS DUN LABEL Dans les dir line
      else if(lexem_type(lex, "symbol") && (lex->column!=0))//On arrive à un label
      {
        while (strcmp(((label_address_t) queue_peek(queue_addresse_label))->name, lex->value)!=0)
        {
          queue_addresse_label=queue_next(queue_addresse_label);

          //POur le cas où il y aurait un jump absolu il faut avancer jusqu'au bon label_adress dans la queue
          if (strcmp(((label_address_t) queue_peek(queue_addresse_label))->name, lex->value)==0)
          {
            //Si c'est le cas d'un jump forward, il yara plusieurs élements dans la queue
            if (jump_forward==1)
            {
              line=lex->line;
              //On va avancer jusqu' au bon label_adress_t dnas la queue correspondant au lexem qu'on lit
              if (line>save_line)
              {
                queue_addresse_label=queue_next(queue_addresse_label);
              }
              //On enregistre la ligne
              save_line=line;
              //et on met le int jump_forward à 0
              jump_forward=0;
            }
          }
        }
        lexem_advance(&save_lexem_second_part);
        lex=lexem_peek_pass_new_line(&save_lexem_second_part);
        //On fait le delta entre la'adresse de définition du label et l'adresse d'appel du label
        //Si l'instrcution ne necessite pas de delta, dan sla ormeiere partie de la fonction on s'est débrouillé pour mettre un 0 à adress_first
        ad=((label_address_t) queue_peek(queue_addresse_label))->address_end - ((label_address_t) queue_peek(queue_addresse_label))->address_first;
        //On récupère le int ad et on le transforme en char * pour pouvoir le stocker dans la liste de lexem correcpodante au bytecode
        sprintf(char_etoile_address, "%x", ad);
        bytecode=list_add_last( bytecode, lexem_new( "integer::dec", char_etoile_address, 2, 9 ));
        save_bytecode=bytecode;
      } //Fin du cas label pour calcul lnotab

      //CAS DUN LABEL a la fin du .pys
      else if(lexem_type(lex, "symbol") && lex->column==0)
      {
        //On passe le label pour pouvoir ensuite agir sur son contenu comme si c'était normal pour pouvoir le ranger dans le bytecode
        lexem_advance(&save_lexem_second_part);
        lex=lexem_peek_pass_new_line(&save_lexem_second_part);
      }
    }

    if (list_empty(save_lexem_second_part))
    {
      break;
    }
  }

  //Transformer la liste de lexem save_bytecode en pyobj et l'assigner au bon endroit du pyobj code en entrée de pyasm
  code->py.codeblock->binary.content.bytecode=pyobj_from_bytecode_list(save_bytecode);

  //On libre la mémoire interne à la fonction
  if (!queue_empty(queue_addresse_label))
  {
    queue_delete(queue_addresse_label, label_address_delete);
  }
  list_delete(save_bytecode, lexem_delete);
  free(char_etoile_address);
  //Valeur de retour
  return 0;
}
