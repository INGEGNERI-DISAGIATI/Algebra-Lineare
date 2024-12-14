#include <stdio.h>
#include "algebra.h"
//define


//function prototypes


int main(void) {
    
    int r1 = 0;
    do {
        puts("0) ESCI.");
        puts("1) Matrice n * m [inserisci il vettore dei termini noti come ultima colonna]");
        puts("2) Matrice n * n [non inserire il vettore dei termini noti ]");
        puts("3) Operazioni tra matrici / vettori");
        puts("");
        printf("Cosa vuoi calcolare? ");
        scanf("%d", &r1);

        switch (r1) {
            case 0: 
                puts("Uscita...");
                break;
            
            case 1 : {
                int r2 = 0;
                size_t righe = 0;
                size_t colonne = 0;
                int **matrice = inserisciMatriceNM(&righe, &colonne);

                
                do {    
                    puts("0) <--- BACK");
                    puts("1) Trova Soluzioni");
                    puts("2) Stampa Matrice");
                    puts("");
                    printf("Cosa vuoi calcolare? ");
                    scanf("%d", &r2);

                    switch (r2) {
                        case 0:
                            break;
                        case 1: 
                            risolviSistema(matrice, righe, colonne);
                            break;
                        case 2: {
                                int **copiaMatrice = copiaMatriceDinamica(matrice, righe, colonne);

                                eliminazioneDiGauss(matrice, righe, colonne);
                                stampaMatrice(matrice, righe, colonne);

                                cancellaMatrice(copiaMatrice, righe);
                            }
                            break;

                        default: puts("ERRORE: inserisci una scelta valida (da 0 a 2)");

                    }

                } while (r2 != 0);
                cancellaMatrice(matrice, righe);
                break;
            }

            case 2: {
                int r2 = 0;
                size_t ordine = 0;
                
                int **matrice = inserisciMatriceNN(&ordine);

                do {    
                    puts("0) <--- BACK");
                    puts("1) Determinante tramite Laplace");
                    puts("2) Determinante tramite Sarrus [richiede matrice di ordine 3]");
                    puts("3) Determinante tramite Gauss");
                    puts("4) Eliminazione a scala tramite Gauss");
                    puts("5) Eliminazione a scala tramite Gauss-Jordan");
                    puts("6) Calcola la Matrice inversa");
                    puts("");
                    printf("Cosa vuoi calcolare? ");
                    scanf("%d", &r2);

                    switch (r2) {
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

                        case 4: {
                                int **copiaMatrice = copiaMatriceDinamica(matrice, ordine, ordine);
                                eliminazioneDiGauss(copiaMatrice, ordine, ordine);
                                stampaMatrice(copiaMatrice, ordine, ordine);

                                cancellaMatrice(copiaMatrice, ordine);
                            }
                            break;

                        case 5: {
                                int **copiaMatrice = copiaMatriceDinamica(matrice, ordine, ordine);
                                eliminazioneDiGauss(copiaMatrice, ordine, ordine);
                                eliminazioneDiGaussJordan(copiaMatrice, ordine, ordine);
                                stampaMatrice(copiaMatrice, ordine, ordine);

                                cancellaMatrice(copiaMatrice, ordine);
                            }
                            break;

                        case 6 : {
                                Frazione **inversa = matriceInversa(matrice, ordine);
                                stampaMatriceDiFrazioni(inversa, ordine, ordine);
                                cancellaMatrice_f(inversa, ordine);

                            }
                            break;

                        default: puts("ERRORE: inserisci una scelta valida (da 0 a 1)");

                    }

                } while (r2 != 0);
                cancellaMatrice(matrice, ordine);
                break;
            }

            case 3: {
                
                int r2 = 0;

                do {
                    puts("0) <--- BACK");
                    puts("1) Prodotto tra Vettori");
                    puts("2) Prodotto Vettore per Scalare");
                    puts("3) Prodotto Matrice per Vettore"); //TODO:
                    puts("4) Prodotto Tra Matrici");
                    puts("5) Prodotto Matrice per Scalare");
                    puts("");
                    printf("Cosa vuoi calcolare? ");
                    scanf("%d", &r2);

                    switch (r2) {
                        case 0:
                                puts("Uscita...");
                            break;

                        case 1: {
                                size_t componenti1 = 0;
                                size_t componenti2 = 0;

                                int *vettore1 = inserisciVettore(&componenti1);
                                int *vettore2 = inserisciVettore(&componenti2);

                                if (componenti1 != componenti2) {
                                    puts("ERRORE: Il numero di componenti dei 2 vettori deve essere uguale");
                                    return EXIT_FAILURE;
                                }
                                int prodottoV = prodottoVettori(vettore1, vettore2, componenti1);

                                printf("Il risultato del prodotto tra i 2 vettori è: %d\n", prodottoV);

                                cancellaVettoreRiga(vettore1);
                                cancellaVettoreRiga(vettore2);
                            }
                            break;

                        case 2: {
                                size_t componenti = 0;
                                int scalare = 0;
                                printf("%s", "Inserisci lo scalare: ");
                                scanf("%d", &scalare);

                                int *vettore = inserisciVettore(&componenti);

                                int *prodottoVS = prodottoVettoreScalare(vettore, componenti, scalare);

                                cancellaVettoreRiga(vettore);

                                printf("Il prodotto tra il vettore e lo scalare %d è: \n", scalare);
                                stampaArray(prodottoVS, componenti);

                                cancellaVettoreRiga(prodottoVS);
                            }
                            break;

                        case 3: {
                                size_t componenti = 0;
                                size_t righe = 0;
                                size_t colonne = 0;

                                int *vettore = inserisciVettore(&componenti);
                                int **matrice = inserisciMatriceNM(&righe, &colonne);

                                if (colonne != componenti) {
                                    puts("ERROE: il numero di colonne della matrice deve essere UGUALE al numero di componenti del vettore");
                                    return EXIT_FAILURE;
                                }

                                int *prodottoMV = prodottoMatriceVettore(matrice, righe, colonne, vettore, componenti);

                                cancellaMatrice(matrice, righe);
                                cancellaVettoreRiga(vettore);

                                puts("Il prodotto tra la matrice e il vettore è: ");
                                stampaArray(prodottoMV, righe);

                                cancellaVettoreRiga(prodottoMV);
                            }
                            break;

                        case 4: {
                                size_t righe1 = 0;
                                size_t colonne1 = 0;
                                size_t righe2 = 0;
                                size_t colonne2 = 0;

                                int **matrice1 = inserisciMatriceNM(&righe1, &colonne1);

                                int **matrice2 = inserisciMatriceNM(&righe2, &colonne2);

                                if (colonne1 != righe2) {
                                    puts("ERRORE: Il numero di colonne della matrice 1 deve essere UGUALE al numero di righe della matrice 2");
                                    return EXIT_FAILURE;
                                }

                                size_t colonne1Righe2 = colonne1;

                                int ** prodottoM = prodottoMatrici(matrice1, matrice2, righe1, colonne1Righe2, colonne2);

                                cancellaMatrice(matrice1, righe1);
                                cancellaMatrice(matrice2, righe2);

                                puts("Il prodotto tra le 2 matrici è: ");
                                stampaMatrice(prodottoM, righe1, colonne2);

                                cancellaMatrice(prodottoM, righe1);
                            }
                            break;

                        case 5: {
                                int scalare = 0;
                                size_t righe = 0;
                                size_t colonne = 0;

                                printf("Inserisci lo scalare: ");
                                scanf("%d", &scalare);

                                int **matrice = inserisciMatriceNM(&righe, &colonne);

                                int **prodottoMS = prodottoMatriceScalare(matrice, righe, colonne, scalare);

                                cancellaMatrice(matrice, righe);

                                printf("Il prodotto tra la matrice e lo scalare %d è: \n", scalare);
                                stampaMatrice(prodottoMS, righe, colonne);

                                cancellaMatrice(prodottoMS, righe);
                            }
                            break;

                        default: puts("ERRORE: inserisci una scelta valida");
                    }
                } while (r2 != 0);
            }
        }
    } while (r1 != 0);

    return EXIT_SUCCESS;
}