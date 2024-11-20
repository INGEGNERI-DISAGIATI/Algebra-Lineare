#include "algebra.h"
#include <stdio.h>
#include <string.h>
//define


//function prototypes





int main(void) {
    // int rigaA[] = {0, 0, 17, 0};
    // int rigaB[] = {1, 8, 32, 9};

    // int righe = 3;
    // int colonne = 4;
    // int mat[3][4] = { // che hit sta matrice!
    //     {2, 4, -2,  4},
    //     {1, 2, 1,  3},
    //     {3, 6, -3,  6}
    // };
    // int **matrice = copiaMatriceStaticaInDinamica((int *)mat, righe, colonne);


    // stampaMatrice(matrice, righe, colonne);
    // // ordinaRighe(matrice2, righe, colonne);
    // eliminazioneDiGauss(matrice, righe, colonne);
    // stampaMatrice(matrice, righe, colonne);

    // // printf("%d\n", aScala(matrice2, righe, colonne));
    int righe, colonne;

    printf("Inserisci il numero di righe: ");
    scanf("%d", &righe);
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &colonne);

    int **matrice = (int **)malloc(righe * sizeof(int *));
    for (int i = 0; i < righe; i++) {
        matrice[i] = (int *)malloc(colonne * sizeof(int));
    }

    printf("Inserisci gli elementi della matrice:\n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &matrice[i][j]);
        }
    }

    printf("Matrice inserita:\n");
    stampaMatrice(matrice, righe, colonne);

    eliminazioneDiGauss(matrice, righe, colonne);
    eliminazioneDiGaussJordan(matrice, righe, colonne);

    printf("Matrice dopo l'eliminazione di Gauss:\n");
    stampaMatrice(matrice, righe, colonne);

    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    free(matrice);

    return EXIT_SUCCESS;
}
