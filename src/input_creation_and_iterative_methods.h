#include <gsl/gsl_cblas.h>
#include <gsl/gsl_vector.h>

#include <math.h>
#include <assert.h>

int normalize_vector(gsl_vector *vector_to_normalize);
double scalar_product(gsl_vector *vector1, gsl_vector *vector2);
void print_vector_contents(gsl_vector *vector, int n_lig);

