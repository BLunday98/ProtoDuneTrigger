#Makefile for ADJACENCY c++ programs.

CPPFLAG= -I $(CANVAS_ROOT_IO_INC) \
         -I $(ROOT_INC)

CXXFLAGS=-std=c++14 -Wall -Werror -pedantic
CXX=g++
LDFLAGS=$$(root-config --libs --cflags)


####################################################################################################

INCLUDES := ./include/*
INCLUDE_DIR := -I./include

OBJS := src/AdjacencyAlgorithms.o src/TriggerCandidate.o src/ModuleTrigger.o 
OUTS := $(wildcard */*.o) $(patsubst %.cc, %, $(wildcard */*.cc))

####################################################################################################

#Trigger Candidates
TC_DIR := $(PWD)/src
TC_SRC := $(wildcard  $(TC_DIR)/*.cc)
TC_BIN := $(patsubst  $(TC_DIR)/%.cc,  $(TC_DIR)/%.o,  $(TC_SRC))

#Module Level Trigger
MLT_DIR := $(PWD)/src
MLT_SRC := $(wildcard $(MLT_DIR)/*.cc)
MLT_BIN := $(patsubst $(MLT_DIR)/%.cc, $(MLT_DIR)/%.o, $(MLT_SRC))

#Test 
TEST_DIR := $(PWD)/test
TEST_SRC := $(wildcard $(TEST_DIR)/*.cc)
TEST_BIN := $(patsubst $(TEST_DIR)/%.cc, $(TEST_DIR)/%.o, $(TEST_SRC))

####################################################################################################
tcmlt: $(OBJS) $(TC_BIN) $(MLT_BIN) 

test: $(OBJS) $(TEST_BIN)

all: $(OBJS) $(TC_BIN) $(MLT_BIN) $(TEST_BIN)

AdjacencyAlgorithms.o: AdjacencyAlgorithms.cpp
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

TriggerCandidate.o: TriggerCandidate.cpp
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

ModuleTrigger.o: ModuleTrigger.cpp
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE_DIR) -o $*.o -c $*.cc
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE_DIR) -o $* $(OBJS) $*.o

clean:
	rm -f $(OBJS) $(OUTS) $(TEST_BIN)
