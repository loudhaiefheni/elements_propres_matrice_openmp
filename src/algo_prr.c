#include "inverter.h"
#include "input_creation_and_iterative_methods.h"
#include "algo_prr.h"


void algo_PRR(gsl_matrix *a , gsl_vector *x)
{
//// Initialisation des constantes, des vecteurs et des matrices
	
	int n = 10; //taile de l espace de base (taille de la matrice d entrée)
	int m = 5; //taille du sous espace 
	int est_precis; //booleen pour la precision de l iteration
	int iteration;
	long double precision = 1;//precision souhaitee pour les resultats
	long double epsilon_i; //precision des resultats de l iteration
	
	//vecteur d entree sa normalisation donne le vecteur y_0
	gsl_vector *x = gsl_vector_alloc(m);

	gsl_vector *y_k = gsl_vector_alloc(n);
	gsl_vector *y_k_moins_un = gsl_vector_alloc(n);

	//gsl_vector v_m [m];
	gsl_matrix *v_m = gsl_matrix_alloc(n,m);
	gsl_matrix *a = gsl_matrix_alloc(n,n);
	
	// tableau de flottants contenant les resultats des produits scalaires sur les vecteurs (y_k et y_k-1) ou (y_k et y_k)
	double c[2*m+1];

	//tabelau de vecteur 
	gsl_vector* q[m];

	//matrices contruites a partir du tableau c 
	gsl_matrix *b_m = gsl_matrix_alloc(m,m);
	gsl_matrix *b_m_moins_un = gsl_matrix_alloc(m,m);

	//produit des matrices b_m et e_m
	gsl_matrix *f_m = gsl_matrix_alloc(m,m);
	//inverse de la matrice b_m-1
	gsl_matrix *e_m = gsl_matrix_alloc(m,m);

	//matrice contenant les vecteurs propres et vecteur contenant les valeurs propres
	gsl_matrix * vecteurs_propres = gsl_matrix_alloc(m, m);
	gsl_vector * valeurs_propres = gsl_vector_alloc(m);

	//vecteur contentant un vecteur propre
	gsl_vector * vecteur_propre = gsl_vector_alloc(m);

	gsl_vector *vecteur_A_Qi = gsl_vector_alloc(m);
	gsl_vector *vecteur_lamba_Q = gsl_vector_alloc(m);

	

//// Etape 1 
//1. Calculer C2k−1 = (yk, yk−1), C2k = (yk, yk) où yk = Ayk−1, for k = 1, m.
	iteration = 0;
	est_precis = 0;
	while(!est_precis && iteration < ITERATION_MAX)
	{

		normalize_vector(x);

		y_k_moins_un = x;

		c[0] = scalar_product(y_k_moins_un, y_k_moins_un);

		for(int k = 1 ; k <= m ; k++)
		{
			gsl_matrix_set_col(v_m, k-1, y_k_moins_un);
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
				gsl_matrix_set(b_m, ligne , colonne, c[colonne + ligne + 1]);
			}
		}

	////Etape 2
	//2. Calculer Em = B−1 m−1, Fm = Em * Bm

		e_m = invert_a_matrix(b_m_moins_un, m);
		gsl_blas_dsymm(CblasLeft, CblasUpper, 1, e_m, b_m, 0, f_m);

		// Calcul valeurs et vecteurs propres de f_m
		gsl_eigen_symmv_workspace *my_workspace;
		my_workspace = gsl_eigen_symmv_alloc(n);/// a voir si c est pa m au lieu de n

		gsl_eigen_symmv(f_m, valeurs_propres, vecteurs_propres, my_workspace);
		gsl_eigen_symmv_free(my_workspace);

	////Etape 3
	//3. Calculer qi = Vm × ui pour i = 1, . . . m

		for(int i = 0; i < m; i++)
		{
			gsl_matrix_get_row(vecteur_propre, vecteurs_propres, i);
			q[i] = matrix_vector_product(v_m, vecteur_propre);
			printf("Qi = Vm x Ui\n");
			print_vector_contents(q[i]);
		}

	////Etape 4
	//4. Si maxi=1,m k(Aqi − λiqi)k ε, alors avec un nouveau vecteur x aller `a l’´etape 1.

		est_precis = 1;
		for (int i =0; i < m ; i++ )
		{
			vecteur_A_Qi = matrix_vector_product(a,q[i]);
			vecteur_lamba_Q = q[i];
			gsl_vector_scale(vecteur_lamba_Q, gsl_vector_get(valeurs_propres, i));
			gsl_vector_sub(vecteur_A_Qi, vecteur_lamba_Q);
			epsilon_i = get_norm(vecteur_A_Qi); 
			if(epsilon_i > precision)
			{
				est_precis = 0;
			}
		}
		iteration++;
		//recalcule de x
	}
}