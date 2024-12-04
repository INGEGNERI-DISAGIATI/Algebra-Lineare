#include <stdio.h>
#include <stdlib.h>


#include "src/algebra.h"
//define
/**
    TODO: documentazione
    (un array contenente gli elementi della colonna selezionata)
*/
int prodottoVettori(int *vettore1, int *vettore2, size_t size);

/**
    TODO: documentazione
    (un array contenente gli elementi della colonna selezionata)
*/
int *prodottoVettoreScalare(int *vettore, size_t size, int scalare);

/**
    TODO: documentazione
    (un array contenente gli elementi della colonna selezionata)
*/
int **prodottoMatrici(int **matrice1, int **matrice2, size_t righe1, size_t colonne1Righe2, size_t colonne2);

/**
    TODO: documentazione
    (un array contenente gli elementi della colonna selezionata)
*/
int **prodottoMatriceScalare(int **matrice, size_t righe, size_t colonne, int scalare);

/**
    TODO: documentazione
    (un array contenente gli elementi della colonna selezionata)
*/
int *estraiColonna(int **matrice, size_t righe, int colonna);




int prodottoVettori(int *vettore1, int *vettore2, size_t righe) {
    int scalare = 0;
    
    for (int i = 0; i < righe; i++) {
        scalare += vettore1[i] * vettore2[i];
    }

    return scalare;
}

int *prodottoVettoreScalare(int *vettore, size_t righe, int scalare) {
    int *vettoreScalare = malloc(righe * sizeof(int));
    
    for (int i = 0; i < righe; i++) {
        vettoreScalare[i] = scalare * vettore[i];
    }

    return vettoreScalare;
}

int **prodottoMatrici(int **matrice1, int **matrice2, size_t righe1, size_t colonne1Righe2, size_t colonne2) {
    int **prodotto = creaMatrice(righe1, colonne2);

    for (int i = 0; i < righe1; i++) {
        for (int j = 0; j < colonne2; j++) {
            for (int k = 0; k < colonne1Righe2; k++) {
                prodotto[i][j] += matrice1[i][k] * matrice2[k][j];
            }
        }
    }

    return prodotto;
}

int **prodottoMatriceScalare(int **matrice, size_t righe, size_t colonne, int scalare) {
    int **prodottoMatrice = creaMatrice(righe, colonne);
    
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            prodottoMatrice[i][j] = scalare * matrice[i][j];
        }
    }

    return prodottoMatrice;
}


int *estraiColonna(int **matrice, size_t righe, int colonna) {
    int *colonnaEstratta = malloc(righe * sizeof(int));
    
    for (int i = 0; i < righe; i++) {
        colonnaEstratta[i] = matrice[i][colonna];
    }

    return colonnaEstratta;
}


int main(void) {
    int vettore[4] = {1, 2, 3, 4};
    int vettore2[4] = {9, 9, 9, 9};

    printf("prodotto vettore per vettore %d\n", prodottoVettori(vettore, vettore2, 4));

    int *v1 = malloc(2 * sizeof(int));
    v1[0] = 10;
    v1[1] = 20;

    int *prodottoVS = prodottoVettoreScalare(v1, 2, 100);
    stampaArray(prodottoVS, 2);

    int mat1[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int mat2[3][5] = {
        {4, 4, 4, 4, 6},
        {6, 2, 1, 6, 7},
        {8, 6, 4, 11, 3}
    };

    int **matrice1 = copiaMatriceStaticaInDinamica((int *)mat1, 2, 3);
    int **matrice2 = copiaMatriceStaticaInDinamica((int *)mat2, 3, 5);

    
    int **prodottoMM = prodottoMatrici(matrice1, matrice2, 2, 3, 5);

    stampaMatrice(prodottoMM, 2, 5);


    int **prodottoMS = prodottoMatriceScalare(matrice1, 2, 3, 10);
    stampaMatrice(prodottoMS, 2, 3);

    return EXIT_SUCCESS;
}

