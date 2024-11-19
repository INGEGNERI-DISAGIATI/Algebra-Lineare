#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "old_algebra.c"

/*
    Funzione Ricorsiva che accetta 2 parametri interi 'a' e 'b' e ne restituisce il minimo comune multiplo.
    Controlla se il valore 'b' è uguale a 0 e ritorna: a
    altrimenti ritorna il minimo comune multiplo tra 'b' e 'a % b'
*/

int compare(const void *a, const void *b);

typedef struct {
    int numeroDiZeri;
    int indiceDiRiga;
} Tupla;


int MCD(int a, int b) {
    if(b == 0) {
        return a;
    }
    return (MCD(b, a % b));
}

int mcm(int a, int b) {
    a = abs(a);
    b = abs(b);
    return ((a * b) / MCD(a, b));
}

void combinazioneLineare(const int *rigaA, int *rigaB, size_t colonne) {
    if(rigaB[0] == 0) {
        return;
    }

    int moltiplicatore = mcm(rigaA[0], rigaB[0]);
    int coefficienteA = (moltiplicatore / rigaA[0]);
    int coefficienteB = (moltiplicatore / rigaB[0]);

    for(size_t i = 0; i < colonne; i++) {
        rigaB[i] = (coefficienteB * rigaB[i]) - (coefficienteA * rigaA[i]);
    }
}

int contaZeriPerRigaConsecutivi(const int *riga, size_t colonne) {
    int counter = 0;
    for(int i = 0; i < colonne; i++) {
        if(riga[i] != 0 ) {
            return counter;
        }
        counter++;
    }
    return counter;
}

Tupla *contaZeri(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = calloc(righe, sizeof(Tupla));
    for(int i = 0; i < righe; i++) {
        zeri[i].numeroDiZeri = contaZeriPerRigaConsecutivi(matrice[i], colonne);
        zeri[i].indiceDiRiga = i;
    }

    return zeri;
}

/*
    funzione conta pivot;
*/

void ordinaRighe(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = contaZeri(matrice, righe, colonne);
    qsort(zeri, righe, sizeof(Tupla), compare);
    int **copia = copiaMatriceDinamica(matrice, righe, colonne);
    
    for(int i = 0; i < righe; i++) {
        // matrice[i] = copia[zeri[i].indiceDiRiga];
    
    }

    cancellaMatrice(copia, righe);
}
  
/*
    per eliminazione di gauss verso l'alto, fare la matrice trasposta della matrice ridotta a scala e 
    applicare la riduzione verso il basso.

    per la matrice trasposta, le righe diventano le colonne di quella ritornata.
    1 2 3
    4 5 6
    7 8 9

    1 4 7
    2 5 8
    3 6 9 */


//--------------------------------------------------------------------------------


void stampaArray(int *array, size_t size) {
    for(size_t i = 0; i < size; i++) {
        printf("%4d ", array[i]);
    }   
    puts("");
}

void stampaMatrice(int **matrice, size_t righe, size_t colonne) {
    for(size_t i = 0; i < righe; i++) {
        stampaArray(matrice[i], colonne);
    }
    puts("");
    
}

void stampaTuple(Tupla *tuple, size_t righe) {
    for(int i = 0; i < righe; i++) {
        printf("Numero di Zeri: %d\n", tuple[i].numeroDiZeri);
        printf("Indice di riga: %d\n", tuple[i].indiceDiRiga);
        puts("");
    }
}

/*
    Compare di tuple per ordinare le tuple.
*/
int compare(const void *a, const void *b) {
    const Tupla *tupleA = (const Tupla *)a;
    const Tupla *tupleB = (const Tupla *)b;

    return (tupleA->numeroDiZeri - tupleB->numeroDiZeri);
}