#include "input_creation_and_iterative_methods.h"

/**
 * @brief Fonction calculant la norme d un vecteur
 * 
 * @param vector Le vecteur dont on souhiate connaitre la norme
 * @return double La norme du vectur
 */
double get_norm(gsl_vector *vector)
{
	// calcul de la norme
	double xi;
	double sum = 0;
	//Parallelisation de la boucle 
	#pragma omp parallel for reduction(+ : sum)
	for (int i = 0; i < vector->size; i++)
	{
//printf("Task dist %d WITH VALUE %d \n", omp_get_thread_num(), i);
		xi = gsl_vector_get(vector, i);
		sum += xi*xi;
	}
	double norm = sqrt(sum);
	return norm;
}
/**
 * @brief Fonction qui permet de normaliser un vecteur
 * 
 * @param vector_to_normalize le vecteur a normaliser
 * @return int retourne 0 si tout c'est passe correctement
 */
int normalize_vector(gsl_vector *vector_to_normalize)
{
	double xi;
	double norm = get_norm(vector_to_normalize);

	//Parallelisation de la boucle 
	#pragma omp parallel for private(xi)
	for (int i = 0; i < vector_to_normalize->size; i++)
	{
// printf("Task dist %d WITH VALUE %d \n", omp_get_thread_num(), i);
		xi = gsl_vector_get(vector_to_normalize, i);
		xi = xi / norm;
		gsl_vector_set(vector_to_normalize, i, xi);
	}

	return 0;
}
/**
 * @brief Fonction calculant le produit scalaire de deux vecteurs
 * 
 * @param vector1 le premier vecteur a multiplier
 * @param vector2 le deuxieme vecteur a multiplier
 * @return double le resultat du produit 
 */
double scalar_product(gsl_vector *vector1, gsl_vector *vector2)
{
	assert(vector1->size == vector2->size);
	double ret_value = 0; 
	#pragma omp parallel for reduction(+ : ret_value)
	for (size_t i = 0; i < vector1->size; i++)
		ret_value += gsl_vector_get(vector1, i) * gsl_vector_get(vector2, i);
	return ret_value;
}

/**
 * @brief Fonction calculant le produit d'une matrice et d'un vecteur
 * 
 * @param matrix la matrice a multiplier
 * @param vector le vecteur a multipplier
 * @return gsl_vector * le vecteur resultat du produit
 */
gsl_vector* matrix_vector_product(gsl_matrix *matrix, gsl_vector *vector)
{
	int row, colomn;
	double result;
	gsl_vector *vector_result = gsl_vector_alloc(matrix->size1);
	
	//Parallelisation de la premiere boucle qui parcourt les lignes de la matrice
	#pragma omp parallel for private(result)
	for(row = 0; row <matrix->size1; row++)
	{
		result = 0;
		for(colomn = 0; colomn < matrix->size2 ; colomn++)
		{
			result += (double)gsl_matrix_get(matrix, row, colomn) * (double)gsl_vector_get(vector,colomn);
		}
		gsl_vector_set(vector_result,row, result);
	}
	return vector_result;
}

/**
 * @brief Fonction permettant d'afficher un vecteur
 * 
 * @param vector Vecteur a afficher
 */
void print_vector_contents(gsl_vector *vector)
{
	size_t i;
	double element;

	for (i = 0; i < vector->size; ++i) {
		element = gsl_vector_get(vector, i);
		printf("%lf ", element);
	}
	printf("\n");
}

/**
 * @brief Fonction permettant d'afficher une matrice
 * 
 * @param matrix 
 */
void print_matrix_contents(gsl_matrix *matrix)
{
	size_t i, j;
	double element;

	for (i = 0; i < matrix->size1; i++) {
		for (j = 0; j < matrix->size2; j++) {
			element = gsl_matrix_get(matrix, i, j);
			printf("%lf ", element);
		}
		printf("\n");
	}
	printf("\n");
}
