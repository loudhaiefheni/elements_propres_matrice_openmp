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

void print_vector_contents(gsl_vector *vector, int n_ligne)
{
	int i, j;
	double element;

	for (i = 0; i < n_ligne; ++i) {
		element = gsl_vector_get(vector, i);
		printf("%f ", element);
	}
	printf("\n");
}
