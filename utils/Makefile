#Makefile for gallery c++ programs.
#Note, being all-incllusive here: you can cut out libraries/includes you do not need
#you can also change the flags if you want too (Werror, pedantic, etc.)

CPPFLAGS=-I $(CANVAS_INC) \
         -I $(CETLIB_INC) \
         -I $(FHICLCPP_INC) \
         -I $(GALLERY_INC) \
         -I $(HEP_CONCURRENCY_INC) \
         -I $(LARCOREOBJ_INC) \
         -I $(LARDATAOBJ_INC) \
         -I $(CETLIB_EXCEPT_INC) \
         -I $(CANVAS_ROOT_IO_INC) \
         -I $(ROOT_INC) \
         -I $(ART_INC)

CXXFLAGS=-std=c++14 -Wall -pedantic
CXX=g++
LDFLAGS=$$(root-config --libs --cflags) \
        -L $(CANVAS_LIB) -l canvas \
        -L $(CETLIB_LIB) -l cetlib \
        -L $(FHICLCPP_LIB) -l fhiclcpp \
        -L $(GALLERY_LIB) -l gallery \
        -L $(LARCOREOBJ_LIB) -l larcoreobj_SummaryData \
        -L $(LARDATAOBJ_LIB) -l lardataobj_Simulation -l lardataobj_RecoBase -l lardataobj_MCBase -l lardataobj_RawData -l lardataobj_OpticalDetectorData -l lardataobj_AnalysisBase

Skim_PDSP: Skim_PDSP.cc
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

all:
	Skim_PDSP

clean:
	rm -rf Skim_PDSP
