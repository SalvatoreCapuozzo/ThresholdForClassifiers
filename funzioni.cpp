//
//  funzioni.cpp
//  Calcolatore
//
//  Created by Filippo Ferrandino - Salvatore Capuozzo on 04/11/17.
//  Copyright © 2017 Filippo Ferrandino - Salvatore Capuozzo. All rights reserved.
//

#include "funzioni.h"

// Numero delle colonne del file csv
int n;

FILE* p;
char ss[1000];

int u = 5000;

/*
 * Tipologia del file csv in ingresso:
 * - type == 0 => tipologia Comma And Tabs (C&T):
 *      dopo la stringa 'Actual' è presente una virgola
 *      dopo le stringhe dei risultati è presente una tab
 * - type == 1 => tipologia Tab And Spaces (T&C):
 *      dopo la stringa 'Actual' è presenta una tab
 *      dopo le stringhe dei risultati è presente una virgola
 */
int type;

char * pch;

void f1() {
    fscanf(p,"%s",ss);
    if (ss[6] == ',') {
        type = 0;
    } else {
        type = 1;
    }
    
    if (type == 1) {
        fscanf(p,"%[^\n]",ss);

        cout << "T&C csv" << endl;
        
        pch = strtok(ss,",");
        
        while (pch != NULL) {
            n++;
            pch = strtok(NULL, ",");
        }
    } else {
        cout << "C&T csv" << endl;
        pch = strtok(ss,",");
        while (pch != NULL) {
            n++;
            pch = strtok(NULL, ",");
        }
    }
}

bool control(analis* s) {
    float a=0;
    s->p_max=0.0;
    int j;
    if (type == 0) {
        j = 0;
    } else {
        j = 1;
    }
    for (int i=j; i<n; i++) {
        if (s->probabilita[i] > s->p_max)
            s->p_max = s->probabilita[i];
        a += s->probabilita[i];
        //cout << "Iterazione " << i << ": " << s->probabilita[i] << "\n";
    }
    if (a > 0.999 && a < 1.001)
        return true;
    //cout << "Valore totale: " << a << endl;
    return false;
}

void f1(char* s) {
    fscanf(p,"%s",ss);
    
    if (type == 1) {
        int found = 0;
        for (int i = 0; i < 12 && found == 0; i++) {
            if (ss[i] == ',') {
                found = 1;
                ss[i] = '\0';
            }
        }
    }
    
    pch = strtok(ss,",");

    while (pch != NULL) {
        sprintf(s,"%s",pch);
        
        pch = strtok(NULL, ",");
    }
}

void f1(analis* s) {
    fscanf(p,"%s",ss);
    
    pch = strtok (ss,",");
    int i=0;
    while (pch != NULL) {
        // Verifica del contenuto puntato da pch
        // (Se type == 0, allora f1() ha già compiuto il suo lavoro correttamente
        // e pch[1] non sarà mai '.')
        // (Se type == 1, allora deve essere chiamata la funzione f1(float *, int)
        // prima di saltare all'elemento successivo di ss)
        if (pch[1] != '.') {
            if (strcmp(s->attuale,pch))
                s->corretto = false;
            else
                s->corretto = true;
        } else {
            f1(s->probabilita, i);
            i++;
        }
        pch = strtok(NULL, ",");
    }
}

void f1(float* n, int i) {
    while (pch != NULL) {
        n[i] = atof(pch);
        i++;
        pch = strtok(NULL, ",");
    }
}

void f1(float* n) {
    int i=0;
    fscanf(p,"%s",ss);
    
    pch = strtok(ss,",");
    while (pch != NULL) {
        n[i] = atof(pch);
        i++;
        pch = strtok(NULL, ",");
    }
}

void searchInFolder(string folder) {
    DIR *dirp = NULL;
    
    struct dirent *dp;
    
    // Filippo
    //dirp = opendir("dati\\");
    // Salvatore
    cout << "Folder name: " << folder << endl;
    string directory = "/Users/salvatorecapuozzo/ThresholdForClassifiers/dati/" + folder;
    dirp = opendir(&directory[0]);
    int p = 0;
    while (dirp) {
        if ((dp = readdir(dirp)) != NULL) {
            p++;
            printf("%d = ", dp->d_type);
            puts(dp -> d_name);
            if (p > 2) {
                string name = dp->d_name;
                if (strcmp(dp->d_name, ".DS_Store") && dp->d_type != 4) {
                    // Prelievo dei file nella cartella 'dati' con esecuzione del programma
                    if (strcmp(&folder[0], "")) {
                        string fileDir = directory + "/" + dp->d_name;
                        programma(dp->d_name, &fileDir[0]);
                    } else {
                        string fileDir = directory + dp->d_name;
                        programma(dp->d_name, &fileDir[0]);
                    }
                } else if (dp->d_type == 4) {
                    // Ricorsività della funzione abilitata nel caso in cui il file
                    // trovato sia un'altra directory
                    if (strcmp(&folder[0], "")) {
                        string fullDir = directory + "/" + dp->d_name;
                        string dir = fullDir.substr(54);
                        searchInFolder(&dir[0]);
                    } else {
                        string fullDir = directory + dp->d_name;
                        string dir = fullDir.substr(54);
                        searchInFolder(&dir[0]);
                    }
                }
            }
        } else {
            closedir(dirp);
            dirp = NULL;
        }
    }
}

void programma(char* nomeFile, char * path) {
    string arg = (string) nomeFile;
    cout << arg;
    
    n = 0;
    
    // True Positive (TP)
    int esatti[N+1];
    // Fake Positive (FP)
    int sbagliati[N+1];
    // Fake Negative (FN)
    int scartatiEsatti[N+1];
    // True Negative (TN)
    int scartatiSbagliati[N+1];
    
    // Inizializzazione degli array
    for (int i=0;i<N+1;i++) {
        sbagliati[i]=esatti[i]=scartatiEsatti[i]=scartatiSbagliati[i]=0;
    }
    
    string nome_file;
    nome_file=nomeFile;
    
    // Concatenazione nome file con la directory associata
    // Salvatore
    string pathDir = path;
    string partialPath = pathDir.substr(54);
    nome_file = "/Users/salvatorecapuozzo/ThresholdForClassifiers/dati/" + partialPath;
    // Filippo
    //nome_file="dati\\" + nome_file;
    
    //nome_file = nome_file.substr(54);
    cout << "\nFile: " << nome_file << endl;
    
    p = fopen(&nome_file[0],"r");
    
    // Ciclo a cui si ha accesso solo in caso di errore
    while (!p) {
        cout<<"\nInserisci nome file: ";
        cin>>nome_file;
        
        // Concatenazione nome file con la directory associata
        // Salvatore
        nome_file = "/Users/salvatorecapuozzo/ThresholdForClassifiers/dati/" + nome_file;
        // Filippo
        //nome_file="dati\\" + nome_file;
        
        cout << "\nFile: " << nome_file << endl;
        
        p = fopen(&nome_file[0],"r");
        if (!p)
            cout << "\nErrore apertura file!";
    }
    
    nome_file=nomeFile;
    
    // Creazione nuovo file di risultati associato al file in input
    // Salvatore
    string subpath = pathDir.substr(54);
    cout << subpath << endl;
    replace(subpath.begin(), subpath.end(), '/', '>');
    
    pathDir = "/Users/salvatorecapuozzo/ThresholdForClassifiers/risultati/" + subpath;
    cout << pathDir << endl;
    //nome_file = "/Users/salvatorecapuozzo/ThresholdForClassifiers/risultati/Risultati_" + nome_file;
    // Filippo
    //nome_file="risultati\\Risuttati_" + nome_file;
    
    FILE* csv;
    csv = fopen(&pathDir[0],"w");
    
    analis app;
    
    if(p) {
        f1();
        if (type == 0) {
            n = n - 2;
        } else {
            n = n - 1;
        }
        for (int i=0; i<u; i++) {
            if (p) {
                // Liberazione della memoria con lo spazio necessario
                memset(app.attuale,0.0,n);
                // Registrazione del nome del vero pacchetto
                f1(app.attuale);
                // Verifica della correttezza della previsione
                f1(&app);
                // Salvataggio di tutti i vettori di indici di probabilità
                if (type != 1) {
                    f1(app.probabilita);
                }
                if (!control(&app)) {
                    //cout<<"\ni= "<<i<<"\n----------\n";
                    u = i - 1;
                    u--;
                }
                for (int j=0; j<N+1; j++) {
                    if (app.p_max >= (1.0*j)/N) {
                        if (app.corretto) {
                            esatti[j]++;
                        } else {
                            sbagliati[j]++;
                        }
                    } else {
                        if (app.corretto) {
                            scartatiEsatti[j]++;
                        } else {
                            scartatiSbagliati[j]++;
                        }
                    }
                }
            } else {
                u--;
                cout << "errori I= " << i << endl;
            }
        }
        int i = 0;
        while (!feof(p)) {
            i++;
            memset(app.probabilita,0.0,n);
            f1(app.attuale);
            f1(&app);
            if (type != 1) {
                f1(app.probabilita);
            }
            if (!control(&app)) {
                //cout<<"\ni= "<<i<<"\n----------\n";
            }
            
            for (int j=0; j<N+1; j++) {
                if (app.p_max >= (1.0*j)/N) {
                    if (app.corretto)
                        esatti[j]++;
                    else
                        sbagliati[j]++;
                }
                else {
                    if (app.corretto)
                        scartatiEsatti[j]++;
                    else
                        scartatiSbagliati[j]++;
                }
            }
        }
    }
    //else cout<<"errore file non aperto!";
    fclose(p);
    
    cout<<"\ncoef;\t"<<"  esatti;"<<"\t"<<"  sbagliati;"<<" scSbagliati;"<<"\t  scEsatti;"<<"\taccuratezza;"<<"\t precisione;"<<"\t  recupero;"<<"\tf1Score;"<<endl;
    fprintf(csv,"coef;esatti;sbagliati;scSbagliati;scEsatti;accuratezza;precisione;recupero;f1Score;\n");
    
    for (int j=0; j<N+1; j++) {
        // Definizione di accuratezza: (TP+TN)/(TP+FP+FP+FN)
        float accuratezza = (esatti[j]+scartatiSbagliati[j])*1.0/(esatti[j]+sbagliati[j]+scartatiEsatti[j]+scartatiSbagliati[j])*1.0;
        
        // Definizione di precisione: TP/(TP+FP)
        float precisione = esatti[j]/((esatti[j]+sbagliati[j])*1.0);
        
        // Definizione di recupero: TP/(TP+FN)
        float recupero = esatti[j]/(esatti[j]+scartatiEsatti[j]*1.0);
        
        // Definizione di f1-score: 2TP/(2TP+FP+FN)
        float f1score = 2*precisione*recupero/(precisione+recupero);
        
        char str[100];
        printf("%.1f; \t%8d;  \t%11d;    \t%6d;  \t %4d;  \t\t %.3f; \t\t %.3f; \t\t%.3f; \t  %.3f;\n",j/(N*1.0),esatti[j],sbagliati[j],scartatiSbagliati[j],scartatiEsatti[j],accuratezza,precisione, recupero, f1score);
        sprintf(str,"%f;%d;%d;%d;%d;%f;%f;%f;%f;\n",j/(N*1.0),esatti[j],sbagliati[j],scartatiSbagliati[j],scartatiEsatti[j],accuratezza,precisione, recupero, f1score);
        char * pch2;
        char * pch3;
        pch2 = strchr(str,'.');
        pch3 = pch2;
        while (pch2!=NULL) {
            pch2 = strchr(pch2+1,'.');
            if(pch3 == NULL)
                break;
            pch3[0] = ',';
            pch3 = pch2;
        }
        
        fprintf(csv,"%s",str);
    }
    fclose(csv);
    
    // Chiamata della funzione di creazione dei grafici con i dati del file csv salvato
    plotCsvFile(pathDir);
}
