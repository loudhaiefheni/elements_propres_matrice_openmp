#include "input_creation_and_iterative_methods.h"


int normalize_vector(gsl_vector *vector_to_normalize)
{
	// calcul de la norme
	double xi, sum = 0;
	for (int i = 0; i < vector_to_normalize->size; i++)
	{
		xi = gsl_vector_get(vector_to_normalize, i);
		sum += xi*xi;
	}
	printf("sum : %f\n", sum);
	double norm = sqrt(sum);
	printf("norm : %f\n", norm);
	for (int i = 0; i < vector_to_normalize->size; i++)
	{
		xi = gsl_vector_get(vector_to_normalize, i);
		xi = xi / norm;
		gsl_vector_set(vector_to_normalize, i, xi);
	}

	return 0;
}

double scalar_product(gsl_vector *vector1, gsl_vector *vector2)
{
	assert(vector1->size == vector2->size);
	double ret_value;
	for (size_t i = 0; i < vector1->size; i++)
		ret_value += gsl_vector_get(vector1, i) * gsl_vector_get(vector2, i);
	return ret_value;
}

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
