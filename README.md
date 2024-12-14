# Algebra-Lineare

## Indice
- [Descrizione](#descrizione)
- [Funzionalità](#funzionalità)
- [Struttura della Directory](#struttura-della-directory)
- [Installazione](#installazione)
- [Nota Importante](#nota-importante)
- [Contributori](#contributori)


## Descrizione

Algebra-Lineare è un programma in C progettato per eseguire varie operazioni di algebra lineare.
Il programma include funzionalità per creare, manipolare ed eseguire operazioni
su matrici e vettori. Supporta l'allocazione dinamica della memoria per matrici e vettori,
e include funzioni per quasi tutte le operazioni.


## Funzionalità

- **Eliminazione di Gauss**: Esegui l'eliminazione di Gauss su una matrice per ridurla a forma a scalini.
- **Trovare Soluzioni della Matrice**: Risolvi sistemi di equazioni lineari utilizzando la forma a scalini ridotta ottenuta dall'eliminazione di Gauss.
- **Calcolo del Determinante**: Calcola il determinante di una matrice.
- **Gestione della Memoria**: Alloca e dealloca memoria per matrici e vettori.
- **Inserimento Matrici**: Inserisci matrici e vettori dall'utente.
- **Stampa Matrici**: Stampa matrici, incluse matrici di frazioni.

## Struttura della Directory
```bash
Algebra-Lineare/  
├── Makefile  
├── bin/
│ └── mainProgram   
├── obj/
│ ├── algebra.o //quando esegui make, verrà creato questo file
│ └── mainProgram.o //quando esegui make, verrà creato questo file  
├── src/
│ ├── algebra.c
│ ├── algebra.h
│ └── mainProgram.c  
└── README.md  
```
## Installazione

Per compilare il programma, apri il terminale e naviga nella directory del progetto. Quindi, esegui il seguente comando:

```bash
#Apri la cartella nel terminale e scrivi:
~/Algebra-Lineare: make 

#Quindi esegui il programma scrivendo:
~/Algebra-Lineare/bin: ./mainProgram
```

## Nota Importante
ps. se trovi dei bug, problemi o hai dei suggerimenti, faccelo sapere. Saremo felici di aiutarti.

## Contributori
- [GiooRussooo](https://github.com/GiooRussooo)
- [Soruk17](https://github.com/Soruk17)
- [Tommischiri](https://github.com/Tommischiri)
- [Framaio25](https://github.com/Framaio25)