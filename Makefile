cc=g++

PETSC_DIR=/home/ahenches/Documents/isty/projets/elements_propres_matrice_openmp/lib/petsc

INCLUDE=-I$(PETSC_DIR)/include -I$(PETSC_DIR)/$(PETSC_ARCH)/include 

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules
all: simple 

simple: simple.cpp
	g++ $(INCLUDE) simple.cpp -o simple

