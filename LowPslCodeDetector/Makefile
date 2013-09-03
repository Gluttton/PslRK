#===--- Common variables               ---===#
CXX                 = g++
INCLUDES            = -I include
OPTIMIZATION       ?= O0



#===--- Executable specified variables ---===#
EXE_CXXFLAGS        = -c \
                      -MD \
                      -std=c++0x -march=native -m64 -mfpmath=sse,387 -msse4.2 \
                      -Wall -Wextra \
                      -$(OPTIMIZATION) \
                      -fverbose-asm -Wa,-ahlms=$(<:.cpp=.lst)
EXE_LDPATH          =
EXE_LDADD           =
EXE_SRC             = src/main.cpp \
                      src/logger.cpp
EXE_OBJ             = $(EXE_SRC:.cpp=.o)
EXE                 = bark



#===--- Testing specified variables    ---===#
TEST_CXXFLAGS       = -c \
                      -MD \
                      -std=c++0x -march=native -m64 -mfpmath=sse,387 -msse4.2 \
                      -Wall -Wextra \
                      -$(OPTIMIZATION) -ggdb3 \
                      -pg -fprofile-arcs -ftest-coverage \
                      -fverbose-asm -Wa,-ahlms=$(<:.cpp=.lst)
TEST_LDPATH         =
TEST_LDADD          = -pg -lgcov -lgtest -lgtest_main -lgmock -lpthread
TEST_SRC            = test/logger.test.cpp \
                      test/generator.test.cpp \
                      test/validator.test.cpp
TEST_OBJ            = $(TEST_SRC:test.cpp=test.o)
TEST                = bark.test



#===--- Merged variables               ---===#
OBJ                 = $(EXE_OBJ) $(TEST_OBJ)
COV_DATA            = $(shell find . -type f -name '*.d' -o -name '*.gcov' -o -name '*.gcda' -o -name '*.gcno' -o -name 'coverage' -o -name 'coverage.info')
LST_DATA            = $(shell find . -type f -name '*.lst')
PRO_DATA            = $(shell find . -type f -name 'gmon.out')
TMP_DATA            = $(shell find . -type f -name '*~')
LOG_DATA            = $(shell find . -type f -name 'bark.log' -o -name 'bark.dat' -o -name 'bark.stat')



#===--- Rules                          ---===#
all: $(EXE)


$(EXE): $(EXE_OBJ)
	$(CXX) $(EXE_OBJ) $(EXE_LDPATH) $(EXE_LDADD) -o $@


testing: $(TEST)


$(TEST): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) $(TEST_LDPATH) $(TEST_LDADD) -o $@


.cpp.o:
	$(CXX) $(EXE_CXXFLAGS) $(INCLUDES) $< -o $@


.test.cpp.test.o:
	$(CXX) $(TEST_CXXFLAGS) $(INCLUDES) $< -o $@


clean:
	rm -rf $(OBJ) $(EXE) $(TEST) $(TMP_DATA) $(LST_DATA) $(COV_DATA) $(PRO_DATA) $(LOG_DATA)


coverage:
	lcov -q -c -f -b . -d test -o coverage.info && genhtml coverage.info --legend --demangle-cpp -f -q -o coverage


profile:
	gprof $(TEST) gmon.out -b -Q
