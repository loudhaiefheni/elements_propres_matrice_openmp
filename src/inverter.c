#include "./inverter.h"

/**
 * @file inverter.c
 * @author bjd2385
 * @brief 
 * Found at https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7
 * 
 */

/* A simple example of inverting a matrix using the gsl */


/************************************************************
 * PROCEDURE: invert_a_matrix
 * 
 * DESCRIPTION: Invert a matrix using GSL.
 *
 * RETURNS:
 *      gsl_matrix pointer
 */
gsl_matrix * invert_a_matrix(gsl_matrix *matrix, int size)
{
    gsl_permutation *p = gsl_permutation_alloc(size);
    int s;

    // Compute the LU decomposition of this matrix
    gsl_linalg_LU_decomp(matrix, p, &s);

    // Compute the  inverse of the LU decomposition
    gsl_matrix *inv = gsl_matrix_alloc(size, size);
    gsl_linalg_LU_invert(matrix, p, inv);

    gsl_permutation_free(p);

    return inv;
}



