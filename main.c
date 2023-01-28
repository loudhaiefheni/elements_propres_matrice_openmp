#include "src/inverter.h"
#include "src/input_creation_and_iterative_methods.h"
#include "src/algo_prr.h"
#include "src/load_matrix.h"
#include "main.h"

// https://en.wikipedia.org/wiki/Singular_value_decomposition
// https://www.gnu.org/software/gsl/doc/html/eigen.html#c.gsl_eigen_symm_workspace

int main(){

///////////////////////////////////////// Initialisation ///////////////////////////////////////////

//// Lecture des fichiers contenant les matrices et créations des matrices correspondantes

	gsl_matrix *a;
	a = remplir_matrice("test.mtx");
	afficher_matrice(a);

	int n = a->size1;
	int m = (int)0.1*n;

/*
	gsl_matrix *A = gsl_matrix_alloc(n,n);
	for(int r =0; r< n; r++)
	{
		for(int c=0; c<n; c++)
		{
			gsl_matrix_set(A, r, c, (double)r);
		}
	}

*/
	gsl_vector *x = gsl_vector_alloc(n);
	gsl_vector_set_zero(x); 
	gsl_vector_set(x, 0, (double)1);
	print_vector_contents(x);

	algo_PRR(a,x, n, m);

	
    // Clean up
    gsl_matrix_free(a);

	return 0;
}
