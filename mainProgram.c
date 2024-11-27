#include <stdio.h>
#include "algebra.h"
//define


//function prototypes
int **inserisciMatriceNM(size_t *righe, size_t *colonne);
int **inserisciMatriceNN(size_t *ordine);


int **inserisciMatriceNM(size_t *righe, size_t *colonne) {
    int **matrice;
    
    // Input dimensioni matrice
    printf("Inserisci il numero di righe: ");
    scanf("%zu", righe);
    printf("Inserisci il numero di colonne: ");
    scanf("%zu", colonne);
    
    // Allocazione memoria per le righe
    matrice = (int **)malloc(*righe * sizeof(int *));
    if (matrice == NULL) {
        printf("Errore nell'allocazione della memoria\n");
        return NULL;
    }
    
    // Allocazione memoria per le colonne
    for (size_t i = 0; i < *righe; i++) {
        matrice[i] = (int *)malloc(*colonne * sizeof(int));
        if (matrice[i] == NULL) {
            printf("Errore nell'allocazione della memoria\n");
            // Libera la memoria già allocata
            for (size_t j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            return NULL;
        }
    }
    
    // Input valori matrice
    printf("Inserisci i valori della matrice:\n");
    for (size_t i = 0; i < *righe; i++) {
        for (size_t j = 0; j < *colonne; j++) {
            printf("Elemento [%zu][%zu]: ", i, j);
            scanf("%d", &matrice[i][j]);
        }
    }
    
    return matrice;
}

int **inserisciMatriceNN(size_t *ordine) {
    int **matrice;
    
    // Input dimensione matrice
    printf("Inserisci l'ordine della matrice quadrata: ");
    scanf("%zu", ordine);
    
    // Allocazione memoria per le righe
    matrice = (int **)malloc(*ordine * sizeof(int *));
    if (matrice == NULL) {
        printf("Errore nell'allocazione della memoria\n");
        return NULL;
    }
    
    // Allocazione memoria per le colonne
    for (size_t i = 0; i < *ordine; i++) {
        matrice[i] = (int *)malloc(*ordine * sizeof(int));
        if (matrice[i] == NULL) {
            printf("Errore nell'allocazione della memoria\n");
            // Libera la memoria già allocata
            for (size_t j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            return NULL;
        }
    }
    
    // Input valori matrice
    printf("Inserisci i valori della matrice:\n");
    for (size_t i = 0; i < *ordine; i++) {
        for (size_t j = 0; j < *ordine; j++) {
            printf("Elemento [%zu][%zu]: ", i, j);
            scanf("%d", &matrice[i][j]);
        }
    }
    
    return matrice;
}

int main(void) {
    
    int r1 = 0;
    do {
        puts("0) ESCI.");
        puts("1) matrice n * m [inserisci il vettore dei termini noti come ultima colonna]");
        puts("2) matrice n * n [non inserire il vettore dei termini noti ]");
        puts("");
        printf("Cosa vuoi calcolare? ");
        scanf("%d", &r1);

        switch(r1) {
            case 0: 
                puts("Uscita...");
                break;
            
            case 1 : {
                int r2 = 0;
                size_t righe;
                size_t colonne;
                int **matrice = inserisciMatriceNM(&righe, &colonne);

                
                do {    
                    puts("0) <--- BACK");
                    puts("1) Trova Soluzioni");
                    puts("2) Stampa Matrice");
                    puts("");
                    printf("Cosa vuoi calcolare? ");
                    scanf("%d", &r2);

                    switch(r2) {
                        case 0:
                            break;
                        case 1: 
                            risolviSistema(matrice, righe, colonne);
                            break;
                        case 2:
                            eliminazioneDiGauss(matrice, righe, colonne);
                            stampaMatrice(matrice, righe, colonne);
                            break;

                        default: puts("ERRORE: inserisci una scelta valida (da 0 a 2)");

                    }

                } while (r2 != 0);
                break;
            }

            case 2: {
                int r2 = 0;
                size_t ordine;
                
                int **matrice = inserisciMatriceNN(&ordine);

                
                do {    
                    puts("0) <--- BACK");
                    puts("1) Determinante tramite Laplace");
                    puts("2) Determinante tramite Sarrus [richiede matrice di ordine 3]");
                    puts("3) Determinante tramite Gauss");
                    puts("4) Eliminazione a scala tramite Gauss");
                    puts("5) Eliminazione a scala tramite Gauss-Jordan");
                    puts("");
                    printf("Cosa vuoi calcolare? ");
                    scanf("%d", &r2);

                    switch(r2) {
                        case 0:
                            break;

                        case 1: 
                            printf("Determinante (Laplace): %d\n", laPlace(matrice, ordine));
                            break;

                        case 2:
                            if(ordine != 3) {
                                puts("INSERISCI MATRICE 3 * 3");
                                break;
                            }
                            printf("Determinante (Sarrus): %d\n", sarrus(matrice, ordine));
                            
                            break;

                        case 3:
                            printf("Determinante (El. Gauss): %d\n" ,determinante(matrice, ordine));
                            break;

                        case 4:
                            eliminazioneDiGauss(matrice, ordine, ordine);
                            stampaMatrice(matrice, ordine, ordine);
                            break;

                        case 5:
                            eliminazioneDiGauss(matrice, ordine, ordine);
                            eliminazioneDiGaussJordan(matrice, ordine, ordine);
                            stampaMatrice(matrice, ordine, ordine);
                            break;
                        default: puts("ERRORE: inserisci una scelta valida (da 0 a 1)");

                    }

                } while (r2 != 0);
                break;
            }
        }

    } while (r1 != 0);

    return EXIT_SUCCESS;
}