#include "src/inverter.h"
#include "src/input_creation_and_iterative_methods.h"
#include "src/algo_prr.h"
#include "src/load_matrix.h"
#include "main.h"

// https://en.wikipedia.org/wiki/Singular_value_decomposition
// https://www.gnu.org/software/gsl/doc/html/eigen.html#c.gsl_eigen_symm_workspace

int main(){

	//Initialisation et lecture de la matrice A depuis un fichier
	gsl_matrix *a;
	a = remplir_matrice("test.mtx");
	afficher_matrice(a);

	//Initialisation des tailles n et m (espace de depart et sous espace)
	int n = a->size1;
	int m = (int)(n/10);

	//Initialisation du vecteur x de taille n (1,0,0,...)
	gsl_vector *x = gsl_vector_alloc(n);
	gsl_vector_set_zero(x); 
	gsl_vector_set(x, 0, (double)1);
	print_vector_contents(x);

	//Lancement de l algorithme sur la matrice lue et le vecteur x
	algo_PRR(a,x, n, m);

    //Liberation de la memoire
    gsl_matrix_free(a);

	return 0;
}
