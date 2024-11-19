#include "algebra.c"
#include <stdio.h>
#include <string.h>
//define


//function prototypes





int main(void) {
    int rigaA[] = {0, 0, 17, 0};
    int rigaB[] = {1, 8, 32, 9};

    int **matrice = malloc(2 * sizeof(int *));
    matrice[0] = malloc(4 * sizeof(int));
    matrice[1] = malloc(4 * sizeof(int));
    memcpy(matrice[0], rigaA, 4 * sizeof(int));
    memcpy(matrice[1], rigaB, 4 * sizeof(int));


    // combinazioneLineare(rigaA, rigaB, 4);

    // stampaArray(rigaB, 4);
    // puts("");
    // stampaMatrice(matrice, 2, 4);

    // printf("%d\n", contaZeriPerRigaConsecutivi(rigaA, 4));
    Tupla *zeri = contaZeri(matrice, 2, 4);
    // stampaArray(zeri, 2);

    for(int i = 0; i < 2; i++) {
        printf("Numero di Zeri: %d\n", zeri[i].numeroDiZeri);
        printf("Indice di riga: %d\n", zeri[i].indiceDiRiga);
        puts("");
    }

    qsort(zeri, 2, sizeof(Tupla), compare);

    for(int i = 0; i < 2; i++) {
        printf("Numero di Zeri: %d\n", zeri[i].numeroDiZeri);
        printf("Indice di riga: %d\n", zeri[i].indiceDiRiga);
        puts("");
    }

    return EXIT_SUCCESS;
}