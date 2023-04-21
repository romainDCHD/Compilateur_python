##Projet sei AKIKI-DUCHADEAU-RASCOL
##-----------------------------------------------

note: toutes les fonction test "presentables" n'ont pas de numero. Celles dont le nom fini par 2 (ex: test-objet2.c) sont les fonctions qui nous permettent de debugguer.

###########################################################################EXECUTABLES################################################################################
#./prog/lexer.c  (/*Fonctionnel*/)
But: le programme lexer qui réalise l’analyse lexicale d’un fichier .pys passé en argument sur la ligne de commande
Tester: Tapper "./bin/lexer config/pyas.conf ./functions/function[i].pys" (depends de quelle fonction vous desirer tester)


#./prog/regex-read.c  (/*Fonctionnel*/)
But:le programme qui lit (parse) une expression régulière passée en argument sur la ligne de commande et affiche sa structure
Tester: Tapper "./bin/regexp-read [expression reguliere]"


#./prog/parser.c
But:le programme parser qui réalise l’analyse syntaxique d’un fichier .pys passé en argument sur la ligne de commande
Tester: Tapper "./bin/parser data_base.tx ./functions/function[i].pys"

#./prog/pyas.c  (/*Fonctionnel sauf pour le livrable 4*/)
But: le programme pyas qui réalise l’assemblage d’un fichier .pys passé en argument sur la ligne de commande et génère le fichier binaire pyas.pyc correspondant
Tester: -Tapper "./bin/bin config/pyas.conf ./functions/function[i].pys" (depends de quelle fonction vous desirer tester)
        -Pour compiler l'executable python ainsi obtenue, tapper "python ./bin/pyas.pyc"


#./prog/regexp-match.c  (/*Fonctionnel*/)
But: le programme qui match une expression régulière et une chaîne passées en argument sur la ligne de commande et affiche le résultat
Tester: Tapper "./bin/regexp-match [expression regulier] [source a tester]" (ex:[a-c]+ aaab)


############################################################################################################################################################
#config/pyas.conf
    But: fichier regroupant tous les types avec les definitions associées; c'est le dictionnaire complet de lexem


#config/pyas.conf.test
    But: Dictionnaire de lexem réduit pour les tests


#queue.c
  But: Définir toutes les fonctions nécéssaire à l'utilisation des queue

  Avancement: Tout fonctionne parfaitement

  Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-queue.exe -v " ou pour tester avec le type char group " ./bin/unit/test-queue-cg.exe -v ".
  Cette commande va tester les fonctions : queue_new, queue_empty, enqueue, (queue_to_list), queue_peek, dequeue, queue_length.


#list.c
  But: Définir toutes les fonctions nécéssaire à l'utilisation des queue

  Avancement: Tout fonctionne parfaitement

  Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-list.exe -v " qui a été modifié après le bootstrap
  ou pour tester list_compare Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-list2.exe -v " Fonctionnelle


#char_group.c
  But: Définir toutes les fonctions nécéssaire à l'utilisation des chargroup

  Avancement: Tout fonctionne parfaitement

  Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-char_group.exe -v "

#database.c
    But: Lire le config/pyas.conf, et inclure les informations triée dans une queue

    Avancement: Fonctionnel

    Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-database2.exe config/pyas.conf", pour afficher tout ce que fait database.c à partir du fichier complet database.txt.

#regexp.c
    But: Comparer une source char* avec une expression régulière sous forme char*

    Avancement: 3 tests sur 5 fonctionnel (mais réglages de ces problèmes sur la version adaptée à nos choix, c'est à dire char_group)

    Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-regexp.exe ".


#regexp-cg.c
    But: Comparer une source char* a une liste de  char_group

    Avancement: Fonctionnel

    Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-regexp-cg.exe  [une expression reguliere]  [une source a comparer avec]". exemple [a-c]+x aaaax

    Pour tester avec les test d'integrations : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./tests/integration/execute_tests.py runtest ./bin/unit/test-regexp-cg.exe ./tests/integration/02_test_regexp_match "

#parse.c
    But: Prendre un char* en argument et mettre les différentes unités logiques dans une liste de chargroup

    Avancement: Fonctionnel

    Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande " ./bin/unit/test-re-parse.exe   config/pyas.conf.test ".
    le programme va prendre le fichier config/pyas.conf.test et mettre les différents éléments char-group dans une liste avant d'imprimer la liste


#lexer.c
    But: Elément final: Lire un fichier assembler .pys et renvoyer une liste de lexem

    Avancement: Fonctionnel

    Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-lexer.exe config/pyas.conf.test ./functions/function1.pys ".

#lexem.c

  But: Fonctions utiles pour grammar.c

  Avancement: Fonctionnel

  Pour tester les fonctions du livrable 2: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-lexem.exe ".
  Pour tester lexem_compare : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-lexem.-compare.exe ".

#grammar.c

  But: Fonctions pour chaque non-terminal : Fonctions qui vérifient la syntaxe en renvoyant 1 ou 0

  Avancement: fonctionnel d'après les tests "à la main" effectués avec test-grammar2.c (utile pour debugger) mais le test_grammar.c (qui est plus exhaustif) ne fonctionne pas encore totalement correctement.

  Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-grammar.exe -v" (test-grammar2.c était utile pour debugguer)

#objet.c

  But: Fonction qui remplit la structure python  : Construction d’un objet de code python

  Avancement: fonctionnel

  Pour tester: Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-objet.exe"

#production_bytecode.c

  But: Fonction qui remplit le lnotab et le bytecode de la structure python

  Avancement:  fonctionnel avec function1.pys

  Pour tester la fonction opcode_is : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-opcode_is.exe -v" Fonctionnelle.

  Pour tester la fonction argument_yes_or_no : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-argument-yes-or-no.exe -v" Fonctionnelle.

  Pour tester la fonction find_the_part_instruction : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-find_the_part_instruction.exe -v" Fonctionnelle

  Pour tester la fonction length_calculated_for_bytelist : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-length-calculated-for-bytelist.exe " Fonctionnelle

  Pour tester la fonction lenght_lnotab : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-lenght-lnotab -v" Fonctionnelle

  Pour tester la fonction pyobj_from_lnotab_tab : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/pyobj-from-lnotab-tab" Fonctionnelle

  Pour tester la fonction pyobj_from_bytecode_list : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/pyobj-from-bytecode-list" Fonctionnelle

  Pour tester les fonctions sur la strcuture du dictionnaire choisie ici label_adress_t : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-dictionnaire.c" Fonctionnelle

  Pour tester la fonction pyasm : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-production-bytecode-avec-livrable-1.exe config/pyas.conf functions/function1.pys" Fonctionnelle

  ou Pour tester de manière moins exhaustive la fonction pyasm : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-production_bytecode.exe"

#write_bitecode.c

    But: Fonction qui ecrit sur un fichier en binaire l'executable de la machine virtuelle python

    Avancement: Fonctionnel

    Pour tester la fonction pyobj_write : Tapez d'abord "make" dans le terminal pour compiler, Tapez ensuite la commande "./bin/unit/test-write_bitecode.exe config/pyas.conf ./functions/function[i].pys" , un message de 'write to file ok' indiquant que l'ecriture sur le fichier a ete faite .
    -Ensuite pour visualiser  le fichier "write_bitecode.pyc" de l'executable ecrit en binaire tapper " hexdump -C write_bitecode.pyc"
    -Pour compiler l'executable python ainsi obtenue, tapper "python write_bitecode.pyc"
