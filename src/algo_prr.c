#include "inverter.h"
#include "input_creation_and_iterative_methods.h"
#include "algo_prr.h"


void algo_PRR(gsl_matrix *a , gsl_vector *x, int n, int m)
{
//// Initialisation des constantes, des vecteurs et des matrices

	int est_precis; //booleen pour la precision de l iteration
	int iteration;
	double xi;
	double precision = 0.01;//precision souhaitee pour les resultats
	double epsilon_i, epsilon_max; //precision des resultats de l iteration
	
	
	gsl_vector *y_k = gsl_vector_alloc(n);
	gsl_vector *y_k_moins_un = gsl_vector_alloc(n);

	gsl_matrix *v_m = gsl_matrix_alloc(n,m);
	
	// tableau de flottants contenant les resultats des produits scalaires sur les vecteurs (y_k et y_k-1) ou (y_k et y_k)
	double c[2*m+1];

	//tabelau de vecteur 
	gsl_matrix *q = gsl_matrix_alloc(n,m);

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

	gsl_vector * vecteur_A_Qi = gsl_vector_alloc(n);
	gsl_vector * vecteur_lambda_Q = gsl_vector_alloc(n);

	//vecteur temporaire pour le calcul de x
	gsl_vector * tmp_vector = gsl_vector_alloc(m);

	

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
printf("print_matrix_contents(f_m);\n");
print_matrix_contents(f_m);
		// Calcul valeurs et vecteurs propres de f_m
		gsl_vector_complex *vecteur_complex_transition = gsl_vector_complex_alloc(m);
		gsl_matrix_complex *vecteurs_propres_complexes = gsl_matrix_complex_alloc(m, m);
		gsl_eigen_nonsymmv_workspace *my_workspace;
		my_workspace = gsl_eigen_nonsymmv_alloc(m);/// a voir si c est pa m au lieu de n
		gsl_eigen_nonsymmv_params(1, my_workspace); // valeur possiblement modifiable
		gsl_eigen_nonsymmv(f_m, vecteur_complex_transition, vecteurs_propres_complexes, my_workspace);
		*valeurs_propres = (gsl_vector_complex_real(vecteur_complex_transition).vector);
		//vecteurs_propres = gsl_matrix_complex_real(V);
		gsl_eigen_nonsymmv_free(my_workspace);

	////Etape 3
	//3. Calculer qi = Vm × ui pour i = 1, . . . m
		
printf("print_vector_contents(valeurs_propres);\n");
print_vector_contents(valeurs_propres);
printf("print_matrix_contents(vecteurs_propres);\n");
print_matrix_contents(vecteurs_propres);
		for(int i = 0; i < m; i++)
		{
			gsl_matrix_complex_get_row(vecteur_complex_transition, vecteurs_propres_complexes, i);
			*vecteur_propre = gsl_vector_complex_real(vecteur_complex_transition).vector;
			gsl_matrix_set_col(q, i, matrix_vector_product(v_m, vecteur_propre));
		}

printf("print_matrix_contents(q);\n");
print_matrix_contents(q);
	////Etape 4
	//4. Si maxi=1,m k(Aqi − λiqi)k ε, alors avec un nouveau vecteur x aller `a l’´etape 1.
		epsilon_max = 0;
		for (int i = 0; i < m ; i++ )
		{
			gsl_matrix_get_col(vecteur_lambda_Q, q, i);
			vecteur_A_Qi = matrix_vector_product(a, vecteur_lambda_Q);
printf("print_vector_contents(vecteur_A_Qi);\n");
print_vector_contents(vecteur_A_Qi);
			printf("Calcul lambda * Qi i:%d\n",i);
printf("print_vector_contents(vecteur_Q);\n");
print_vector_contents(vecteur_lambda_Q);
			gsl_vector_scale(vecteur_lambda_Q, gsl_vector_get(valeurs_propres, i));
printf("print_vector_contents(vecteur_lambda_Q);\n");
print_vector_contents(vecteur_lambda_Q);
			gsl_vector_sub(vecteur_A_Qi, vecteur_lambda_Q);
			epsilon_i = get_norm(vecteur_A_Qi); 
			
			if(epsilon_i > epsilon_max)
			{
				printf("AHAHAHAH : %lf\n", epsilon_i);
				epsilon_max = epsilon_i;
			}
		}
		if(epsilon_max < precision)
		{
			est_precis = 1;
		}

		iteration++;
		//re-calcul de x
		for(int i = 0; i < n; i++)
		{
			gsl_matrix_get_row(tmp_vector, q, i);
			xi = 0;
			for (int j =0; j<m ; j++)
			{
				xi += gsl_vector_get(tmp_vector, j);
			}
			gsl_vector_set(x,i, xi );
		}
print_vector_contents(x);
printf("epsilon max : %f\n", epsilon_max);
printf("est precis : %d\n", est_precis);
printf("iteration : %d\n", iteration);
	}
}
