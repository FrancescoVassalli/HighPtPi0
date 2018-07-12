CC=g++
CPPFLAGS=-O2 -ansi -W -fPIC
ROOTINCLUDE=`root-config --libs --cflags`
PYTHIA8INCLUDE=-I/home/user/pythia8226/include
PYTHIA8LIB=-rpath,/home/user/pythia8226/lib
HEPINCLUDE=-I/home/user/HEPBuild/include/
HEPLIB=-rpath,/home/user/HEPBuild/lib/HepMC
ARCHIVE=/home/user/pythia8226/lib/libpythia8.a
driver: driver.o PionPythiaGen.o 
	$(CC) driver.o PionPythiaGen.o -o mainPionGenerator
PionPythiaGen.o: PionPythiaGen.cc PionPythiaGen.h
	$(CC) $(CPPFLAGS) -c PionPythiaGen.o $(ARCHIVE) $(ROOTINCLUDE) $(PYTHIA8INCLUDE) $(HEPINCLUDE) -Wl,$(PYTHIA8LIB),$(HEPLIB) -ldl 
driver.o: driver.cc
	$(CC) $(CPPFLAGS) -c driver.cc
clean:
	rm *.o mainPionGenerator

