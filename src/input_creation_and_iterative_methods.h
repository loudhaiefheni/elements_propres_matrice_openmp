#include <gsl/gsl_cblas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <omp.h>
#include <math.h>
#include <assert.h>


// Calculer la norme d'un vecteur donné
double get_norm(gsl_vector *vector);

// Normaliser un vecteur donné
int normalize_vector(gsl_vector *vector_to_normalize);

// Calculer le produit scalaire de deux vecteurs donnés
double scalar_product(gsl_vector *vector1, gsl_vector *vector2);

// Calculer le produit d'une matrice donnée et d'un vecteur
gsl_vector* matrix_vector_product(gsl_matrix *matrix, gsl_vector *vector);

// Afficher le contenu d'un vecteur donné
void print_vector_contents(gsl_vector *vector);

// Afficher le contenu d'une matrice donnée
void print_matrix_contents(gsl_matrix *matrix);
