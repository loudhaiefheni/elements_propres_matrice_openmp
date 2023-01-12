SLEPSC_DIR=lib/slepsc
PEPSC_DIR=lib/pepsc
include=-I/usr/include/
libs=-L/usr/lib/x86_64-linux-gnu/
flags=-lgsl -lgslcblas -lm
cc=g++

sequentiel: sequentiel.o inverter.o input_andCo.o
			$(cc) -o $@ $(libs) $^ $(flags) 

sequentiel.o: sequentiel.cpp src/inverter.c
			$(cc) $(include) -c $^

inverter.o: src/inverter.c
			$(cc) -o $@ $(include) -c $^

input_andCo.o: src/input_creation_and_iterative_methods.c
			$(cc) -o $@ $(include) -c $^

# test: test.o
# 			$(cc) -o $@ $(libs) test.o $(flags)

# test.o: test.cpp
# 			$(cc) -o $@ $(include) -c $^

