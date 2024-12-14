#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/**
 * @brief Struct per rappresentare una tupla.
 *
 * La struct Tupla è utilizzata per memorizzare il numero di zeri in una riga di una matrice e l'indice della riga.
 *
 * @param numeroDiZeri Numero di zeri nella riga.
 * @param indiceDiRiga Indice della riga nella quale sono contati gli zeri.
 */
typedef struct {
 int numeroDiZeri; /**< Numero di zeri nella riga */
 int indiceDiRiga; /**< Indice della riga nella quale sono contati gli zeri */
} Tupla;

/**
 * @brief Struct per rappresentare una frazione.
 *
 * La struct Frazione è utilizzata per rappresentare le frazioni senza utilizzare i tipi di dato float o double.
 *
 * @param numeratore Numeratore della frazione.
 * @param denominatore Denominatore della frazione.
 */
typedef struct {
 int numeratore;   /**< Numeratore della frazione */
 int denominatore; /**< Denominatore della frazione */
} Frazione;

/**
 * @brief Calcola il Massimo Comun Divisore di 2 numeri
 *
 * Controlla se il valore 'b' è uguale a 0 e ritorna: a.
 * Altrimenti ritorna il MASSIMO COMUN DIVISORE tra 'b' e 'a % b'
 * utilizza la formula di Euclide utilizzando il resto.
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
 * @param rigaA Primo array di interi
 * @param rigaB Secondo array di interi
 * @param colonne Numero di elementi dell'array
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
 * @param riga Array di interi
 * @param colonne Numero di elementi dell'array
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
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Tupla*
 */
Tupla *contaZeri(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Ordina le righe della matrice in ordine crescente in base al numero di zeri.
 *
 * Calcola il numero di zeri per ogni riga utilizzando la funzione contaZeri.
 * Ordina le righe della matrice in base al numero di zeri utilizzando l'algoritmo quick sort
 * e un metodo comparatore che agisce solo sul campo numeroDiZeri della tupla.
 * Esegue una copia della matrice originale, dealloca ogni riga della matrice originale e
 * assegna il puntatore alla riga nella posizione "zeri[i].indiceDiRiga" della matrice copia.
 * Infine, dealloca il puntatore alla matrice di copia e libera l'array di tuple.
 * Ritorna il numero di inversioni necessarie calcolare successivamente il determinante con il metodo di Gauss
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
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
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Bool
 */
bool aScala(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Individua la posizione J del pivot della riga i-esima
 *
 * Chiama dietro le quinte la funzione contaZeriPerRigaConsecutivi.
 *
 * @param riga Array di interi
 * @param colonne Numero di elementi dell'array
 * @return Int
 */
int individuaPivot(int *riga, size_t colonne);

/**
 * @brief Svuota la colonna sottostante al pivot corrente mediante la combinazione lineare
 *
 * Itera sulla matrice partendo dalla riga inserita e arriva fino al numero di righe massimo, nel mentre
 * esegue la combinazione lineare tra la riga dalla quale partire e tutte le righe sottostanti ad essa.
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @param riga Riga dalla quale partire per svuotare la colonna
 * @return Void
 */
void svuotaColonna(int **matrice, size_t righe, size_t colonne, size_t riga);

/**
 * @brief Esegue l'eliminazione di Gauss su una matrice generica (n * m) di interi
 *
 * Fin quando la matrice non è a scala, oppure è stata ciclata tutta la matrice, vengono ordinate le righe in
 * base al numero di zeri che sono in ogni riga, e svuota la colonna sottostante alla riga corrente
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
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
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
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
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Int
 */
int roucheCapelli(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Restituisce il numero di pivot della matrice, in caso non sia a scala ritorna -1
 *
 * Scorre tutta la matrice e fin quando trova un elemento non nullo, incrementa il numero di pivot
 * e passa alla prossima riga.
 * 
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Int
 */
int contaPivot(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Risolve la Matrice
 *
 * Risolve a scala il sistema utilizzando la risoluzione verso il basso e verso l'alto
 * 
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
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
 * @param matrice Matrice di interi
 * @param ordine Mrdine della matrice
 * @return Int
 */
int determinante(int **matrice, size_t ordine);

/**
 * @brief Riduce la matrice eliminando la riga i e la colonna j
 *
 * Elimina la riga i e la colonna j e viene utilizzata all'interno della funzione che calcola il determinante
 * tramite laplace
 *
 * @param matrice Matrice di interi
 * @param ordine Ordine della matrice
 * @param dRiga Riga da rimuovere
 * @param dColonna Colonna da rimuovere
 * @return Int** [matrice di interi]
 */
int **riduciMatrice(int **matrice, size_t ordine, int dRiga, int dColonna);

/**
 * @brief Determinante calcolato con la regola di Sarrus
 *
 * Calcola il determinante di una matrice 3 * 3 con il metodo di sarrus.
 *
 * @param matrice Matrice di interi
 * @param ordine Ordine della matrice
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
 * @param matrice Matrice di interi
 * @param ordine Ordine della matrice
 * @return Int
 */
int laPlace(int **matrice, size_t ordine);

/**
 * @brief Goofy ahh POW [credit: @Framaio25]
 *
 * funzione alternativa di pow per interi 
 *
 * @param base Numero da elevare
 * @param exp Esponente
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
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Void
 */
void ruotaMatrice(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Inverte gli elementi di un array
 *
 * Itera fino alla metà dell'array e lo spêcchia. (peppe riey)
 *
 * @param vettore Array di interi
 * @param ordine Numero di elementi dell'array
 * @return Void
 */
void invertiArray(int *vettore, size_t ordine);

/**
 * @brief Esegue lo shift delle colonne della matrice verso sinistra.
 *
 * Itera per tutta la matrice e posiziona gli elementi nella posizione i-esima alla posizione successiva.
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Void
 */
void shiftSinistraMatrice(int **matrice, size_t righe, size_t colonne);



/**
 * @brief Moltiplica tra di loro 2 vettori e restituisce uno scalare
 *
 * Itera per la lunghezza dell'array e somma a una variabile il prodotto dell'elemento i-esimo del
 * vettore 1 con l'elemento i-esimo del vettore 2, venendo successivamente restituita.
 *
 * @param vettore1 Primo vettore di interi
 * @param vettore2 Secondo vettore di interi
 * @param size Numero di elementi del vettore
 * @return Int
 */
int prodottoVettori(int *vettore1, int *vettore2, size_t size);

/**
 * @brief Moltiplica il vettore per uno scalare
 *
 * Itera per la lunghezza dell'array e l'i-esimo elemento del vettore con lo scalare e restituisce un nuovo vettore
 *
 * @param vettore Primo vettore di interi
 * @param size Numero di elementi del vettore
 * @param scalare Moltiplicatore di ogni elemento del vettore
 * @return Int * [array di interi]
 */
int *prodottoVettoreScalare(int *vettore, size_t size, int scalare);

/**
 * @brief Moltiplica una matrice per un vettore
 *
 * Crea un vettore di lunghezza dinamica (pari al numero delle righe della matrice) e alla sua i-esima posizione assegna la somma dei prodotti
 * di tutti gli elementi j-esimi della matrice e del vettore.
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della seconda matrice
 * @param vettore Vettore di interi
 * @param componenti Numero di elementi del vettore
 * @return Int * [array di interi]
 */
int *prodottoMatriceVettore(int **matrice, size_t righe, size_t colonne, int *vettore, size_t componenti);

/**
 * @brief Moltiplica 2 matrici
 *
 * Esegue il prodotto riga per colonna di due matrici, (una m * n e l'altra n * k). All'elemento i,j 
 * della matrice risultato (m * k); aggiunge la somma degli elementi della prima riga moltiplicati per quelli della seconda
 * e restituisce una nuova matrice
 *
 * @param matrice1 Prima matrice di interi
 * @param matrice2 Seconda matrice di interi
 * @param righe1 Righe della prima matrice
 * @param colonne1Righe2 Colonne della prima matrice e righe della seconda colonna
 * @param colonne2 Colonne della seconda matrice
 * @return Int ** [matrice di interi]
 */
int **prodottoMatrici(int **matrice1, int **matrice2, size_t righe1, size_t colonne1Righe2, size_t colonne2);

/**
 * @brief Moltiplica una matrice per uno scalare
 *
 * Itera su tutta la matrice e moltiplica ogni elemento i,j della matrice per uno scalare e restituisce una nuova matrice
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della seconda matrice
 * @param scalare Moltiplicatore della matrice
 * @return Int ** [matrice di interi]
 */
int **prodottoMatriceScalare(int **matrice, size_t righe, size_t colonne, int scalare);

/**
 * @brief Estrae una colonna da una matrice
 *
 * Assegna a un array gli elementi della
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonna Colonna da estrarre
 * @return Int ** [matrice di interi]
 */
int *estraiColonna(int **matrice, size_t righe, int colonna);




/**
 * @brief Stampa un array di interi
 *
 * @param array Array di interi
 * @param size Numero di elementi dell'array
 * @return Void
 */
void stampaArray(int *array, size_t size);

/**
 * @brief Stampa un array di interi
 *
 * @param matrice Matrice di interi
 * @param righe Numero di righe della matrice
 * @param colonne Numero di colonne della matrice
 * @return Void
 */
void stampaMatrice(int **matrice, size_t righe, size_t colonne);

/**
 * @brief Stampa un array di Tuple
 *
 * @param tuple Array di Tuple
 * @param righe Numero di righe dell'array di Tuple
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
 * @param a Puntatore void
 * @param b Puntatore void
 * @return Int
 */
int compare(const void *a, const void *b);

//FRAZIONI

/**
 * @brief Riduce ai minimi termini una Frazione
 *
 * Calcola il massimo comun divisore di tutti e due i numeri della frazione e li divide per esso.
 *
 * @param frazione Puntatore a Frazione
 * @return Void
 */
void riduciAiMinimiTermini(Frazione *frazione);

/**
 * @brief Modifica la prima frazione moltiplicandola per la seconda e la semplifica
 *
 * Moltiplica il numeratore della prima per quello della seconda e il denominatore
 * della prima per quello della seconda. Infine riduce ai minimi termini
 *
 * @param f1 Puntatore a Frazione
 * @param f2 Puntatore a Frazione
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
 * @param righe Righe della matrice
 * @param colonne Colonne della matrice
 * @return Int **
*/
int **inserisciMatriceNM(size_t *righe, size_t *colonne);

/**
 * @brief Crea una matrice n * n con valori inseriti dall'utente
 *
 * Chiede all'utente l'ordine della matrice che vuole inserire, crea dinamicamente la matrice e chiede
 * all'utente di inserire valore per valore al suo interno, dopo aver fatto ciò, modifica il puntatore dell'ordine
 *
 * @param ordine Ordine della matrice
 * @return Int ** [matrice di interi]
*/
int **inserisciMatriceNN(size_t *ordine);

/**
 * @brief Crea un array di n elementi con valori inseriti dall'utente
 *
 * Chiede all'utente il numero di componenti dell'array che vuole inserire, lo crea dinamicamente e chiede
 * all'utente di inserire valore per valore al suo interno, dopo aver fatto ciò, modifica il puntatore del numero di componenti.
 *
 * @param componenti Numero di componenti del vettore
 * @return Int * [array di interi]
*/
int *inserisciVettore(size_t *componenti);

/**
 * @brief Restituisce una matrice identità dell'ordine dato
 *
 * Crea una matrice dinamica riempita con tutti zeri e sulla diagonale principale inserisce 1.
 *
 * @param ordine Ordine della matrice identità
 * @return Int ** [matrice di interi]
*/
int **creaMatriceIdentita(size_t ordine);

/**
 * @brief Affianca 2 matrici 
 *
 * Crea una matrice che ha come numero di righe il parametro passato all'interno della funzione e come numero
 * di colonne la somma del numero di colonne delle 2 matrici.
 * Copia al suo interno tutti gli elementi della matrice1 e quelli della matrice2 e la restituisce.
 *
 * @param matrice1 Matrice a cui viene affiancata matrice2
 * @param colonne1 Colonne della matrice 1
 * @param matrice2 Matrice che viene affiancata alla matrice1
 * @param colonne2 Colonne della matrice 2
 * @param righe Righe delle 2 matrici
 * @return Int ** [matrice di interi]
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
 * @param matrice Matrice della quale verrà calcolata l'inversa
 * @param ordine Ordine della matrice
 * @return Frazione ** [matrice di frazioni]
*/
Frazione **matriceInversa(int **matrice, size_t ordine);

/**
 * @brief Stampa la matrice di frazioni
 *
 * Se il denominatore è 1, stampa solo il numeratore, altrimenti lo stampa a frazione.
 *
 * @param matrice Matrice di Frazioni
 * @param righe Righe della matrice
 * @param colonne Righe delle colonne
 * @return Void
*/
void stampaMatriceDiFrazioni(Frazione **matrice, size_t righe, size_t colonne);



//DONAZIONE DI @Framaio25
/**
 * @brief Alloca dinamicamente un array di interi
 *
 * Alloca dinamicamente un array di interi e inizializza tutti i suoi valori a zero, se l'allocazione fallisce 
 * restituisce NULL altrimenti restituisce il puntatore al primo elemento dell'array di interi
 * 
 * @param dimensione Numero di componenti dell'array
 * @return Int * [matrice di interi]
 */
int *creaVettoreRiga(size_t dimensione);

/**
 * @brief Alloca dinamicamente una matrice di interi
 *
 * Alloca dinamicamente una matrice di interi in cui ogni elemento è inzializzato a zero, per fare ciò alloca 
 * dinamicamente un array di puntatori a intero di dimensione numRighe, e nell'iesimo elemento di questo array 
 * viene inserito il puntatore al primo elemento di un array di interi di dimensione numColonne allocato dinamicamente 
 * tramite la funzione creaVettoreRiga, se l'allocazione dell array di puntatori a intero e di tutti gli array di interi 
 * riesce restituisce il puntatore al primo elemento dell array di puntatori a interi, altrimenti restituisce NULL
 *
 * @param numRighe Numero di righe della matrice
 * @param numColonne Numero di colonne della matrice
 * @return Int ** [matrice di interi]
 */
int **creaMatrice(size_t numRighe, size_t numColonne);

/**
 * @brief Copia gli elementi di un array (statico o dinamico) in un altro array dinamico
 *
 * Alloca dinamicamente un array di interi di dimensione numColonne tramite la funzione creVettoreRiga, se l'allocazione del 
 * nuovo vettore riga riesce al suo iesimo elemento viene assegnato l'iesimo elemento dell'array passatogli come parametro 
 * (riga[]) e restituisce il puntatore al primo elemento della copia, altrimenti restituisce NULL
 *
 * @param riga[] Puntatore al primo elemento dell array da copiare
 * @param numColonne Numero di elementi del vettore da copiare
 * @return Int ** [matrice di interi]
 */
int *copiaVettoreRiga(int riga[], size_t numColonne);

/**
 * @brief Copia gli elementi di una matrice statica in una matrice dinamica
 *
 * Alloca dinamicamente una matrice di interi di righe numRighe e di colonne numColonne tramite la funzione creaMatrice, 
 * se l'allocazione riesce inizia a riempire la matrice dinamica utilizzando gli elementi della matrice statica passata alla
 * funzione con un cast come puntatore ad array di interi, per elaborare il vettore riga come una matrice, inzializza un offset
 * a 0, a ogni ijesima iterazione questo offset viene incrementato di uno, sfruttando la contiguità in memoria delle matrici statiche
 * assegnando all'ijesimo elemento della matrice dinamica l'elemento di indice offset del vettore statico si otterà una copia dinamica
 * della matrice statica, copiata la matrice, restituisce un puntatore alla matrice dinamica, se l'allocazione della matrice dinamica
 * fallisce restituisce NULL
 *
 * @param pointerTo00 Puntatore al primo elemento della matrice statica usando (int *)matriceStatica
 * @param numRighe Numero di righe della matrice da copiare
 * @param numRighe Numero di colonne della matrice da copiare
 * @return Int * [array di interi]
 */
int **copiaMatriceStaticaInDinamica(int *pointerTo00, size_t numRighe, size_t numColonne);

/**
 * @brief Copia una matrice dinamica in un altra matrice dinamica
 *
 * Alloca dinamicamente una matrice dinamica con la funzione creaMatrice, se l'allocazione riesce all'ijesimo elemento
 * della nuova matrice viene assegnato il valore dell'ijesimo elemento della matrice originale e restituisce il puntatore
 * alla copia della matrice, altrimenti restituisce NULL
 *
 * @param matrice Puntatore alla matrice dinamica
 * @param numRighe Numero di righe della matrice da copiare
 * @param numColonne Numero di colonne della matrice da copiare
 * @return Int ** [matrice di interi]
 */
int **copiaMatriceDinamica(int **matrice, size_t numRighe, size_t numColonne);


/**
 * @brief Dealloca la memoria allocata a un array dinamico
 *
 * @param riga Puntatore al primo elemento dell'array dinamico da deallocare
 * @return Void
*/
void cancellaVettoreRiga(int *riga);

/**
 * @brief Dealloca la memoria allocata a una matrice, e a tutte le sue righe
 *
 * Dealloca la memoria assegnata a ogni array di interi che costituivano le colonne della matrice, e all array di puntatori
 * a intero che creava la matrice
 *
 * @param matrice Puntatore alla matrice dinamica
 * @param numRighe Numero di righe della matrice da eliminare
 * @return Void
*/
void cancellaMatrice(int **matrice, size_t numRighe);

/**
 * @brief Dealloca la memoria allocata a una matrice, e a tutte le sue righe
 *
 * Dealloca la memoria assegnata a ogni array di frazioni che costituivano le colonne della matrice, e all array di puntatori
 * a frazione che creava la matrice
 *
 * @param matrice Puntatore alla matrice dinamica
 * @param numRighe Numero di righe della matrice da eliminare
 * @return Void
*/
void cancellaMatrice_f(Frazione **matrice, size_t numRighe);

/**
 * @brief Crea e retituisce la trasposta di una matrice
 *
 * Alloca dinamicamente una matrice di righe NumColonne e di colonne NumRighe con la funzione creaMatrice , se l'allocazione 
 * riesce all'ijesimo elemento della nuova matrice viene assegnato il valore del jiesimo elemento della matrice passata come
 * parametro e restituisce il puntatore alla nuova matrice dinamica, altrimenti restituisce NULL
 *
 * @param matrice Puntatore alla matrice dinamica di cui si vuole costruire la trasposta
 * @param numRighe Numero di righe della matrice di cui si vuole costruire la trasposta
 * @param numColonne Numero di colonne della matrice di cui si vuole costruire la trasposta
 * @return Int** [matrice di interi]
*/
int **MatriceTrasposta(int **matrice, size_t numRighe, size_t numColonne);

/**
 * @brief Scambia due righe di una matrice dinamica
 *
 * Essendo la matrice un array di puntatori a interi, per scambiare due righe ovvero array di interi, scambia il puntatore
 * alla riga di indice RigaA con il puntatore alla riga di indce rigaB tramite una variabile ausiliaria
 *
 * @param matrice Puntatore alla matrice dinamica
 * @param rigaA Indice della prima riga della matrice da scambiare con la seconda
 * @param rigaB Indice della seconda riga della matrice da scambiare con la prima
 * @return Void
*/
void scambiaRighe(int **matrice, int rigaA, int rigaB);

#endif
