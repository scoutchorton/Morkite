#
# General C/C++ makefile
# scoutchorton, 2022
#

#
# General project details
#

#Name of the project and executable
NAME = morkite
#Language used (C or C++)
LANG = C++
#Flags for gcc/g++
FLAGS := -Wall -c
#Libraries that the program uses
LIBS :=
#Flags for gcc/g++ when compiling for debug
DEBUG_FLAGS = -ggdb
# Compilers
C_CC = gcc
CPP_CC = g++











#############
# Functions #
#############

#Replica of the Linux `uniq` command
_uniq_fltr = ${filter-out ${firstword ${1}},${1}} ${firstword ${1}}
uniq = ${if ${filter-out ${words ${1}},${words ${2}}},${call uniq,${call _uniq_fltr,${1}},${2} n},${1}}

#Get files recrusively
subfiles = ${strip ${foreach ITEM,${wildcard $1*},${call subfiles,${ITEM}/} ${wildcard ${ITEM}/*}}}
subdirs = ${call uniq,${dir ${call subfiles,$1}}}

#Get index of item in list
_index_iter = ${if ${filter-out $1,${firstword $2}},w ${call _index_iter,$1,${wordlist 2,${words $2},$2}},w}
index = ${words ${call _index_iter ,$1,$2}}

#Repeat string multiple times
repeat = ${if ${filter-out $2,${words $3}},$1${call repeat,$1,$2,w $3},}

#############
# Variables #
#############

#Folders
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

#Misc
EXTS = c cc cp cxx cpp CPP c++ C
CC = ${CPP_CC}
.DEFAULT_GOAL := __main
FLAGS := ${FLAGS} -I ${INCDIR}

#Language verification
ifeq "${LANG}" "C++"
	LANG = c++
else ifeq "${LANG}" "c++"
	LANG = c++
else ifeq "${LANG}" "C"
	LANG = c
else ifeq "${LANG}" "c"
	LANG = c
else
	${error Language ${LANG} not understood, please use C or C++}
endif

#C variations
ifeq "${LANG}" "c"
	EXTS = c
	CC = ${C_CC}
endif

#Source/object files
SRC = ${strip ${foreach EXT,${EXTS},${filter %.${EXT},${call subfiles,${SRCDIR}}}}}
OBJ = ${strip ${foreach EXT,${EXTS},${patsubst ${SRCDIR}%.${EXT},${OBJDIR}%.o,${filter %.${EXT},${SRC}}}}}

######################
# Compiling recipies #
######################

.SECONDEXPANSION:

#Compile executable
${BINDIR}/${NAME}: obj ${OBJ} bin
	@echo "[EXE] ${notdir $@}"
	${CC} ${FLAGS} -o $@ ${OBJ} ${LIBS}

#Compile each file to an object
${OBJ}: $${dir $$@} $${wildcard $${foreach EXT,$${EXTS},$${patsubst $${OBJDIR}%.o,$${SRCDIR}%.$${EXT},$$@}}}
	@echo "${call repeat, ,${words ${subst /, ,${patsubst %/, ,$@}}}} [OBJ] [${call index,$@,${OBJ}}/${words ${OBJ}}] ${notdir $@}"
	${CC} -c ${FLAGS} -o $@ ${filter-out $<,$^} ${LIBS}

#Create folders
obj bin ${call uniq,${dir ${OBJ}}}:
	@echo "${call repeat, ,${words ${subst /, ,$@}}} [DIR] $@"
	@mkdir -p $@

#Allow for debugging
.PHONY: debug
debug: FLAGS := ${DEBUG_FLAGS} ${FLAGS}
debug: ${BINDIR}/${NAME}

#Cleanup compilation data
.PHONY: clean
clean:
	@rm -rf obj bin

#Compile everything
.PHONY: all
all: ${OBJ} ${BINDIR}/${NAME}

#Compile the main file
.PHONY: __main
__main: ${BINDIR}/${NAME}
