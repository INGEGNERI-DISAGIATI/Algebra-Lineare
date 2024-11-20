#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "old_algebra.c"

typedef struct {
    int numeroDiZeri;
    int indiceDiRiga;
} Tupla;


int mcm(int a, int b);
void combinazioneLineare(int *rigaA, int *rigaB, size_t colonne);
int contaZeriPerRigaConsecutivi(const int *riga, size_t colonne);
Tupla *contaZeri(int **matrice, size_t righe, size_t colonne);
void ordinaRighe(int **matrice, size_t righe, size_t colonne);
bool aScala(int **matrice, size_t righe, size_t colonne);
int individuaPivot(int *riga, size_t colonne);
void svuotaColonna(int **matrice, size_t righe, size_t colonne, size_t riga);
void eliminazioneDiGauss(int **matrice, size_t righe, size_t colonne);

void ruotaMatrice(int **matrice, size_t ordine);

void stampaArray(int *array, size_t size);
void stampaMatrice(int **matrice, size_t righe, size_t colonne);
void stampaTuple(Tupla *tuple, size_t righe);
int compare(const void *a, const void *b);







/*
    Funzione Ricorsiva che accetta 2 parametri interi 'a' e 'b' e ne restituisce il minimo comune multiplo.
    Controlla se il valore 'b' è uguale a 0 e ritorna: a
    altrimenti ritorna il MASSIMO COMUN DIVISORE tra 'b' e 'a % b'
*/
int MCD(int a, int b) {
    if(b == 0) {
        return a;
    }
    return (MCD(b, a % b));
}

/*

*/
int mcm(int a, int b) {
    a = abs(a);
    b = abs(b);
    return ((a * b) / MCD(a, b));
}

/*

*/
void combinazioneLineare(int *rigaA, int *rigaB, size_t colonne) {
    int jPivot = individuaPivot(rigaA, colonne);
    
    if(rigaB[jPivot] == 0) {
        return;
    }

    int moltiplicatore = mcm(rigaA[jPivot], rigaB[jPivot]);

    int coefficienteA = (moltiplicatore / rigaA[jPivot]);
    int coefficienteB = (moltiplicatore / rigaB[jPivot]);

    for(size_t i = 0; i < colonne; i++) {
        rigaB[i] = (coefficienteB * rigaB[i]) - (coefficienteA * rigaA[i]);
    }
}

/*

*/
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

/*

*/
Tupla *contaZeri(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = calloc(righe, sizeof(Tupla));
    for(int i = 0; i < righe; i++) {
        zeri[i].numeroDiZeri = contaZeriPerRigaConsecutivi(matrice[i], colonne);
        zeri[i].indiceDiRiga = i;
    }

    return zeri;
}

/*

*/
void ordinaRighe(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = contaZeri(matrice, righe, colonne);
    qsort(zeri, righe, sizeof(Tupla), compare);
    
    int **copia = copiaMatriceDinamica(matrice, righe, colonne);
    
    for(int i = 0; i < righe; i++) {
        free(matrice[i]);
        matrice[i] = copia[zeri[i].indiceDiRiga];
    }

    free(copia);
    free(zeri);
}

/*

*/  
bool aScala(int **matrice, size_t righe, size_t colonne) {  
    for(int i = 0; i < righe - 1; i++) {
        if(individuaPivot(matrice[i], colonne) >= individuaPivot(matrice[i + 1], colonne)) {
            return false;
        }
    }
    return true;
}

/*

*/
int individuaPivot(int *riga, size_t colonne) {
    return contaZeriPerRigaConsecutivi(riga, colonne);
}

/*

*/
void svuotaColonna(int **matrice, size_t righe, size_t colonne, size_t riga) {
    for(int i = riga + 1; i < righe; i++) {
        combinazioneLineare(matrice[riga], matrice[i], colonne);
    }
}

/*

*/
void eliminazioneDiGauss(int **matrice, size_t righe, size_t colonne) {
    int index = 0;

    while(!aScala(matrice, righe, colonne) && index < righe) {
        ordinaRighe(matrice, righe, colonne);
        svuotaColonna(matrice, righe, colonne, index);

        index ++;
    }
}

/*
    prendere la matrice con i termini noti (non mi interessa di separarli)
    ruotare con ruotaMatrice
    
*/

// void eliminazioneDiGaussJordan(int **matrice, size_t righe, size_t colonne) {
//     if(righe != colonne - 1) {
//         return;
//     }

//     //int *terminiNoti = separaTerminiNoti(matrice, righe, colonne - 1);
    
//     ruotaMatrice(matrice, ordine);
//     shiftSinistraMatrice(matrice, righe, righe)
//     //invertiTerminiNoti(terminiNoti, ordine);
//     //int **matriceCompleta = affiancaVettoreAMatrice(matrice, vettore, ordine);
//     eliminazioneDiGauss(matrice, ordine, ordine + 1);
// }

/*

*/
void ruotaMatrice(int **matrice, size_t ordine) {
    
    for(int i = 0; i < ordine / 2; i++) {
        for(int j = 0; j < ordine / 2; j++) {
            int tmp2 = matrice[i][ordine - j - 1];
            matrice[i][ordine - j - 1] = matrice[i][j];
            matrice[i][j] = tmp2;
        }
        int *tmp = matrice[ordine - i - 1];
        matrice[ordine - i - 1] = matrice[i];
        matrice[i] = tmp;
    }
}

void invertiTerminiNoti(int *vettore, size_t ordine) {
    for(int i = 0; i < ordine / 2; i++) {
        int tmp = vettore[ordine - i - 1];
        vettore[ordine - i - 1] = vettore[i];
        vettore[i] = tmp;
    }
}

void shiftSinistraMatrice(int **matrice, size_t righe, size_t colonne) {
    for(int i = 0; i < righe; i++) {
        for(int j = 0; j < colonne - 1; j++) {
            int tmp = matrice[i][j];
            matrice[i][j] = matrice[i][j + 1];
            matrice[i][j + 1] = tmp;
        }
    }
}
//--------------------------------------------------------------------------------



/*

*/
void stampaArray(int *array, size_t size) {
    for(size_t i = 0; i < size; i++) {
        printf("%4d ", array[i]);
    }   
    puts("");
}

/*

*/
void stampaMatrice(int **matrice, size_t righe, size_t colonne) {
    for(size_t i = 0; i < righe; i++) {
        stampaArray(matrice[i], colonne);
    }
    puts("");
    
}

/*

*/
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


/*
    per eliminazione di gauss verso l'alto, fare la matrice trasposta della matrice ridotta a scala e 
    applicare la riduzione verso il basso.

    per la matrice trasposta, le righe diventano le colonne di quella ritornata.
    1 2 3
    4 5 6
    7 8 9

    1 4 7
    2 5 8
    3 6 9 
*/