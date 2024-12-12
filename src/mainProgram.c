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
            /*
            case 3: {
                
                int r2 = 0;

                size_t righe1 = 0;
                size_t colonne1 = 0;
                
                size_t righe2 = 0;
                size_t colonne2 = 0;

                int **matrice1 = inserisciMatriceNM(righe1, colonne1);
                int **matrice2 = inserisciMatriceNM(righe2, colonne2);

                if (colonne1 != righe2) {
                    puts("ERRORE: Il numero di colonne della matrice 1 deve essere uguale al numero di righe della matrice 2");
                    break;
                }

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
                        case 0: {
                                //TODO:
                            }
                            break;
                        case 1: {
                                //TODO:
                            }
                            break;
                        case 2: {
                                //TODO:
                            }
                            break;
                        case 3: {
                                //TODO:
                            }
                            break;
                        case 4: {
                                //TODO:
                            }
                            break;
                        case 5: {
                                //TODO:
                            }
                            break;

                        default:
                    }
                } while (r2 != 0);


                cancellaMatrice(matrice1, righe1);
                cancellaMatrice(matrice2, righe2);
                cancellaMatrice(prodottoMatrice, righe1);
                */

            }
        }
    while (r1 != 0);

    return EXIT_SUCCESS;
}