#include "src/inverter.h"
#include "sequentiel.hpp"





int main(){
    //1. Calculer C2k−1 = (yk, yk−1), C2k = (yk, yk) o`u yk = Ayk−1, for k = 1, m.
    //Constituer les matrices Bm−1, Bm et Vm.

    //2. Calculer Em = B−1 m−1. 
    // On utilise le code de @author bjd2385 trouvé à https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7
    // j'inverse une matrice 2x2 pour tester voir "matrice 2x2 inversion exemple.png" dans testing
    srand(time(NULL));

    double c0 = 1, c1 = 2, c2 = 3, c3 = 4; 

    int mat_size = 2;

    gsl_matrix *b_m_moins_un = gsl_matrix_alloc(mat_size, mat_size);

    gsl_matrix_set(b_m_moins_un, 0, 0, c0);
    gsl_matrix_set(b_m_moins_un, 0, 1, c1);
    gsl_matrix_set(b_m_moins_un, 1, 0, c1);
    gsl_matrix_set(b_m_moins_un, 1, 1, c2);

    gsl_matrix *b_m = gsl_matrix_alloc(mat_size, mat_size);

    gsl_matrix_set(b_m, 0, 0, c1);
    gsl_matrix_set(b_m, 0, 1, c2);
    gsl_matrix_set(b_m, 1, 0, c2);
    gsl_matrix_set(b_m, 1, 1, c3);

    // fill this matrix with random doubles
    // randomize_mat_contents(mat, mat_size);

    // let's see the original now
    printf("Matrice originale b_m_moins_un :\n");
    print_mat_contents(b_m_moins_un, mat_size);

    

    // compute the matrix inverse
    gsl_matrix *e_m = invert_a_matrix(b_m_moins_un, mat_size);
    printf("Matrice inversée:\n");
    print_mat_contents(e_m, mat_size);

    printf("Matrice originale b_m :\n");
    print_mat_contents(b_m, mat_size);

    gsl_matrix *f_m = gsl_matrix_alloc(mat_size, mat_size);

    gsl_blas_dsymm(CblasLeft, CblasUpper, 1, e_m, b_m, 0, f_m);

    // int gsl_blas_dsymm(CBLAS_SIDE_t Side, CBLAS_UPLO_t Uplo, 1 const gsl_matrix *A, const gsl_matrix *B, 0, gsl_matrix *C)

    printf("Matrice Resultat f_m :\n");
    print_mat_contents(f_m, mat_size);


    //Constituer Fm = Em × Bm.
    // Em est l'inverse d'une matrice symmétrique et est donc aussi symétrique
    // On multiplie donc deux matrices symétrique


    gsl_matrix_free(b_m_moins_un);
    gsl_matrix_free(e_m);
    gsl_matrix_free(b_m);
    gsl_matrix_free(f_m);
    //Calculer les valeurs et vecteurs propres de Fm: (λi, ui) pour i = 1, . . . , m.

    //3. Calculer qi = Vm × ui pour i = 1, . . . m
    //4. Si maxi=1,m k(Aqi − λiqi)k ε, alors avec un nouveau vecteur x aller `a l’´etape 1.

    //
    //
    //
    //



    return 0;
}
