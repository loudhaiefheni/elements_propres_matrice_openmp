#include "src/inverter.h"
#include "src/input_creation_and_iterative_methods.h"
#include "src/algo_prr.h"
#include "src/load_matrix.h"
#include "header.h"
#define LISSAGE_N 10

// https://en.wikipedia.org/wiki/Singular_value_decomposition
// https://www.gnu.org/software/gsl/doc/html/eigen.html#c.gsl_eigen_symm_workspace

// renvoie la moyenne en terme de time to solution des n_exec executions de l'algo
double PPR_lisse(int n_exec, gsl_matrix *A){
	double t_start, t_end;
	double t_moy = 0;
	//Initialisation des tailles n et m (espace de depart et sous espace)
	int n = A->size1;
	int m = ceil(n/M_SIZE_FACTOR);

	double X[n];
	//Initialisation du vecteur x de taille n (1,0,0,...)
	// print_vector_contents(x);
	for(int i = 0; i<n_exec; i++){
		// Lancement de l algorithme sur la matrice lue et le vecteur x
		memset(X, 0.0, n);
		X[0] = 1;
		printf("Lissage %d\n", i + 1); 
		t_start = omp_get_wtime(); 
		algo_PRR(A, X, n, m);
		t_end = omp_get_wtime();
		t_moy += t_end - t_start;
		printf("TEMPS PARALLEL : %lf \n", t_end - t_start);
	}
	return t_moy / n_exec;
	
}

int main(int argc, char * argv[]){
	if (argc == 1)
	{
		printf("Argument nom de fichier manquant\n");
		return 0;
	}

	// Initialisation et lecture de la matrice A depuis un fichier
	gsl_matrix *a;
	a = remplir_matrice(argv[1]);
	// print_vector_contents(a);


	for (int num_thread = 1; num_thread <= 16; num_thread *= 2) {
		omp_set_num_threads(num_thread);
		#pragma omp parallel
		{
			printf("A");
		}
		printf("NOMBRE DE THREAD  : %d\n", omp_get_max_threads());
		printf("time to solution en moyenne de : %lf\n", PPR_lisse(LISSAGE_N, a));
	}

    // Liberation de la memoire
	gsl_matrix_free(a);

	return 0;
}
