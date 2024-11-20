#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
    Tipo: Tupla
    contiene 2 interi e viene utilizzato per memorizzare quanti zeri ci sono per ogni riga
*/
typedef struct {
    int numeroDiZeri;
    int indiceDiRiga;
} Tupla;

/*
    Tipo: Frazione
    Serve a rappresentare le frazioni senza utilizzare i float
*/
typedef struct {
    int numeratore;
    int denominatore;
} Frazione;

int MCD(int a, int b);
int mcm(int a, int b);
void combinazioneLineare(int *rigaA, int *rigaB, size_t colonne);
int contaZeriPerRigaConsecutivi(const int *riga, size_t colonne);
Tupla *contaZeri(int **matrice, size_t righe, size_t colonne);
void ordinaRighe(int **matrice, size_t righe, size_t colonne);
bool aScala(int **matrice, size_t righe, size_t colonne);
int individuaPivot(int *riga, size_t colonne);
void svuotaColonna(int **matrice, size_t righe, size_t colonne, size_t riga);
void eliminazioneDiGauss(int **matrice, size_t righe, size_t colonne);
void eliminazioneDiGaussJordan(int **matrice, size_t righe, size_t colonne);
int roucheCapelli(int **matrice, size_t righe, size_t colonne);
int contaPivot(int **matrice, size_t righe, size_t colonne);
void risolviSistema(int **matrice, size_t righe, size_t colonne);

int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne);
void ruotaMatrice(int **matrice, size_t righe, size_t colonne);
void invertiTerminiNoti(int *vettore, size_t ordine);
void shiftSinistraMatrice(int **matrice, size_t righe, size_t colonne);

void stampaArray(int *array, size_t size);
void stampaMatrice(int **matrice, size_t righe, size_t colonne);
void stampaTuple(Tupla *tuple, size_t righe);
int compare(const void *a, const void *b);

//FRAZIONI
void riduciAiMinimiTermini(Frazione *frazione);


//DONAZIONE DI MR.MAIO NON DOCUMENTATA
int *creaVettoreRiga(size_t dimensione);
int **creaMatrice(size_t numRighe, size_t numColonne);
int *copiaVettoreRiga(int riga[], size_t numColonne);
int **copiaMatriceStaticaInDinamica(int *pointerTo00, size_t numRighe, size_t numColonne);
int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne);

void cancellaVettoreRiga(int *riga);
void cancellaMatrice(int **matrice, size_t numRighe);

int **MatriceTrasposta(int **matrice, size_t numRighe, size_t numColonne);
void scambiaRighe(int **matrice, int rigaA, int rigaB);

#endif