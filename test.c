#include "algebra.c"
// #include "old_algebra.c"
#include <stdio.h>
#include <string.h>
//define


//function prototypes





int main(void) {
    // int rigaA[] = {0, 0, 17, 0};
    // int rigaB[] = {1, 8, 32, 9};

    int righe = 3;
    int colonne = 4;
    int mat[3][4] = { // che hit sta matrice!
        {1, 3, 1,  0},
        {3, 9, 4,  1},
        {2, 1, 5,  0}
    };
    int **matrice = copiaMatriceStaticaInDinamica((int *)mat, righe, colonne);

    // combinazioneLineare(rigaA, rigaB, 4);

    // stampaArray(rigaB, 4);
    // puts("");
    // // printf("%d\n", contaZeriPerRigaConsecutivi(rigaA, 4));
    // Tupla *zeri = contaZeri(matrice2, righe, colonne);
    
    // stampaTuple(zeri, righe);

    // qsort(zeri, righe, sizeof(Tupla), compare);

    // stampaTuple(zeri, righe);

    stampaMatrice(matrice, righe, colonne);
    // ordinaRighe(matrice2, righe, colonne);
    eliminazioneDiGauss(matrice, righe, colonne);
    stampaMatrice(matrice, righe, colonne);
    
    eliminazioneDiGaussJordan(matrice, righe, colonne);
    stampaMatrice(matrice, righe, colonne);

    // printf("%d\n", aScala(matrice2, righe, colonne));

    return EXIT_SUCCESS;
}
