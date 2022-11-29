#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_linalg.h>

gsl_matrix *invert_a_matrix(gsl_matrix *matrix, int size);
void print_mat_contents(gsl_matrix *matrix, int size);
void randomize_mat_contents(gsl_matrix *matrix, int size);
