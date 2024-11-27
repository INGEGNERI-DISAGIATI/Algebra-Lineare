#include "algebra.h"
#include <stdio.h>
#include <stdlib.h>


int MCD(int a, int b) {
    if (b == 0) {
        return a;
    }
    return (MCD(b, a % b));
}

int mcm(int a, int b) {
    a = abs(a);
    b = abs(b);
    return ((a * b) / MCD(a, b));
}


int combinazioneLineare(int *rigaA, int *rigaB, size_t colonne) {
    int jPivot = individuaPivot(rigaA, colonne);
    
    if (rigaB[jPivot] == 0) {
        return 1;
    }

    int moltiplicatore = mcm(rigaA[jPivot], rigaB[jPivot]);

    int coefficienteB = (moltiplicatore / rigaB[jPivot]);
    int coefficienteA = (moltiplicatore / rigaA[jPivot]);

    for (size_t i = 0; i < colonne; i++) {
        rigaB[i] = (coefficienteB * rigaB[i]) - (coefficienteA * rigaA[i]);
    }
    return coefficienteB;
}


int contaZeriPerRigaConsecutivi(const int *riga, size_t colonne) {
    int counter = 0;
    for (int i = 0; i < colonne; i++) {
        if (riga[i] != 0 ) {
            return counter;
        }
        counter++;
    }
    return counter;
}

Tupla *contaZeri(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = calloc(righe, sizeof(Tupla));
    for (int i = 0; i < righe; i++) {
        zeri[i].numeroDiZeri = contaZeriPerRigaConsecutivi(matrice[i], colonne);
        zeri[i].indiceDiRiga = i;
    }

    return zeri;
}

int ordinaRighe(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = contaZeri(matrice, righe, colonne);

    qsort(zeri, righe, sizeof(Tupla), compare);

    int scambi = 0;
    for(int i = 0; i < righe; i++) {
        scambi += abs(zeri[i].indiceDiRiga - i);
    }
    scambi /= 2;

    int **copia = copiaMatriceDinamica(matrice, righe, colonne);
    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
        matrice[i] = copia[zeri[i].indiceDiRiga];
    }

    free(copia);
    free(zeri);

    return scambi;
}




bool aScala(int **matrice, size_t righe, size_t colonne) {  
    for (int i = 0; i < righe - 1; i++) {
        if (individuaPivot(matrice[i], colonne) >= individuaPivot(matrice[i + 1], colonne)) {
            return false;
        }
    }
    return true;
}

int individuaPivot(int *riga, size_t colonne) {
    return contaZeriPerRigaConsecutivi(riga, colonne);
}

/**
 * @brief Svuota la colonna sottostante al pivot corrente mediante la combinazione lineare
 *
 * Itera sulla matrice partendo dalla riga inserita e arriva fino al numero di righe massimo, nel mentre
 * esegue la combinazione lineare tra la riga dalla quale partire e tutte le righe sottostanti ad essa.
 * Se viene passato come primo parametro un puntatore non nullo ad un array  (di lunghezza righe) allora
 * moltiplica l'elemento i dell'array per il coefficiente di combinazione usato per modificare la riga i a
 * attraverso le combinazioni lineari
 * 
 * @param arrayCoefficienti array di coefficienti di combinazione da modificare
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @param righe riga dalla quale partire per svuotare la colonna
 * @return Void
 */
void svuotaColonnaInt(int *coefficienti, int **matrice, size_t righe, size_t colonne, size_t riga) {
    for (int i = riga + 1; i < righe; i++) {
        int coefficiente = combinazioneLineare(matrice[riga], matrice[i], colonne);
        if(coefficienti != NULL) {
            *coefficienti *= coefficiente;
        }
    }
}


void svuotaColonna(int **matrice, size_t righe, size_t colonne, size_t riga) {
    svuotaColonnaInt(NULL, matrice, righe, colonne, riga);
}

/**
 * @brief Esegue l'eliminazione di Gauss su una matrice generica (n * m) di interi
 *
 * Fin quando la matrice non è a scala, oppure è stata ciclata tutta la matrice, vengono ordinate le righe in
 * base al numero di zeri che sono in ogni riga, e svuota la colonna sottostante alla riga corrente
 * Se viene passato come primo parametro un puntatore non nullo ad un array (di lunghezza righe) allora modifica
 * l'array in modo che l'elemento i corrisponde al prodotto dei coefficienti di combinazione usati sulla riga i
 * durante la riduzione a scala
 *
 * @param arrayCoefficienti array di coefficienti di combinazione da modificare
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
int eliminazioneDiGaussInt(int *coefficienti, int **matrice, size_t righe, size_t colonne) {
    int index = 0;
    int scambi = 0;
    if(coefficienti != NULL) {
        *coefficienti = 1;
    }
    while (!aScala(matrice, righe, colonne) && index < righe) {
        scambi += ordinaRighe(matrice, righe, colonne);
        svuotaColonnaInt(coefficienti, matrice, righe, colonne, index);

        index ++;
    }

    return scambi;
}

int eliminazioneDiGauss(int **matrice, size_t righe, size_t colonne) {
    return eliminazioneDiGaussInt(NULL, matrice, righe, colonne);
}


void eliminazioneDiGaussJordan(int **matrice, size_t righe, size_t colonne) {
    if (!aScala(matrice, righe, colonne)) {
        return;
    }

    ruotaMatrice(matrice, righe, colonne);
    shiftSinistraMatrice(matrice, righe, colonne);
    
    eliminazioneDiGauss(matrice, righe, colonne);
    
    ruotaMatrice(matrice, righe, colonne);
    shiftSinistraMatrice(matrice, righe, colonne);
    ordinaRighe(matrice, righe, colonne);
}

int roucheCapelli(int **matrice, size_t righe, size_t colonne) {
    if (!aScala(matrice, righe, colonne)) {
        return -2;
    }
    //verifica matrice senza termini noti
    int rangoA = contaPivot(matrice, righe, colonne - 1);
    int rangoAb = contaPivot(matrice, righe, colonne);

    if (rangoA != rangoAb) {
        return -1;
    }
    else {
        return (colonne - 1 - rangoA);
    }
}


int contaPivot(int **matrice, size_t righe, size_t colonne) {
    if(!aScala(matrice, righe, colonne)) {
        return -1;
    }
    int counter = 0;
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            if (matrice[i][j] != 0) {
                counter++;
                break;
            }
        }
    }

    return counter;
}

void risolviSistema(int **matrice, size_t righe, size_t colonne) {
    int **copia = copiaMatriceDinamica(matrice, righe, colonne);

    eliminazioneDiGauss(copia, righe, colonne);
    int rc = roucheCapelli(copia, righe, colonne);

    if (rc == -1) {
        puts("Sistema Incompatibile");
        return;
    }
    if (rc > 0) {
        stampaMatrice(copia, righe, colonne);
        printf("Il sistema ammette ∞^%d soluzioni\n", rc);
        return;
    }

    int pivot = contaPivot(copia, righe, colonne);
    eliminazioneDiGaussJordan(copia, righe, colonne);
    

    Frazione *soluzioni = malloc(pivot * sizeof(Frazione));
    
    for (int i = 0; i < pivot; i++) {
        
        soluzioni[i].denominatore = copia[i][i];
        soluzioni[i].numeratore = copia[i][colonne - 1];
        
        riduciAiMinimiTermini(&soluzioni[i]);

        printf("x%d = %d", (i + 1), soluzioni[i].numeratore);
        if (soluzioni[i].denominatore != 1) {
            printf("/%d", soluzioni[i].denominatore);
        }

        puts("");
    }

    free(copia);
}

int determinante(int **matriceOriginale, size_t ordine) {
    /*if(!aScala(matrice, ordine, ordine)) {
        return -1;
    }*/
    int **matrice = copiaMatriceDinamica(matriceOriginale, ordine, ordine);
    Frazione determinante;
    determinante.numeratore = 1;

    int coefficienti = 1;

    int moltiplicatoreDeterminante = eliminazioneDiGaussInt(&coefficienti, matrice, ordine, ordine);
    
    for(int i = 0; i < ordine; i++) {
        determinante.numeratore *= matrice[i][i];
    }
    determinante.denominatore = coefficienti;
    
    free(matrice);
    riduciAiMinimiTermini(&determinante);

    return (moltiplicatoreDeterminante % 2 == 0) ? determinante.numeratore : -1 * determinante.numeratore;
}

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

void ruotaMatrice(int **matrice, size_t righe, size_t colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne / 2; j++) {
            int tmp2 = matrice[i][colonne - j - 1];
            matrice[i][colonne - j - 1] = matrice[i][j];
            matrice[i][j] = tmp2;
        }
    }
    for (int i = 0; i < righe / 2; i++) {
        int *tmp = matrice[righe - i - 1];
        matrice[righe - i - 1] = matrice[i];
        matrice[i] = tmp;
    }
}

void invertiArray(int *vettore, size_t ordine) {
    for (int i = 0; i < ordine / 2; i++) {
        int tmp = vettore[ordine - i - 1];
        vettore[ordine - i - 1] = vettore[i];
        vettore[i] = tmp;
    }
}

void shiftSinistraMatrice(int **matrice, size_t righe, size_t colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne - 1; j++) {
            int tmp = matrice[i][j];
            matrice[i][j] = matrice[i][j + 1];
            matrice[i][j + 1] = tmp;
        }
    }
}
//--------------------------------------------------------------------------------



void stampaArray(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%4d ", array[i]);
    }   
    puts("");
}

void stampaMatrice(int **matrice, size_t righe, size_t colonne) {
    for (size_t i = 0; i < righe; i++) {
        stampaArray(matrice[i], colonne);
    }
    puts("");
    
}

void stampaTuple(Tupla *tuple, size_t righe) {
    for (int i = 0; i < righe; i++) {
        printf("Numero di Zeri: %d\n", tuple[i].numeroDiZeri);
        printf("Indice di riga: %d\n", tuple[i].indiceDiRiga);
        puts("");
    }
}

int compare(const void *a, const void *b) {
    const Tupla *tupleA = (const Tupla *)a;
    const Tupla *tupleB = (const Tupla *)b;

    return (tupleA->numeroDiZeri - tupleB->numeroDiZeri);
}

void riduciAiMinimiTermini(Frazione *frazione) {
    int mcd = MCD(frazione->numeratore,frazione->denominatore);
    frazione->numeratore /= mcd;
    frazione->denominatore /= mcd;

    if (frazione->denominatore < 0) {
        frazione->numeratore *= -1;
        frazione->denominatore *= -1;
    }
}

void moltiplicaFrazioni(Frazione *f1, Frazione *f2) {
    f1->numeratore = f1->numeratore * f2->numeratore;
    f1->denominatore = f1->denominatore * f2->denominatore;
    riduciAiMinimiTermini(f1);
}


// ------------------------------------------------------------------------------------------------ //
                                //MR MAIO'S FUNCTIONS

int *creaVettoreRiga(size_t dimensione) {
    int *ret = calloc(dimensione, sizeof(int));
    if (ret == NULL) {
        puts("Errore di allocazione della memoria in creaVettoreRiga");
    }
    return ret;
}

int **creaMatrice(size_t numRighe, size_t numColonne) {
    int **ret = calloc(numRighe, sizeof(int *));
    if (ret == NULL) {
        puts("Errore di allocazione della memoria in creaMatrice");
        return ret;
    }
    for (size_t i = 0; i < numRighe; i++) {
        ret[i] = creaVettoreRiga(numColonne);
    }
    return ret;
}

int *copiaVettoreRiga(int riga[], size_t numColonne) {
    int *ret = creaVettoreRiga(numColonne);
    for (int i = 0; i < numColonne; i++) {
        ret[i] = riga[i];
    }
    return ret;
}

int **copiaMatriceStaticaInDinamica(int *pointerTo00, size_t numRighe, size_t numColonne) {
    int **ret = creaMatrice(numRighe, numColonne);
    int offset = 0;
    for (size_t i = 0; i < numRighe; i++) {
        for (size_t j = 0; j < numColonne; j++) {
            ret[i][j] = pointerTo00[offset];
            offset++;
        }
    }
    return ret;
}

int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne) {
    int **ret = creaMatrice(numRighe, numColonne);
    for (size_t i = 0; i < numRighe; i++) {
        for (size_t j = 0; j < numColonne; j++) {
            ret[i][j] = matrice[i][j];
        }
    }
    return ret;
}

void cancellaVettoreRiga(int *riga) {
    free(riga);
}

void cancellaMatrice(int **matrice, size_t numRighe) {
    for (size_t i = 0; i < numRighe; i++) {
        cancellaVettoreRiga(matrice[i]);
    }
}

int **MatriceTrasposta(int **matrice, size_t numRighe, size_t numColonne) {
    int **ret = creaMatrice(numColonne, numRighe);
    for (size_t i = 0; i < numColonne; i++) {
        for (size_t j = 0; j < numRighe; j++) {
            ret[i][j] = matrice[j][i];
        }
    }
    return ret;
}

void scambiaRighe(int **matrice, int rigaA, int rigaB) {
    int *scambio = matrice[rigaA];
    matrice[rigaA] = matrice[rigaB];
    matrice[rigaB] = scambio;
}
