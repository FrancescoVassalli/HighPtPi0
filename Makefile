SHELL=/usr/bin/env bash
CXX_COMMON=-O2 -pedantic -W -fPIC -Wpointer-arith -Warray-bounds -Wchar-subscripts -Wmissing-braces -Wnonnull -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wempty-body -Wignored-qualifiers -Wmissing-field-initializers -Wuninitialized -Wunused-parameter -Wshadow
PREFIX_INCLUDE=/phenix/u/vassalli/pythia8230/include
PREFIX_LIB=/phenix/u/vassalli/pythia8230/lib
CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON)
CXX_COMMON+= -L$(PREFIX_LIB) -Wl,-rpath,$(PREFIX_LIB) -lpythia8 -ldl
CXX=g++
HEPMC2_INCLUDE=/direct/phenix+u/vassalli/HEPBuild/include
HEPMC2_LIB=/direct/phenix+u/vassalli/HEPBuild/lib

driver: driver.cc PionPythiaGen.o
		$(CXX) $< PionPythiaGen.o -o driver -std=c++11 -I$(HEPMC2_INCLUDE) $(CXX_COMMON) -\
L$(HEPMC2_LIB) -Wl,-rpath,$(HEPMC2_LIB) -lHepMC `root-config --libs --cflags`

PionPythiaGen.o: $(PREFIX_LIB)/libpythia8.a PionPythiaGen.cc PionPythiaGen.h
		$(CXX) $< -c PionPythiaGen.cc -std=c++11 -I$(HEPMC2_INCLUDE) $(CXX_COMMON) -\
L$(HEPMC2_LIB) -Wl,-rpath,$(HEPMC2_LIB) -lHepMC `root-config --libs --cflags`

clean:
	rm PionPythiaGen.o driver
