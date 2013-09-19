# Source files
SRC =  $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
DEPS = $(SRC:.cc=.d)
EXE = test_runner

GMOCK_DIR ?= ../../gmock-1.6.0

# Compiler options
CXX ?= g++
CXXFLAGS = -Werror -Wall -g -std=c++11
INC = -I ../ -I $(GMOCK_DIR)/include -I $(GMOCK_DIR)/gtest/include
LIB = -L $(GMOCK_DIR) -l gmock -l pthread

all: $(EXE)

test:
	./test_runner

$(EXE): $(OBJ) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LIB)

%.o: %.cc
	$(CXX) $(INC) $(CXXFLAGS) -c $<

%.d: %.cc
	$(CXX) $(INC) $(CXXFLAGS) -MM $< -MF $@
	
clean:
	rm -f $(EXE) $(OBJ) $(DEPS)

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

