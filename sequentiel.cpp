#include "src/inverter.h"
#include "sequentiel.hpp"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>




int main(){
    //1. Calculer C2k−1 = (yk, yk−1), C2k = (yk, yk) o`u yk = Ayk−1, for k = 1, m.
    //Constituer les matrices Bm−1, Bm et Vm.

    //2. Calculer Em = B−1 m−1. 
    // On utilise le code de @author bjd2385 trouvé à https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7
    // j'inverse une matrice 2x2 pour tester voir "matrice 2x2 inversion exemple.png" dans testing
    srand(time(NULL));
    int mat_size = 2;

    gsl_matrix *mat = gsl_matrix_alloc(mat_size, mat_size);

    // 
    gsl_matrix_set(mat, 0, 0, 1);
    gsl_matrix_set(mat, 0, 1, 2);
    gsl_matrix_set(mat, 1, 0, 3);
    gsl_matrix_set(mat, 1, 1, 4);

    // fill this matrix with random doubles
    // randomize_mat_contents(mat, mat_size);

    // let's see the original now
    printf("Original matrix:\n");
    print_mat_contents(mat, mat_size);

    // compute the matrix inverse
    gsl_matrix *inverse = invert_a_matrix(mat, mat_size);
    printf("Inverted matrix:\n");
    print_mat_contents(inverse, mat_size);

    gsl_matrix_free(mat);
    gsl_matrix_free(inverse);


    //Constituer Fm = Em × Bm.
    //Calculer les valeurs et vecteurs propres de Fm: (λi, ui) pour i = 1, . . . , m.

    //3. Calculer qi = Vm × ui pour i = 1, . . . m
    //4. Si maxi=1,m k(Aqi − λiqi)k ε, alors avec un nouveau vecteur x aller `a l’´etape 1.

    //
    //
    //
    //



    return 0;
}
