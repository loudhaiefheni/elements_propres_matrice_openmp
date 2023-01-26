#include <gsl/gsl_cblas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

#include <math.h>
#include <assert.h>

double get_norm(gsl_vector *vector);
int normalize_vector(gsl_vector *vector_to_normalize);
double scalar_product(gsl_vector *vector1, gsl_vector *vector2);
gsl_vector* matrix_vector_product(gsl_matrix *matrix, gsl_vector *vector);
void print_vector_contents(gsl_vector *vector);
void print_matrix_contents(gsl_matrix *matrix);

