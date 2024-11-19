#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    Funzione Ricorsiva che accetta 2 parametri interi 'a' e 'b' e ne restituisce il minimo comune multiplo.
    Controlla se il valore 'b' è uguale a 0 e ritorna: a
    altrimenti ritorna il minimo comune multiplo tra 'b' e 'a % b'
*/

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

int compare(const void *a, const void *b) {
    const Tupla *tupleA = (const Tupla *)a;
    const Tupla *tupleB = (const Tupla *)b;

    return (tupleA->numeroDiZeri - tupleB->numeroDiZeri);
}
  


//--------------------------------------------------------------------------------


void stampaArray(const int *array, size_t size) {
    for(size_t i = 0; i < size; i++) {
        printf("%4d ", array[i]);
    }   
    puts("");
}

void stampaMatrice(const int **matrice, size_t righe, size_t colonne) {
    for(size_t i = 0; i < righe; i++) {
        stampaArray(matrice[i], colonne);
    }
    puts("");
    
}