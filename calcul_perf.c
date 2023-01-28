#include "src/inverter.h"
#include "src/input_creation_and_iterative_methods.h"
#include "src/algo_prr.h"
#include "src/load_matrix.h"
#include "header.h"

// https://en.wikipedia.org/wiki/Singular_value_decomposition
// https://www.gnu.org/software/gsl/doc/html/eigen.html#c.gsl_eigen_symm_workspace

// renvoie la moyenne en terme de time to solution des n_exec executions de l'algo
double PPR_lisse(int n_exec, gsl_matrix *A){
	double t_start, t_end;
	double t_moy = 0;
	//Initialisation des tailles n et m (espace de depart et sous espace)
	int n = A->size1;
	int m = (int)(n/10);

	//Initialisation du vecteur x de taille n (1,0,0,...)
	// print_vector_contents(x);
	for(int i = 0; i<n_exec; i++){
		// Lancement de l algorithme sur la matrice lue et le vecteur x
		gsl_vector *x = gsl_vector_alloc(n);
		gsl_vector_set_zero(x);
		gsl_vector_set(x, 0, (double)1);
		printf("Lissage %d\n", i + 1); 
		t_start = omp_get_wtime(); 
		algo_PRR(A, x, n, m);
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



	//omp_set_num_threads(1);
	//printf("NOMBRE DE THREAD %d\n", omp_get_max_threads());
	
	PPR_lisse(5, a);

    // Liberation de la memoire
	gsl_matrix_free(a);

	return 0;
}
