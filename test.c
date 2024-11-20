#include "algebra.h"
#include <stdio.h>
#include <string.h>
//define


//function prototypes





int main(void) {
    
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
    

    /*
    int mat[4][5] = {
        {0,  3, -4,  1, 1},
        {1, -1, -1,  1, 0},
        {2, -2, -2,  2, 0},
        {1, -1,  4, -1, 1}
    };
    righe = 4;
    colonne = 5;
    int **matrice = copiaMatriceStaticaInDinamica((int *)mat, righe, colonne);

    */

    printf("Matrice inserita:\n");
    stampaMatrice(matrice, righe, colonne);

    // eliminazioneDiGauss(matrice, righe, colonne);
    // eliminazioneDiGaussJordan(matrice, righe, colonne);
    // risolviSistema(matrice, righe, colonne);

    printf("determinante del piccione di tua mamma: %d", determinante(matrice, righe));

    //printf("Matrice dopo l'eliminazione di Gauss:\n");
    // stampaMatrice(matrice, righe, colonne);

    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    free(matrice);

    return EXIT_SUCCESS;
}
