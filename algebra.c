#include "algebra.h"
#include <stdio.h>
#include <stdlib.h>

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
int MCD(int a, int b) {
    if (b == 0) {
        return a;
    }
    return (MCD(b, a % b));
}

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
int mcm(int a, int b) {
    a = abs(a);
    b = abs(b);
    return ((a * b) / MCD(a, b));
}

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
Tupla *contaZeri(int **matrice, size_t righe, size_t colonne) {
    Tupla *zeri = calloc(righe, sizeof(Tupla));
    for (int i = 0; i < righe; i++) {
        zeri[i].numeroDiZeri = contaZeriPerRigaConsecutivi(matrice[i], colonne);
        zeri[i].indiceDiRiga = i;
    }

    return zeri;
}

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
bool aScala(int **matrice, size_t righe, size_t colonne) {  
    for (int i = 0; i < righe - 1; i++) {
        if (individuaPivot(matrice[i], colonne) >= individuaPivot(matrice[i + 1], colonne)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Individua la posizione J del pivot della riga i-esima
 *
 * Chiama dietro le quinte la funzione contaZeriPerRigaConsecutivi.
 *
 * @param matrice matrice di interi
 * @param colonne numero di elementi dell'array
 * @return Int
 */
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
int eliminazioneDiGauss(int **matrice, size_t righe, size_t colonne) {
    return eliminazioneDiGaussInt(NULL, matrice, righe, colonne);
}

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
void risolviSistema(int **matrice, size_t righe, size_t colonne) {
    int **copia = copiaMatriceDinamica(matrice, righe, colonne);

    eliminazioneDiGauss(copia, righe, colonne);
    int rc = roucheCapelli(copia, righe, colonne);

    if (rc == -1) {
        puts("Sistema Incompatibile");
        return;
    }
    if (rc > 0) {
        printf("Il sistema ammette ∞^%d soluzioni\n", rc);
        return;
    }

    int pivot = contaPivot(copia, righe, colonne);

    

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

/**
 * @brief Inverte gli elementi di un array
 *
 * Itera fino alla metà dell'array e lo spêcchia. (peppe riey)
 *
 * @param array array di interi
 * @param ordine numero di elementi dell'array
 * @return Void
 */
void invertiArray(int *vettore, size_t ordine) {
    for (int i = 0; i < ordine / 2; i++) {
        int tmp = vettore[ordine - i - 1];
        vettore[ordine - i - 1] = vettore[i];
        vettore[i] = tmp;
    }
}

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



/**
 * @brief Stampa un array di interi
 *
 * @param array array di interi
 * @param size numero di elementi dell'array
 * @return Void
 */
void stampaArray(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%4d ", array[i]);
    }   
    puts("");
}

/**
 * @brief Stampa un array di interi
 *
 * @param array array di interi
 * @param righe numero di righe della matrice
 * @param colonne numero di colonne della matrice
 * @return Void
 */
void stampaMatrice(int **matrice, size_t righe, size_t colonne) {
    for (size_t i = 0; i < righe; i++) {
        stampaArray(matrice[i], colonne);
    }
    puts("");
    
}

/**
 * @brief Stampa un array di Tuple
 *
 * @param array array di interi
 * @param righe numero di righe dell'array di tuple
 * @return Void
 */
void stampaTuple(Tupla *tuple, size_t righe) {
    for (int i = 0; i < righe; i++) {
        printf("Numero di Zeri: %d\n", tuple[i].numeroDiZeri);
        printf("Indice di riga: %d\n", tuple[i].indiceDiRiga);
        puts("");
    }
}

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
int compare(const void *a, const void *b) {
    const Tupla *tupleA = (const Tupla *)a;
    const Tupla *tupleB = (const Tupla *)b;

    return (tupleA->numeroDiZeri - tupleB->numeroDiZeri);
}

/**
 * @brief Riduce ai minimi termini una Frazione
 *
 * Calcola il massimo comun divisore di tutti e due i numeri della frazione e li divide per esso.
 *
 * @param frazione puntatore a Frazione
 * @return Void
 */
void riduciAiMinimiTermini(Frazione *frazione) {
    int mcd = MCD(frazione->numeratore,frazione->denominatore);
    frazione->numeratore /= mcd;
    frazione->denominatore /= mcd;

    if (frazione->denominatore < 0) {
        frazione->numeratore *= -1;
        frazione->denominatore *= -1;
    }
}

/**
 * @brief Modifica la prima frazione moltiplicandola per la seconda e la semplifica
 *
 * Moltiplica il numeratore della prima per quello della seconda e il denominatore
 * della prima per quello della seconda. Infine riduce ai minimi termini
 *
 * @param frazione puntatore a Frazione
 * @return Void
 */
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
