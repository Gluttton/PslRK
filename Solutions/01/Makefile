#===--- Common variables               ---===#
CXX                 = g++
INCLUDES            = -I include
OPTIMIZATION       ?= O0



#===--- Executable specified variables ---===#
EXE_CXXFLAGS        = -c \
                      -MMD \
                      -std=c++11 -march=native -mtune=native \
                      -Wall -Wextra \
                      -$(OPTIMIZATION) \
                      -fverbose-asm -Wa,-ahlms=$(<:.cpp=.lst)
EXE_LDPATH          =
EXE_LDADD           =
EXE_SRC             = src/main.cpp
EXE_OBJ             = $(EXE_SRC:.cpp=.o)
EXE_DEP             = $(wildcard $(EXE_SRC:.cpp=.d))
EXE                 = lpslcd



#===--- Testing specified variables    ---===#
TEST_CXXFLAGS       = -c \
                      -MMD \
                      -std=c++11 -march=native -mtune=native \
                      -Wall -Wextra \
                      -$(OPTIMIZATION) -ggdb3 \
                      -fprofile-arcs -ftest-coverage
TEST_LDPATH         =
TEST_LDADD          = -lgcov -lgtest -lgtest_main -lpthread
TEST_SRC            = test/generator.test.cpp \
                      test/validator.test.cpp
TEST_OBJ            = $(TEST_SRC:.cpp=.o)
TEST_DEP            = $(wildcard $(TEST_SRC:.cpp=.d))
TEST                = lpslcd.test



#===--- Merged variables               ---===#
ifeq ($(filter testing, $(MAKECMDGOALS)),)
CXXFLAGS            = $(EXE_CXXFLAGS)
DEP                 = $(EXE_DEP)
else
CXXFLAGS            = $(TEST_CXXFLAGS)
DEP                 = $(TEST_DEP)
endif

OBJ                 = $(EXE_OBJ) $(TEST_OBJ)
COV_DATA            = $(shell find . -type f -name '*.d' -o -name '*.gcov' -o -name '*.gcda' -o -name '*.gcno' -o -name 'coverage' -o -name 'coverage.info')
LST_DATA            = $(shell find . -type f -name '*.lst')
TMP_DATA            = $(shell find . -type f -name '*~')



#===--- Rules                          ---===#
.PHONY: all testing clean coverage


all: $(EXE)


$(EXE): $(EXE_OBJ)
	$(CXX) $(EXE_OBJ) $(EXE_LDPATH) $(EXE_LDADD) -o $@


testing: $(TEST)


$(TEST): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) $(TEST_LDPATH) $(TEST_LDADD) -o $@


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@


clean:
	rm -rf $(OBJ) $(EXE) $(TEST) $(TMP_DATA) $(LST_DATA) $(COV_DATA) $(PRO_DATA) $(LOG_DATA)


coverage:
	lcov -q -c -f -b . -d test -o coverage.info && genhtml coverage.info --legend --demangle-cpp -f -q -o coverage


include $(DEP)
