#include "algebra.c"
// #include "old_algebra.c"
#include <stdio.h>
#include <string.h>
//define


//function prototypes





int main(void) {
    int rigaA[] = {0, 0, 17, 0};
    int rigaB[] = {1, 8, 32, 9};

    int righe = 3;
    int colonne = 4;
    int matrice[3][4] = {
        {6, 3, 2, 1},
        {0, 0, 2, 0},
        {0, 5, 9, 8}
    };
    int **matrice2 = copiaMatriceStaticaInDinamica((int *)matrice, righe, colonne);

    // combinazioneLineare(rigaA, rigaB, 4);

    // stampaArray(rigaB, 4);
    // puts("");

    // // printf("%d\n", contaZeriPerRigaConsecutivi(rigaA, 4));
    // Tupla *zeri = contaZeri(matrice2, righe, colonne);
    
    // stampaTuple(zeri, righe);

    // qsort(zeri, righe, sizeof(Tupla), compare);

    // stampaTuple(zeri, righe);

    stampaMatrice(matrice2, righe, colonne);
    ordinaRighe(matrice2, righe, colonne);
    stampaMatrice(matrice2, righe, colonne);

    return EXIT_SUCCESS;
}