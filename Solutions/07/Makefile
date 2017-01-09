CXX                 = g++
OPTIMIZATION       ?= O3
CXXFLAGS            = -c \
                      -std=c++14 -march=native -mtune=native \
                      -Wall -Wextra \
                      -$(OPTIMIZATION) \
                      -fverbose-asm -Wa,-ahlms=$(<:.cpp=.lst)
SRC                 = main.cpp
OBJ                 = $(SRC:.cpp=.o)
EXE                 = lpslcd
LST_DATA            = $(shell find . -type f -name '*.lst')
TMP_DATA            = $(shell find . -type f -name '*~')


all: $(EXE)


$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(EXE) $(TMP_DATA) $(LST_DATA)

