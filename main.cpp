#include <iostream>
#include <stdlib.h>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

#include <stdio.h>
#include <string.h>
#define k 55
#define N 10
#include "funzioni.h"

void fine(analis* list);
int u = 900;

int main() {
	int scartati[N+1];
	int esatti[N+1];
	int sbagliati[N+1];
    
    int scartatiEsatti[N+1];
    int scartatiSbagliati[N+1];
    
    float accuracy[N+1];
    float precision[N+1];
    float recall[N+1];
    float f1score[N+1];

    for (int i=0; i<N+1; i++) {
        // Fake Positive (FP)
        sbagliati[i] = 0;
        // True Positive (TP)
        esatti[i] = 0;
        scartati[i] = 0;
        // Fake Negative (FN)
        scartatiEsatti[i] = 0;
        // True Negative (TN)
        scartatiSbagliati[i] = 0;
        
        accuracy[i] = 0;
        precision[i] = 0;
        recall[i] = 0;
        f1score[i] = 0;
    }
	string nome_file;
    string nome_html = "table.html";

	cout<<"programma di test\n";
	do {
		
            cout << "\tINserisci nome file: ";
            cin >> nome_file;
            nome_file = "dati\\" + nome_file;
            //    nome_file="test.csv";
            p = fopen(&nome_file[0],"r");
            if(!p)
                cout << "Errore apertura file!";
	}
	while(!p);
			
	cout << "inserisci il file su cui vuoi salvare i dati (nomefile.csv) : ";
    cin >> nome_file;
    nome_file = "risultati\\" + nome_file;
    FILE* csv;
	//csv=fopen(&nome_file[0],"w");
	//csv=stdout;
	csv = fopen(&nome_file[0],"w");
	
//	analis list[150];
	analis app;
	
	if(p) {
	
        f1();
        n = n-2;
        int ii=0;
        for (int i=0;i<u;i++) {
            if(p) {


	/*	memset (list[i].attuale,0.0,n);
		f1(list[i].attuale);
		f1(&list[i]);
		f1(list[i].probabilita);
	*/	
                memset(app.attuale,0.0,n);
                f1(app.attuale);
                f1(&app);
                f1(app.probabilita);
                
                if(!control(&app)) {
                    cout<<"\terrore: "<<i<<endl;
                    u = i-1;
                    u--;
                }
                
                for (int j=0;j<N+1;j++) {
                    if (app.p_max>=(1.0*j)/N) {
                        if (app.corretto)
                            esatti[j]++;
                        else
                            sbagliati[j]++;
                    } else
                        scartati[j]++;
                }
		
		//cout<<"attuale: ";	cout <<list[i].attuale<<endl;
		//cout<<"coretto: ";	cout <<list[i].corretto<<endl;
		//cout<<"numeri: ";	 //for(int j=0;j<n;j++)cout<<" "<<list[i].probabilita[j]<<endl;

            } else {
                u--;
                cout<<"errori I= "<<i<<endl;
            }
        }
    }
	else
        cout<<"errore file non aperto!";
    fclose(p);
    //char s1;

	cout<<"coef;\t"<<"scartati"<<";\t"<<"esatti;"<<"\t"<<"\tsbagliati"<<";"<<"  \t  accuratezza;"<<endl;
		fprintf(csv,"coef;scartati;esatti;sbagliati;accuratezza;\n");
	
    for (int j=0; j<N+1; j++) {

        //cout<<"file generat con suecesso, premere un tasto per chiudere!";
        // Definizione di accuratezza: (TP+TN)/(TP+FP+FP+FN)
        // Da correggere
        float accu = esatti[j]/((esatti[j] + sbagliati[j])*1.0);
        accuracy[j] = accu;
        // Definizione di precisione: TP/(TP+FP)
        float prec = esatti[j]/((esatti[j] + sbagliati[j])*1.0);
        precision[j] = prec;
        // Definizione di recall: TP/(TP+FN)
        // Da definire
        float rec = 0;
        recall[j] = rec;
        // Definizione di f1-score: 2TP/(2TP+FP+FN)
        // Da definire
        float f1 = 0;
        f1score[j] = f1;
        
		//cout<<"accurattezza= "<<accu<<endl;
		
        char str[100];
		printf("%.1f; \t%8d;  \t%6d;   \t %6d; \t\t%.3f;\n",j/(N*1.0),scartati[j],esatti[j],sbagliati[j],accu);
		sprintf(str,"%f;%d;%d;%d;%f;\n",j/(N*1.0),scartati[j],esatti[j],sbagliati[j],accu);
		//cout<<i<<";"<<scartati<<";"<<esatti<<";"<<sbagliati<<";"<<accu<<endl;
        char * pch2;
        char * pch3;
        pch2 = strchr(str,'.');
        pch3 = pch2;
        while (pch2 != NULL) {
            //pch3[0]
            pch2=strchr(pch2+1,'.');
            if(pch3 == NULL)
                break;
             pch3[0] = ',';
             pch3 = pch2;
        }
  
	//cout<<str;

        fprintf(csv,"%s",str);
	
    }
    
    p = fopen(&nome_html[0],"r");
    if(!p)
        cout << "Errore apertura file!";
    cout << "inserisci il file su cui vuoi salvare i dati (nomefile.html) : ";
    cin >> nome_file;
    nome_file = "risultati\\" + nome_file;
    FILE* html;
    //csv=fopen(&nome_file[0],"w");
    //csv=stdout;
    html = fopen(&nome_file[0],"w");
    
    //    analis list[150];
    //analis app;
    
    if(p) {
        arrayDati ad;
        for (int i = 0; i < N+1; i++) {
            dato d = { scartati[i], esatti[i], sbagliati[i], accuracy[i] };
            ad[i] = d;
        }
        //char * result = f2(ad);
        //fprintf(html, result);
    }
    //	fine(list);
	return 0;
}

void fine(analis* list){
		
    string nome_file;
    cout << "inserisci il file su cui vuoi salvare i dati (nomefile.csv) : ";
    cin >> nome_file;
    nome_file = "risultati\\" + nome_file;
    FILE* csv;
	//csv=fopen(&nome_file[0],"w");
	//csv=stdout;
	freopen(&nome_file[0],"w",stdout);
    cout << "coef;"<<"scartati"<<";"<<"esatti"<<";"<<"sbagliati"<<";"<<"accuratezza"<<endl;

	for (float i=0.1; i<1; i+=0.1) {
		int scartati=0;
		int esatti=0;
		int sbagliati=0;
		for (int j=0; j<u; j++) {
            if(list[j].p_max>=i){
                if(list[j].corretto)
                    esatti++;
                else
                    sbagliati++;
            } else
                scartati++;
		}
		//cout<<"cf= "<<i<<"\tscartati= "<<scartati<<"\tesat= "<<esatti<<"\tsbagliat= "<<sbagliati<<endl;
		float accu=esatti/((u-scartati)*1.0);
		//cout<<"accurattezza= "<<accu<<endl;
		
        char str[100];
			
		sprintf(str,"%f;%d;%d;%d;%f\n",i,scartati,esatti,sbagliati,accu);
		//cout<<i<<";"<<scartati<<";"<<esatti<<";"<<sbagliati<<";"<<accu<<endl;
        char * pch2;
        char * pch3;
	
        pch2=strchr(str,'.');
        pch3=pch2;
        while (pch2!=NULL) {
            //pch3[0]
            pch2=strchr(pch2+1,'.');
            if(pch3==NULL)
                break;
            pch3[0]=',';
            pch3=pch2;
        }
        cout << str;
	}
}
