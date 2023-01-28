#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_spmatrix.h>

gsl_matrix* remplir_matrice(char* file_name);
gsl_spmatrix* charger_matrice(char *nom_fichier);

#endif
