#include "src/algebra.h"

int main(void) {
    int mat[3][4] = {
        {1,3,1,0},
        {3,9,4,1},
        {2,1,5,0}
    };

    int **matrice = copiaMatriceStaticaInDinamica((int*)mat, 3, 4);

    risolviSistema(matrice, 3, 4);
}
