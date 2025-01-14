#include "src/inverter.h"
#include "src/input_creation_and_iterative_methods.h"
#include "sequentiel.h"


void test_SVD(){
	// https://en.wikipedia.org/wiki/Singular_value_decomposition
	// https://www.gnu.org/software/gsl/doc/html/eigen.html#c.gsl_eigen_symm_workspace
	size_t n = 3;
	gsl_eigen_symm_workspace *my_workspace;
	my_workspace = gsl_eigen_symm_alloc(n);

	gsl_matrix *A = gsl_matrix_alloc(n, n);
	gsl_vector *S = gsl_vector_alloc(n);
	gsl_matrix_set(A, 0, 0, 1);
	gsl_matrix_set(A, 0, 1, -5);
	gsl_matrix_set(A, 0, 2, 1);
	gsl_matrix_set(A, 1, 0, 0);
	gsl_matrix_set(A, 1, 1, 2);
	gsl_matrix_set(A, 1, 2, -1);
	gsl_matrix_set(A, 2, 0, 0);
	gsl_matrix_set(A, 2, 1, 0);
	gsl_matrix_set(A, 2, 2, 3);
	print_matrix_contents(A);
	gsl_eigen_symm(A, S, my_workspace);
	gsl_eigen_symm_free(my_workspace);

	print_vector_contents(S);
}


int main(){
	
	int size_x_vector;

	// NORMALISATION
	/*
	size_x_vector = 10;

	gsl_vector *x = gsl_vector_alloc(size_x_vector);

	gsl_vector_set(x, 0, (double)3);
	gsl_vector_set(x, 1, (double)3);
	gsl_vector_set(x, 2, (double)3);
	gsl_vector_set(x, 3, (double)3);
	gsl_vector_set(x, 4, (double)3);
	gsl_vector_set(x, 5, (double)12);
	gsl_vector_set(x, 6, (double)12);
	gsl_vector_set(x, 7, (double)12);
	gsl_vector_set(x, 8, (double)12);
	gsl_vector_set(x, 9, (double)12);

	print_vector_contents(x, size_x_vector);

	normalize_vector(x, size_x_vector);

	print_vector_contents(x, size_x_vector);

	*/
/*
	size_x_vector = 4;

	gsl_vector *x0 = gsl_vector_alloc(size_x_vector);

	gsl_vector_set(x0, 0, (double)3);
	gsl_vector_set(x0, 1, (double)2);
	gsl_vector_set(x0, 2, (double)1);
	gsl_vector_set(x0, 3, (double)0);

	gsl_vector *x1 = gsl_vector_alloc(size_x_vector);

	gsl_vector_set(x1, 0, (double)-5);
	gsl_vector_set(x1, 1, (double)3);
	gsl_vector_set(x1, 2, (double)8);
	gsl_vector_set(x1, 3, (double)12);


	printf("PRODUIT SCALAIRE : %lf\n", scalar_product(x0, x1));
*/

	gsl_matrix *A = gsl_matrix_alloc(3,3);
	gsl_matrix_set(A, 0, 0, 5);
	gsl_matrix_set(A, 0, 1, -8);
	gsl_matrix_set(A, 0, 2, 3);
	gsl_matrix_set(A, 1, 0, -62);
	gsl_matrix_set(A, 1, 1, 45);
	gsl_matrix_set(A, 1, 2, -10);
	gsl_matrix_set(A, 2, 0, 7);
	gsl_matrix_set(A, 2, 1, 1);
	gsl_matrix_set(A, 2, 2, 37);

	gsl_vector *x3 = gsl_vector_alloc(2);

	gsl_vector_set(x3, 0, (double)-5);
	gsl_vector_set(x3, 1, (double)3);

	
	print_matrix_contents(A);
	print_vector_contents(x3);
	print_vector_contents(matrix_vector_product(A,x3));


	//1. Calculer C2k−1 = (yk, yk−1), C2k = (yk, yk) o`u yk = Ayk−1, for k = 1, m.
	//Constituer les matrices Bm−1, Bm et Vm.

	//2. Calculer Em = B−1 m−1.
	// { 
	// // On utilise le code de @author bjd2385 trouvé à https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7
	// // j'inverse une matrice 2x2 pour tester voir "matrice 2x2 inversion exemple.png" dans testing
	// srand(time(NULL));

	// double c0 = 1, c1 = 2, c2 = 3, c3 = 4; 

	// int mat_size = 2;

	// gsl_matrix *b_m_moins_un = gsl_matrix_alloc(mat_size, mat_size);

	// gsl_matrix_set(b_m_moins_un, 0, 0, c0);
	// gsl_matrix_set(b_m_moins_un, 0, 1, c1);
	// gsl_matrix_set(b_m_moins_un, 1, 0, c1);
	// gsl_matrix_set(b_m_moins_un, 1, 1, c2);

	// gsl_matrix *b_m = gsl_matrix_alloc(mat_size, mat_size);

	// gsl_matrix_set(b_m, 0, 0, c1);
	// gsl_matrix_set(b_m, 0, 1, c2);
	// gsl_matrix_set(b_m, 1, 0, c2);
	// gsl_matrix_set(b_m, 1, 1, c3);

	// // fill this matrix with random doubles
	// // randomize_mat_contents(mat, mat_size);

	// // let's see the original now
	// printf("Matrice originale b_m_moins_un :\n");
	// print_mat_contents(b_m_moins_un, mat_size);

	

	// // compute the matrix inverse
	// gsl_matrix *e_m = invert_a_matrix(b_m_moins_un, mat_size);
	// printf("Matrice inversée:\n");
	// print_mat_contents(e_m, mat_size);

	// printf("Matrice originale b_m :\n");
	// print_mat_contents(b_m, mat_size);

	// gsl_matrix *f_m = gsl_matrix_alloc(mat_size, mat_size);

	// gsl_blas_dsymm(CblasLeft, CblasUpper, 1, e_m, b_m, 0, f_m);

	// // int gsl_blas_dsymm(CBLAS_SIDE_t Side, CBLAS_UPLO_t Uplo, 1 const gsl_matrix *A, const gsl_matrix *B, 0, gsl_matrix *C)

	// printf("Matrice Resultat f_m :\n");
	// print_mat_contents(f_m, mat_size);


	// //Constituer Fm = Em × Bm.
	// // Em est l'inverse d'une matrice symmétrique et est donc aussi symétrique
	// // On multiplie donc deux matrices symétrique


	// gsl_matrix_free(b_m_moins_un);
	// gsl_matrix_free(e_m);
	// gsl_matrix_free(b_m);
	// gsl_matrix_free(f_m);
	// //Calculer les valeurs et vecteurs propres de Fm: (λi, ui) pour i = 1, . . . , m.
	//test_SVD();
	 //}

	//3. Calculer qi = Vm × ui pour i = 1, . . . m
	//4. Si maxi=1,m k(Aqi − λiqi)k ε, alors avec un nouveau vecteur x aller `a l’´etape 1.


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// Initialisation ///////////////////////////////////////////

//// Lecture des fichiers contenant les matrices et créations des matrices correspondantes



//// Initialisation des constantes, des vecteurs et des matrices

	int n = 10; //taile de l espace de base (taille de la matrice d entrée)
	int m = 5; //taille du sous espace 
	long double epsilon; //precision des resultats
	
	//vecteur d entree sa normalisation donne le vecteur y_0
	gsl_vector *x = gsl_vector_alloc(m);

	gsl_vector *y_k = gsl_vector_alloc(n);
	gsl_vector *y_k_moins_un = gsl_vector_alloc(n);

	// tableau de vecteurs contenant les vecteur yk  (yk = A*y_(k-1) = A^(k)*y_0 )
	gsl_vector v_m [m];
	// tableau de vecteurs contenant les resultats des produits scalaires sur les vecteurs (y_k et y_k-1) ou (y_k et y_k)
	gsl_vector c[2*m+1];

	//matrices contruites a partir du tableau c 
	gsl_matrix *b_m = gsl_matrix_alloc(m,m);
	gsl_matrix *b_m_moins_un = gsl_matrix_alloc(m,m);

	//produit des matrices b_m et e_m
	gsl_matrix *f_m = gsl_matrix_alloc(m,m);
	//inverse de la matrice b_m-1
	gsl_matrix *e_m = gsl_matrix_alloc(m,m);


	


//// Etape 1 
//1. Calculer C2k−1 = (yk, yk−1), C2k = (yk, yk) où yk = Ayk−1, for k = 1, m.

	normalize_vector(x);

	y_k_moins_un = x;

	c[0] = scalar_product(y_k_moins_un, y_k_moins_un);

	for(int k = 1 ; k <= m ; k++)
	{
		v_m[k-1] = y_k_moins_un;
		y_k = matrix_vector_product(a, y_k_moins_un);
		c[2*k-1] = scalar_product(y_k, y_k_moins_un);
		c[2*k] = scalar_product(y_k, y_k);
		y_k_moins_un = y_k;
	}

	//Constitution des matrices b_m-1, b_m 

	for(int ligne = 0 ; ligne < m ; ligne++)
	{
		for(int colonne = 0; colonne < m; colonne++)
		{
			gsl_matrix_set(b_m_moins_un, ligne, colonne, c[colonne + ligne]);
			gsl_matrix_set(b_m,ligne , colonne, c[colonne + ligne + 1]);
		}
	}

////Etape 2
//2. Calculer Em = B−1 m−1, Fm = Em * Bm

	e_m = invert_a_matrix(b_m_moins_un, m);
	gsl_blas_dsymm(CblasLeft, CblasUpper, 1, e_m, b_m, 0, f_m);

	// Calcul valeurs et vecteurs propres de f_m

	gsl_eigen_symm_workspace *my_workspace;
	my_workspace = gsl_eigen_symm_alloc(n);

	gsl_eigen_symm(A, S, my_workspace);
	gsl_eigen_symm_free(my_workspace);




//3. Calculer qi = Vm × ui pour i = 1, . . . m


//4. Si maxi=1,m k(Aqi − λiqi)k ε, alors avec un nouveau vecteur x aller `a l’´etape 1.

















	return 0;
}
