#include <stdio.h>
#include <stdlib.h>

/**
 * @brief goofy ass POW [credit: Mr. Maio]
 *
 * funzione alternativa di pow per interi 
 *
 * @param base numero da elevare
 * @param exp esponente
 * @return Int
 */
int gPow(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    int p = base;
    for (int i = 1; i < exp; i++) {
        p *= base;
    }

    return p;
}

/**
 * @brief Riduce la matrice eliminando la riga i e la colonna j
 *
 * Risolve a scala il sistema utilizzando la risoluzione verso il basso e verso l'alto
 *
 * @param matrice matrice di interi
 * @param ordine ordine della matrice
 * @param dRiga riga da rimuovere
 * @param dColonna colonna da rimuovere
 * @return Int** [matrice di interi]
 */
int **riduciMatrice(int **matrice, size_t ordine, int dRiga, int dColonna) {
    int **matRidotta = calloc(ordine - 1, sizeof(int *));
    for (int i = 0; i < ordine - 1; i++) {
        matRidotta[i] = calloc(ordine - 1, sizeof(int));
    }

    int iR = 0;
    int jR = 0;
    for (int i = 0; i < ordine; i++) {
        if (i != dRiga) {
            for (int j = 0; j < ordine; j++) {
                if(j == dColonna) {
                    continue;
                    
                }
                matRidotta[iR % (ordine - 1)][jR % (ordine - 1)] = matrice[i][j];
                jR++;
            }
            iR++;
        }
    }
    return matRidotta;
}

/**
 * @brief Determinante calcolato con la regola di Sarrus
 *
 * Calcola il determinante di una matrice 3 * 3 con il metodo di sarrus.
 *
 * @param matrice matrice di interi
 * @param ordine ordine della matrice
 * @return Int
 */
int sarrus(int **matrice, size_t ordine) {
    if(ordine != 3) {
        puts("Ordine DIVERSO da 3 [verrà ritornato -1]");
        return -1;
    }

    int diagonaliPrincipali = (matrice[0][0] * matrice[1][1] * matrice[2][2]) + (matrice[0][1] * matrice[1][2] * matrice[2][0]) + 
    (matrice[0][2] * matrice[1][0] * matrice[2][1]);
    
    int diagonaliInverse = ((matrice[0][2] * matrice[1][1] * matrice[2][0]) + (matrice[0][0] * matrice[1][2] * matrice[2][1]) + 
    (matrice[0][1] * matrice[1][0] * matrice[2][2]));

    return diagonaliPrincipali - diagonaliInverse;
}

/**
 * @brief Determinante calcolato tramite il metodo di Laplace
 *
 * Funzione ricorsiva che come base-case ha:
 *   - ORDINE: 1 -> il determinante è l'elemento della matrice
 *   - ORDINE: 2 -> il determinante viene utilizzata la regola del determinante di matrice di ordine 2
 *   - ORDINE: 3 -> il determinante viene calcolato tramite la regola di Sarrus.
 *
 * In caso l'ordine sia maggiore di 3, viene utilizzato il metodo di Laplace.
 *
 * @param matrice matrice di interi
 * @param ordine ordine della matrice
 * @return Int
 */
int laPlace(int **matrice, size_t ordine) {
    int det = 0;

    if (ordine == 1) {
        return matrice[0][0];
    }
    if (ordine == 2) {
        return (matrice[0][0] * matrice[1][1]) - (matrice[0][1] * matrice[1][0]);
    }
    if (ordine == 3) {
        return sarrus(matrice, ordine);
    } 
    else {
        for(int i = 0; i < ordine; i++) {
            det += matrice[i][0] * gPow(-1, (i +2)) * laPlace(riduciMatrice(matrice, ordine, i, 0), ordine - 1);
        }
    }
    return det;
}


int main(void) {
    int **matrice;
    int ordine;
    
    // Input dimensione matrice
    printf("Inserisci l'ordine della matrice quadrata: ");
    scanf("%d", &ordine);
    
    // Allocazione memoria per le righe
    matrice = (int **)malloc(ordine * sizeof(int *));
    if (matrice == NULL) {
        printf("Errore nell'allocazione della memoria\n");
        return 1;
    }
    
    // Allocazione memoria per le colonne
    for (int i = 0; i < ordine; i++) {
        matrice[i] = (int *)malloc(ordine * sizeof(int));
        if (matrice[i] == NULL) {
            printf("Errore nell'allocazione della memoria\n");
            // Libera la memoria già allocata
            for (int j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            return 1;
        }
    }
    
    // Input valori matrice
    printf("Inserisci i valori della matrice:\n");
    for (int i = 0; i < ordine; i++) {
        for (int j = 0; j < ordine; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &matrice[i][j]);
        }
    }
    
    // Calcolo determinante
    // int determinante = laPlace(matrice, ordine);
    // int **matriceR = riduciMatrice(matrice, ordine, 0, 0);
    // int determinante = laPlace(matrice, ordine);
    int determinante1 = sarrus(matrice, ordine);
    // printf("Il determinante della matrice è: %d\n", determinante);
    printf("Il determinante della matrice con sarrus è: %d\n", determinante1);
    // for(int i = 0; i < ordine - 1; i++) {
    //     for(int j = 0; j < ordine - 1; j++) {
    //         printf("%d ", matriceR[i][j]);
    //     }
    //     puts("");
    // }



    // Liberazione memoria
    for (int i = 0; i < ordine; i++) {
        free(matrice[i]);
    }
    free(matrice);
    
    return 0;
}