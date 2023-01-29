#include "src/inverter.h"
#include "src/input_creation_and_iterative_methods.h"
#include "src/algo_prr.h"
#include "src/load_matrix.h"
#include "header.h"

// https://en.wikipedia.org/wiki/Singular_value_decomposition
// https://www.gnu.org/software/gsl/doc/html/eigen.html#c.gsl_eigen_symm_workspace

int main(){

	//Initialisation et lecture de la matrice A depuis un fichier
	gsl_matrix *a;
	a = remplir_matrice("test.mtx");
	print_matrix_contents(a);

	//Initialisation des tailles n et m (espace de depart et sous espace)
	int n = a->size1;
	int m = ceil(n/M_SIZE_FACTOR);

	if (m <= 1)
		m = 2;

	//Initialisation du vecteur x de taille n (1,0,0,...)
	double X[n];
	memset(X, 0.0, n);
	X[0] = 1;

	//Lancement de l algorithme sur la matrice lue et le vecteur x
	algo_PRR(a, X, n, m);

	//Liberation de la memoire
	gsl_matrix_free(a);

	return 0;
}
