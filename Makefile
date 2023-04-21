# Ce makefile est destine a compiler et créer les programmes executables organisés en repertoires src, tests, include, obj, bin
#	tests : contient tous les programmes, de tests ou autre. Chaque fichier contient un main
#	src : contient tous les fichiers sources C des modules, comme list.c, graph.c, aretes.c, etc...
#	include : contient tous les fichiers d'entete .h, en particulier tous ceux des modules comme list.h, graph.h, aretes.h, ...
# 	obj : ne pas oublier de créer ce repertoire, qui contiendra tous les fichiers objet issus de la compilation
# 	bin : ne pas oublier de créer ce repertoire, qui contiendra tous les programmes executables issus de la compilation/edition des liens

# Flag de compilation avec le debug possible
CFLAGS = -Wall -Wextra -ggdb3 -Iinclude

# CFLAGS=-c -g -g `pkg-config --cflags gtk+-3.0` -I ../include -Iinclude
# Flag pour l'edition des liens, juste la bibliotheque math a ajouter
LFLAGS = -ldl -lm

FUNC_TESTS_SRC = $(wildcard prog/*.c)
FUNC_TESTS_BIN = $(subst prog, bin, $(FUNC_TESTS_SRC:%.c=%.exe))

UNIT_TESTS_SRC = $(wildcard tests/unit/*.c)
UNIT_TESTS_BIN = $(subst tests/unit, bin/unit, $(UNIT_TESTS_SRC:%.c=%.exe))

SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
INCLUDES = $(wildcard include/*/*.h)

all : $(FUNC_TESTS_BIN) $(UNIT_TESTS_BIN)

bin/%.exe : prog/%.o $(OBJ) $(INCLUDES)
	@mkdir -p bin
	$(CC) $(OBJ) $< $(LFLAGS) -o $@

bin/unit/%.exe : tests/unit/%.o $(OBJ) $(INCLUDES)
	@mkdir -p bin/unit
	$(CC) $(OBJ) $< $(LFLAGS) -o $@

clean :
	$(RM) $(OBJ)
	$(RM) $(FUNC_TESTS_BIN) $(UNIT_TESTS_BIN)
	find . -name "*~" -delete
