#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

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

/**
 * @brief Calcola il Massimo Comun Divisore di 2 numeri
 *
 * Controlla se il valore 'b' è uguale a 0 e ritorna: a
 * altrimenti ritorna il MASSIMO COMUN DIVISORE tra 'b' e 'a % b'
 * utilizza la formula di euclide utilizzando il resto.
 *
 * @param a Primo numero intero.
 * @param b Secondo numero intero.
 * @return Int
 */
int MCD(int a, int b);

/**
 * @brief Calcola il Minimo Comune Multiplo di 2 numeri
 *
 * Calcola il valore assoluto dei due numeri e ritorna il loro prodotto
 * diviso per il MCD dei 2 numeri.
 *
 * @param a Primo numero intero.
 * @param b Secondo numero intero.
 * @return Int
 */
int mcm(int a, int b);

/**
 * @brief Esegue la Combinazione lineare di 2 righe
 *
 * Accetta come parametri 2 array di interi insieme al numero di elementi contenuti nell'array
 * Calcola il pivot della prima riga e controlla se nella stessa posizione del pivot della rigaA
 * l'elemento in rigaB è nullo esce dalla funzione.
 * In caso contrario calcola il moltiplicatore per la combinazione lineare e dal moltiplicatore 
 * ricava i coefficienti di combinazione delle due righe, successivamente esegue la combinazione
 * lineare utilizzando i coefficienti.
 * Ritorna il coefficiente di combinazione della rigaB
 *
 * @param rigaA primo array di interi
 * @param rigaB secondo array di interi
 * @param colonne numero di elementi dell'array
 * @return Int
 */
int combinazioneLineare(int *rigaA, int *rigaB, size_t colonne);

/**
 * @brief Conta quanti zeri consecutivi ci sono in una riga prima dell'elemento non nullo
 *
 * inizializza una variabile counter che si occupa di mantenere il conto di quanti zeri consecutivi
 * sono presenti all'interno della riga, successivamente itera su tutta la riga e fin quando non trova
 * un valore non nullo, incrementa la variabile, in caso contrario ritorna il valore di counter.
 * 
 * FONDAMENTALE.
 * @param rigaA array di interi
 * @param colonne numero di elementi dell'array
 * @return Int
 */
int contaZeriPerRigaConsecutivi(const int *riga, size_t colonne);

/**
 * @brief Conta quanti zeri consecutivi ci sono in ogni riga di una matrice
 *
 * Utilizza un array di Tuple per mantenere il conto di quanti zeri ci sono per ogni riga
 * (vedi definizione di Tupla), itera per tutta la matrice ed assegna all'attributo numeroDiZeri
 * dell'array di Tuple il numero di zeri della riga i, e alla proprietà indiceDiRiga l'indice della riga.
 * 
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Tupla*
 */
Tupla *contaZeri(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Ordina le righe della matrice in ordine crescente in base al numero di zeri.
 *
 * Si calcola il numero di zeri per ogni riga passando alla funzione contaZeri la matrice e le sue grandezze
 * ordina secondo un metodo comparatore che agisce solo sul campo numeroDiZeri della tupla utilizzando l'algoritmo
 * quick sort presente nella libreria standard di C.
 * Esegue la copia della matrice in una matrice copia, dealloca ogni riga della matrice originale e gli assegna
 * il puntatore alla riga in posizione "zeri[i].indiceDiRiga" della matrice copia, infine dealloca il puntatore alla
 * matrice di copia e libera l'array di tuple
 * Ritorna il numero di scambi di righe vicine necessari per ordinare le righe
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Int
 */
int ordinaRighe(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Verifica se la matrice è a scala o no
 *
 * Itera da 0 al numero di righe della matrice - 1, e verifica se il numero di zeri della riga corrente 
 * è minore di quello della riga successiva, in caso ogni riga ha meno zeri della successiva, ritornerà true,
 * in caso contrario ci verrà restituito false.
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Bool
 */
bool aScala(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Individua la posizione J del pivot della riga i-esima
 *
 * Chiama dietro le quinte la funzione contaZeriPerRigaConsecutivi.
 *
 * @param matrice matrice di interi
 * @param colonne numero di elementi dell'array
 * @return Int
 */
int individuaPivot(int *riga, size_t colonne);

/**
 * @brief Svuota la colonna sottostante al pivot corrente mediante la combinazione lineare
 *
 * Itera sulla matrice partendo dalla riga inserita e arriva fino al numero di righe massimo, nel mentre
 * esegue la combinazione lineare tra la riga dalla quale partire e tutte le righe sottostanti ad essa.
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @param righe riga dalla quale partire per svuotare la colonna
 * @return Void
 */
void svuotaColonna(int **matrice, size_t righe, size_t colonne, size_t riga);

/**
 * @brief Esegue l'eliminazione di Gauss su una matrice generica (n * m) di interi
 *
 * Fin quando la matrice non è a scala, oppure è stata ciclata tutta la matrice, vengono ordinate le righe in
 * base al numero di zeri che sono in ogni riga, e svuota la colonna sottostante alla riga corrente
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
int eliminazioneDiGauss(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Esegue l'eliminazione di Gauss-Jordan (Gauss verso l'alto) su una matrice (n * m) 
 *        con la m-esima colonna i termini noti
 *
 * Verifica se il numero di righe e colonne (escluso il vettore dei termini noti) sono uguali, 
 * oppure se non è a scala esce dalla funzione, in caso contrario continua.
 * Ruota la matrice di 180° ed effettua uno shift delle colonne a Sinistra per normalizzare la posizione del vettore dei
 * termini noti, successivamente esegue l'eliminazione di Gauss verso il basso sulla matrice risultante e dopo averla fatta
 * riporta la matrice allo stato originario ruotandola di 180° e shiftandola di nuovo a sinistra.
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
void eliminazioneDiGaussJordan(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Restituisce:
 *  1). -1 se il sistema è impossibile
 *  2) 0 se c'è una sola soluzione
 *  3) x se ha inf^x soluzioni.
 *  4) -2 se la matrice in input non è a scala.
 *
 * Sfrutta una funzione ContaPivot che conta i pivot della matrice inserita, calcola il rango di A
 * accettando come parametri matrice, righe, colonne - 1 (esclude l'ultima colonna) perché si presuppone
 * che la matrice sia già a scala, poi calcola il rango di A|b (vettore dei termini noti)
 * 
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Int
 */
int roucheCapelli(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Restituisce il numero di pivot della matrice, in caso non sia a scala ritorna -1
 *
 * Scorre tutta la matrice e fin quando trova un elemento non nullo, incrementa il numero di pivot
 * e passa alla prossima riga.
 * 
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Int
 */
int contaPivot(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Risolve la Matrice
 *
 * Risolve a scala il sistema utilizzando la risoluzione verso il basso e verso l'alto
 * 
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
void risolviSistema(int **matrice, size_t righe, size_t colonne);



/**
 * @brief Calcola e restituisce il determinante di una matrice
 *
 * Calcola il determinante di una matrice riducendola a scala e facendo il prodotto
 * degli elementi sulla diagonale principale, tenendo conto degli scambi fatti e dei
 * coefficienti di combinazione utilizzati.
 * 
 *
 * @param matrice matrice di interi
 * @param ordine ordine della matrice
 * @return Int
 */
int determinante(int **matrice, size_t ordine);

/**
 * @brief Riduce la matrice eliminando la riga i e la colonna j
 *
 * Elimina la riga i e la colonna j e viene utilizzata all'interno della funzione che calcola il determinante
 * tramite laplace
 *
 * @param matrice matrice di interi
 * @param ordine ordine della matrice
 * @param dRiga riga da rimuovere
 * @param dColonna colonna da rimuovere
 * @return Int** [matrice di interi]
 */
int **riduciMatrice(int **matrice, size_t ordine, int dRiga, int dColonna);

/**
 * @brief Determinante calcolato con la regola di Sarrus
 *
 * Calcola il determinante di una matrice 3 * 3 con il metodo di sarrus.
 *
 * @param matrice matrice di interi
 * @param ordine ordine della matrice
 * @return Int
 */
int sarrus(int **matrice, size_t ordine);

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
int laPlace(int **matrice, size_t ordine);

/**
 * @brief goofy ahh POW [credit: @Framaio25]
 *
 * funzione alternativa di pow per interi 
 *
 * @param base numero da elevare
 * @param exp esponente
 * @return Int
 */
int gPow(int base, int exp);

/**
 * @brief Ruota di 180° una matrice
 *
 * Nella prima iterazione della matrice inverte rispetto all'asse verticale le colonne della matrice 
 * e successivamente inverte secondo l'asse orizzontale le righe della matrice, modificando la matrice
 * originale in una matrice ruotata di 180°
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
void ruotaMatrice(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Inverte gli elementi di un array
 *
 * Itera fino alla metà dell'array e lo spêcchia. (peppe riey)
 *
 * @param array array di interi
 * @param ordine numero di elementi dell'array
 * @return Void
 */
void invertiArray(int *vettore, size_t ordine);

/**
 * @brief Esegue lo shift delle colonne della matrice verso sinistra.
 *
 * Itera per tutta la matrice e posiziona gli elementi nella posizione i-esima alla posizione successiva.
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
void shiftSinistraMatrice(int **matrice, size_t righe, size_t colonne);



/**
 * @brief Moltiplica tra di loro 2 vettori e restituisce uno scalare
 *
 * Itera per la lunghezza dell'array e somma ad una variabile il prodotto dell'elemento i-esimo del 
 * vettore 1 con l'elemento i-esimo del vettore 2, venendo successivamente restituita.
 *
 * @param vettore1 primo vettore di interi
 * @param vettore2 secondo vettore di interi
 * @param size numero di elementi del vettore
 * @return Int
 */
int prodottoVettori(int *vettore1, int *vettore2, size_t size);

/**
 * @brief Moltiplica il vettore per uno scalare
 *
 * Itera per la lunghezza dell'array e l'i-esimo elemento del vettore con lo scalare e restituisce un nuovo vettore
 *
 * @param vettore primo vettore di interi
 * @param size numero di elementi del vettore
 * @param scalare moltiplicatore di ogni elemento del vettore
 * @return Int *
 */
int *prodottoVettoreScalare(int *vettore, size_t size, int scalare);

/**
 * @brief Moltiplica 2 matrici
 *
 * Esegue il prodotto riga per colonna di due matrici, (una m * n e l'altra n * k). All'elemento i,j 
 * della matrice risultato (m * k); aggiunge la somma degli elementi della prima riga moltiplicati per quelli della seconda
 * e restituisce una nuova matrice
 *
 * @param matrice1 prima matrice di interi
 * @param matrice2 seconda matrice di interi
 * @param righe1 righe della prima matrice
 * @param colonne1righe2 colonne della prima matrice e righe della seconda colonna
 * @param colonne2 colonne della seconda matrice
 * @return Int **
 */
int **prodottoMatrici(int **matrice1, int **matrice2, size_t righe1, size_t colonne1Righe2, size_t colonne2);

/**
 * @brief Moltiplica una matrice per uno scalare
 *
 * Itera su tutta la matrice e moltiplica ogni elemento i,j della matrice per uno scalare e restituisce una nuova matrice
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della seconda matrice
 * @param scalare moltiplicatore della matrice
 * @return Int **
 */
int **prodottoMatriceScalare(int **matrice, size_t righe, size_t colonne, int scalare);

/**
 * @brief estrae una colonna da una matrice
 *
 * Assegna ad un array gli elementi della
 *
 * @param matrice matrice di interi
 * @param righe numero di righe della matrice
 * @param colonna colonna da estrarre
 * @return Int **
 */
int *estraiColonna(int **matrice, size_t righe, int colonna);




/**
 * @brief Stampa un array di interi
 *
 * @param array array di interi
 * @param size numero di elementi dell'array
 * @return Void
 */
void stampaArray(int *array, size_t size);

/**
 * @brief Stampa un array di interi
 *
 * @param array array di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
void stampaMatrice(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Stampa un array di Tuple
 *
 * @param array array di interi
 * @param righe numero di righe dell'array di tuple
 * @return Void
 */
void stampaTuple(Tupla *tuple, size_t righe);

/**
 * @brief Comparatore necessario per la funzione qsort().
 *
 * Casta i due puntatori a void in due puntatori a Tupla, successivamente esegue la differenza tra il primo
 * e il secondo valore e restituisce:
 * - un numero maggiore di zero se da come risultato un valore positivo (il valore a è più grande).
 * - zero se i valori sono uguali. 
 * - qualsiasi numero negativo se il secondo è più grande del primo.
 *
 * @param a puntatore void
 * @param b puntatore void
 * @return Void
 */
int compare(const void *a, const void *b);

//FRAZIONI

/**
 * @brief Riduce ai minimi termini una Frazione
 *
 * Calcola il massimo comun divisore di tutti e due i numeri della frazione e li divide per esso.
 *
 * @param frazione puntatore a Frazione
 * @return Void
 */
void riduciAiMinimiTermini(Frazione *frazione);

/**
 * @brief Modifica la prima frazione moltiplicandola per la seconda e la semplifica
 *
 * Moltiplica il numeratore della prima per quello della seconda e il denominatore
 * della prima per quello della seconda. Infine riduce ai minimi termini
 *
 * @param frazione puntatore a Frazione
 * @return Void
 */
void moltiplicaFrazioni(Frazione *f1, Frazione *f2);

/**
 * @brief Crea una matrice n * m con valori inseriti dall'utente
 *
 * Chiede all'utente le righe e le colonne della matrice che vuole inserire, crea dinamicamente la matrice e chiede
 * all'utente di inserire valore per valore al suo interno, dopo aver fatto ciò, modifica i due puntatori delle
 * righe e delle colonne con le misure della matrice
 *
 * @param righe righe della matrice
 * @param colonne colonne della matrice
 * @return Int **
*/
int **inserisciMatriceNM(size_t *righe, size_t *colonne);

/**
 * @brief Crea una matrice n * n con valori inseriti dall'utente
 *
 * Chiede all'utente l'ordine della matrice che vuole inserire, crea dinamicamente la matrice e chiede
 * all'utente di inserire valore per valore al suo interno, dopo aver fatto ciò, modifica il puntatore dell'ordine
 *
 * @param ordine ordine della matrice
 * @return Int **
*/
int **inserisciMatriceNN(size_t *ordine);

/**
 * @brief Restituisce una matrice identità dell'ordine dato
 *
 * Crea una matrice dinamica riempita con tutti zeri e sulla diagonale principale inserisce 1.
 *
 * @param ordine ordine della matrice identità
 * @return Int **
*/
int **creaMatriceIdentita(size_t ordine);

/**
 * @brief Affianca 2 matrici 
 *
 * Crea una matrice che ha come numero di righe il parametro passato all'interno della funzione e come numero
 * di colonne colonne la somma del numero di colonne delle 2 matrici.
 * Copia al suo interno tutti gli elementi della matrice1 e quelli della matrice2 e la restituisce.
 *
 * @param matrice1 matrice a cui viene affiancata matrice2
 * @param colonne1 colonne della matrice 1
 * @param matrice2 matrice che viene affiancata alla matrice1
 * @param colonne2 colonne della matrice 2
 * @param righe righe delle 2 matrici
 * @return Int **
*/
int **affiancaMatrice(int **matrice1, size_t colonne1, int **matrice2, size_t colonne2, size_t righe);

/**
 * @brief Affianca 2 matrici 
 *
 * Affianca alla matrice stessa la matrice identità (creata tramite creaMatriceIdentità) utilizzando il metodo 
 * affiancaMatrice, riduce la prima metà della matrice ad una matrice identità tramite il metodo di Gauss e Gauss Jordan.
 * Successivamente inserisce la seconda metà della matrice affiancata (che per conseguenza dell'eliminaizone di Gauss sarà
 * la matrice inversa di quella iniziale) in una matrice di frazioni, ruducendo opportunamente ogni frazione ai minimi termini.
 *
 * @param matrice matrice della quale verrà calcolata l'inversa
 * @param ordine ordine della matrice
 * @return Frazione **
*/
Frazione **matriceInversa(int **matrice, size_t ordine);

/**
 * @brief Stampa la matrice di frazioni
 *
 * Se il denominatore è 1, stampa solo il numeratore, altrimenti lo stampa a frazione.
 *
 * @param matrice matrice di Frazioni
 * @param righe righe della matrice
 * @param colonne righe delle colonne
 * @return Void
*/
void stampaMatriceDiFrazioni(Frazione **matrice, size_t righe, size_t colonne);



//DONAZIONE DI @Framaio25
/**
    TODO: @Framaio25 -> fare la documentazione
*/
int *creaVettoreRiga(size_t dimensione);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
int **creaMatrice(size_t numRighe, size_t numColonne);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
int *copiaVettoreRiga(int riga[], size_t numColonne);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
int **copiaMatriceStaticaInDinamica(int *pointerTo00, size_t numRighe, size_t numColonne);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne);


/**
    TODO: @Framaio25 -> fare la documentazione
*/
void cancellaVettoreRiga(int *riga);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
void cancellaMatrice(int **matrice, size_t numRighe);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
void cancellaMatrice_f(Frazione **matrice, size_t numRighe);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
int **MatriceTrasposta(int **matrice, size_t numRighe, size_t numColonne);

/**
    TODO: @Framaio25 -> fare la documentazione
*/
void scambiaRighe(int **matrice, int rigaA, int rigaB);

#endif