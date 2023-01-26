#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>

gsl_matrix* remplir_matrice(char* file_name);
void afficher_matrice(gsl_matrix *matrix);

#endif