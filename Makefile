
gsl_include=-I/usr/include/
gsl_lib=-L/usr/lib/x86_64-linux-gnu/
gsl_flags=-lgsl -lgslcblas -lm
cc=gcc

sequentiel: sequentiel.o inverter.o input_andCo.o
			$(cc) -o $@ $(gsl_lib) $^ $(gsl_flags) 

sequentiel.o: sequentiel.c src/inverter.c
			$(cc) $(gsl_include) -c $^

inverter.o: src/inverter.c
			$(cc) -o $@ $(gsl_include) -c $^

input_andCo.o: src/input_creation_and_iterative_methods.c
			$(cc) -o $@ $(gsl_include) -c $^


clean: *.o
	rm *.o

test: test.o
			$(cc) -o $@ $(gsl_lib) test.o $(gsl_flags)

test.o: test.c
			$(cc) -o $@ $(gsl_include) -c $^




