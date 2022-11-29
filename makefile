include=-I/usr/include/
libs=-L/usr/lib/x86_64-linux-gnu/
flags=-lgsl -lgslcblas -lm
cc=g++

sequentiel: sequentiel.o inverter.o
			$(cc) -o $@ $(libs) sequentiel.o inverter.o $(flags) 

sequentiel.o: sequentiel.cpp src/inverter.c
			$(cc) $(include) -c $^

inverter.o: src/inverter.c
			$(cc) -o $@ $(include) -c $^

# test: test.o
# 			$(cc) -o $@ $(libs) test.o $(flags)

# test.o: test.cpp
# 			$(cc) -o $@ $(include) -c $^

