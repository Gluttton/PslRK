#===--- Input variables                ---===#
OPTIMIZATION       ?= O3
ifdef GP
PGO                 = -fprofile-generate
endif
ifdef UP
PGO                 = -fprofile-use
endif
ifdef COV
COVERAGE            = -fprofile-arcs -ftest-coverage
endif
ifdef PROF
PROFILE             = -pg
endif
THREADS            ?= 1
DIRECTORY           = $(shell pwd)
#===--- Common variables               ---===#
C                   = gcc
INCLUDES            =
CFLAGS              = -c \
                      -std=c99 -march=native -m64 \
                      -Wall -Wextra \
                      -$(OPTIMIZATION) \
                      -DTHREADS=$(THREADS) \
                       $(PGO) \
                       $(COVERAGE) \
                       $(PROFILE) \
                      -fverbose-asm -Wa,-ahlms=$(<:.c=.lst)
LDPATH              =
LDADD               = -lm -lpthread \
                      $(PGO) \
                      $(COVERAGE) \
                      $(PROFILE)
SRC                 = main.c
OBJ                 = $(SRC:.c=.o)
EXE                 = lpslcd



#===--- Merged variables               ---===#
COV_DATA            = $(shell find . -type f -name '*.d' -o -name '*.gcov' -o -name '*.gcda' -o -name '*.gcno' -o -name 'coverage' -o -name 'coverage.info')
LST_DATA            = $(shell find . -type f -name '*.lst')
PRO_DATA            = $(shell find . -type f -name 'gmon.out')
TMP_DATA            = $(shell find . -type f -name '*~')
LOG_DATA            = $(shell find . -type f -name 'lpslcd.dat' -o -name 'lpslcd.stat')
DOC_DATA            = $(shell find . -type d -name 'html')



#===--- Rules                          ---===#
.PHONY: all clean coverage profile doxygen


all: $(EXE)


$(EXE): $(OBJ)
	$(C) $(OBJ) $(LDPATH) $(LDADD) -o $@


.c.o:
	$(C) $(CFLAGS) $(INCLUDES) $< -o $@


clean:
	rm -rf $(OBJ) $(EXE) $(TMP_DATA) $(LST_DATA) $(COV_DATA) $(PRO_DATA) $(LOG_DATA) $(DOC_DATA)


coverage:
	lcov -q -c -f -b . -d . -o coverage.info &&\
	lcov -q -r coverage.info /usr/\* -b . -d . -o coverage.info &&\
	genhtml coverage.info --legend -f -q -o coverage


profile:
	gprof $(EXE) gmon.out -b -Q


doxygen:
	doxygen doxygen.cfg
