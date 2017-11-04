//
//  funzioni.h
//  Calcolatore
//
//  Created by Filippo Ferrandino - Salvatore Capuozzo on 04/11/17.
//  Copyright © 2017 Filippo Ferrandino - Salvatore Capuozzo. All rights reserved.
//

#ifndef funzioni_h
#define funzioni_h

#include <dirent.h>
#include "plotCsvFile.h"

#define k 50
#define N 10

// Struttura rappresentante l'analisi di un singolo pacchetto
struct analis{
    char attuale[12];
    bool corretto;
    float probabilita[k];
    float p_max;
    
};

// Funzione di riconoscimento del tipo e del numero delle colonne del file csv
void f1();

// Funzione di prelevamento della stringa Attuale
void f1(char *);

// Funzione di confronto delle stringhe Attuale-Risultato
void f1(analis *);

// Funzione di prelevamento delle probabilità per tipi C&T
void f1(float *);

// Funzione di prelevamento delle probabilità per tipi T&C
void f1(float *, int);

// Funzione di controllo sulle probabilità
// (restituisce 'true' se la somma delle probabilità è pari a 1)
bool control(analis *);

// Funzione ricorsiva di ricerca di file di tipo csv
// (il parametro di tipo stringa serve per le cartelle contenute nella cartella 'dati')
void searchInFolder(string);

// Funzione principale che permette l'analisi dei file csv e che restituisce nuovi file
// csv con l'elaborazione dei dati in ingresso in base all'indice di soglia
void programma(char *, char *);

#endif /* funzioni_h */
