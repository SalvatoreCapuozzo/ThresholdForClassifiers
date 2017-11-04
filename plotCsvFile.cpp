//
//  plotCsvFile.cpp
//  Calcolatore
//
//  Created by Filippo Ferrandino - Salvatore Capuozzo on 04/11/17.
//  Copyright © 2017 Filippo Ferrandino - Salvatore Capuozzo. All rights reserved.
//

#include "plotCsvFile.h"

void plotCsvFile(string pathDir) {
    string dest_file = pathDir;
    unsigned long t = dest_file.find(".csv");
    dest_file[t] = '>';
    dest_file[t+1] = 'd';
    dest_file[t+2] = 'a';
    dest_file[t+3] = 't';
    dest_file.append("aset.png");
    
    /*
     * Plot del grafico rappresentante il dataset in funzione dell'indice di soglia
     * (Esatti, Sbagliati, Scartati Sbagliati, Scartati Esatti)
     */
    Gnuplot plot = Gnuplot();
    
    // Dimensione immagine png di output 1920x1080
    plot.cmd("set terminal png size 1920,1080");
    
    // Nome file di output
    plot.cmd("set output '" + dest_file + "'");
    
    // Segno decimale adottato: Italiano (virgola)
    plot.cmd("set decimalsign locale 'it_IT.UTF-8'");
    
    // Separatore delle celle del file csv: Punto e virgola
    plot.cmd("set datafile separator ';'");
    plot.cmd("set format x '%1.1f'");
    
    // Range dell'ascissa: Tra 1 e 11 con 0.5 di eccesso per ragioni stilistiche
    // (Il valore 0 corrisponde alla riga 0 non valida del file csv)
    plot.cmd("set xrange [0.5:11.5]");
    
    // Range dell'ordinata: Tra 0 e 8000
    plot.cmd("set yrange [0:8000]");
    
    // Valori riportati sull'ordinata: Tra 0 e 800 con risoluzione di 500
    plot.cmd("set ytics '0', '500', '8000'");
    
    // Tipologia di grafico: Istogramma
    plot.cmd("set style data histogram");
    
    // Tipologia di istogramma: In pila
    plot.cmd("set style histogram rowstacked");
    
    // Colorazione dei rettangoli: Riempimento a tinta unita
    plot.cmd("set style fill solid");
    
    // Larghezza dei rettangoli: 0.5
    plot.cmd("set boxwidth 0.5 relative");
    
    // Legenda al di fuori del grafico (per evitare sovrapposizioni)
    plot.cmd("set key outside top right");
    
    // Disegna il grafico delle colonne da 2 a 5 con relativi titoli, colori diversi
    // e con valori dell'ascissa uguali a quelli della colonna 1
    plot.cmd("plot '" + pathDir + "' using 2:xticlabels(1) title 'Esatti' lt rgb 'green', '" + pathDir + "' using 3 title 'Sbagliati' lt rgb 'red', '" + pathDir + "' using 4 title 'Scartati Sbagliati' lt rgb 'cyan', '" + pathDir + "' using 5 title 'Scartati Esatti' lt rgb 'magenta'");
    
    /*
     * Plot del grafico rappresentante i parametri in funzione dell'indice di soglia
     * (Accuratezza, Precisione, Recupero, F1-Score)
     */
    dest_file = pathDir;
    t = dest_file.find(".csv");
    dest_file[t] = '>';
    dest_file[t+1] = 'p';
    dest_file[t+2] = 'a';
    dest_file[t+3] = 'r';
    dest_file.append("ameters.png");
    
    Gnuplot plot2 = Gnuplot();
    plot2.cmd("set terminal png size 1920,1080");
    plot2.cmd("set output '" + dest_file + "'");
    plot2.cmd("set decimalsign locale 'it_IT.UTF-8'");
    plot2.cmd("set datafile separator ';'");
    plot2.cmd("set format x '%1.1f'");
    plot2.cmd("set xrange [0.5:11.5]");
    plot2.cmd("set yrange [0:1.1]");
    plot2.cmd("set ytics '0', '0.1', '1'");
    plot2.cmd("set style data linespoints");
    plot2.cmd("set grid");
    plot2.cmd("set style fill solid");
    plot2.cmd("set key outside top right");
    plot2.cmd("plot '" + pathDir + "' using 6:xticlabels(1) title 'Accuratezza' lt rgb 'green' lw 5 pt 5, '" + pathDir + "' using 7 title 'Precisione' lt rgb 'red' lw 5 pt 5, '" + pathDir + "' using 8 title 'Recupero' lt rgb 'cyan' lw 5 pt 5, '" + pathDir + "' using 9 title 'F1-Score' lt rgb 'magenta' lw 5 pt 5");
}
