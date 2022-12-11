#include "input_creation_and_iterative_methods.h"


int normalise_vector(gsl_vector *vector_to_normalize, int size)
{
    // calcul de la norme
    double xi, sum = 0;
    for (int i = 0; i < size; i++)
    {
        xi = gsl_vector_get(vector_to_normalize, i);
        sum += xi*xi;
    }
    printf("sum : %f\n", sum);
    double norm = sqrt(sum);
    printf("norm : %f\n", norm);
    for (int i = 0; i < size; i++)
    {
        xi = gsl_vector_get(vector_to_normalize, i);
        xi = xi / norm;
        gsl_vector_set(vector_to_normalize, i, xi);
    }

    return 0;
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