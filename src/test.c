#include <stdio.h>
#include <stdlib.h>
#include "algebra.h"

//function prototypes

int main(void) {
    size_t ordine = 3;
    
    // Input matrice quadrata
    int matricee[3][3] = {
        {2, 1, 0},
        {0, -1, 0},
        {0, 3, 1}
    };
    
    int **matrice = copiaMatriceStaticaInDinamica((int *)matricee, ordine, ordine);
    stampaMatrice(matrice, ordine, ordine);
    // Calcolo matrice inversa
    Frazione **inversa = matriceInversa(matrice, ordine);
    if (inversa == NULL) {
        printf("Impossibile calcolare la matrice inversa\n");
        // Libera memoria matrice originale
        for (size_t i = 0; i < ordine; i++) {
            free(matrice[i]);
        }
        free(matrice);
        return EXIT_FAILURE;
    }
    
    // Stampa risultato
    printf("\nMatrice inversa:\n");
    for (size_t i = 0; i < ordine; i++) {
        for (size_t j = 0; j < ordine; j++) {
            if (inversa[i][j].denominatore == 1) {
                printf("%d\t", inversa[i][j].numeratore);
            } else {
                printf("%d/%d\t", inversa[i][j].numeratore, inversa[i][j].denominatore);
            }
        }
        printf("\n");
    }
    
    // Libera memoria
    for (size_t i = 0; i < ordine; i++) {
        free(matrice[i]);
        free(inversa[i]);
    }
    free(matrice);
    free(inversa);
    
    return EXIT_SUCCESS;
}
