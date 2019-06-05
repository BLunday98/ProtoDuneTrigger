#Makefile for ADJACENCY c++ programs.

CPPFLAG= -I $(CANVAS_ROOT_IO_INC) \
         -I $(ROOT_INC)

CXXFLAGS=-std=c++14 -Wall -Werror -pedantic
CXX=g++
LDFLAGS=$$(root-config --libs --cflags)

AdjacencyAlgorithms.o: AdjacencyAlgorithms.cpp
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

TriggerCandidate.o: TriggerCandidate.cpp
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

ModuleTrigger.o: ModuleTrigger.cpp
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

OBJS := src/AdjacencyAlgorithms.o src/TriggerCandidate.o src/ModuleTrigger.o 
OUTS := $(wildcard src/*.o) $(patsubst %.cc, %, $(wildcard src/*.cc))

%.o: %.cc
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -o $*.o -c $*.cc
	$(CXX) $(CPPFLAG) $(CXXFLAGS) $(LDFLAGS) -o $* $(OBJS) $*.o

#Trigger Candidates
TC_DIR := $(PWD)/src
TC_SRC := $(wildcard  $(TC_DIR)/*.cc)
TC_BIN := $(patsubst  $(TC_DIR)/%.cc,  $(TC_DIR)/%.o,  $(TC_SRC))

#Module Level Trigger
MLT_DIR := $(PWD)/src
MLT_SRC := $(wildcard $(MLT_DIR)/*.cc)
MLT_BIN := $(patsubst $(MLT_DIR)/%.cc, $(MLT_DIR)/%.o, $(MLT_SRC))

all: $(OBJS) $(TC_BIN) $(MLT_BIN)

clean:
	rm -f $(OBJS) $(OUTS)
