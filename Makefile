#gsl_include=-I/usr/include/
#gsl_lib=-L/usr/lib/x86_64-linux-gnu/
gsl_flags=-lgsl -lgslcblas -lm
FLAGS=-Wall
cc=gcc

programme: main.o algo.o matrix.o inverter.o input_andCo.o
			$(cc) $(FLAGS) -o $@ $(gsl_lib) $^ $(gsl_flags) 

main.o: main.c src/inverter.c
			$(cc) $(FLAGS) $(gsl_include) -c $^

algo.o: src/algo_prr.c
			$(cc) $(FLAGS) -o $@ $(gsl_include) -c $^

matrix.o: src/matrix.c
			$(cc) $(FLAGS) -o $@ $(gsl_include) -c $^

inverter.o: src/inverter.c
			$(cc) $(FLAGS) -o $@ $(gsl_include) -c $^

input_andCo.o: src/input_creation_and_iterative_methods.c
			$(cc) $(FLAGS) -o $@ $(gsl_include) -c $^


clean: *.o
	rm *.o 
	rm programme

test: test.o
			$(cc) -o $@ $(gsl_lib) test.o $(gsl_flags)

test.o: test.c
			$(cc) -o $@ $(gsl_include) -c $^




