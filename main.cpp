#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

#include <string.h>
#define k 55
#define N 10
#include "funzioni.h"

void programmma(char* argv);

int main() {
    DIR *dirp = NULL;

    struct dirent *dp;

    //dirp = opendir("dati\\");
    dirp = opendir("/Users/salvatorecapuozzo/ThresholdForClassifiers/dati");
    int p=0;
    while (dirp) {
        if ((dp = readdir(dirp)) != NULL) {
            p++;
            puts(dp->d_name);
            if(p>2)
                programmma(dp->d_name);
        } else {
            closedir(dirp);
            dirp = NULL;
        }
    }
    return 0;
}

void fine(analis* list);
int u=5000;

void programmma(char* argv) {
    n = 0;
	int scartati[N+1];
	int scartatiEsatti[N+1];
    int scartatiSbagliati[N+1];
	int esatti[N+1];
	int sbagliati[N+1];

    for (int i=0;i<N+1;i++) {
        sbagliati[i]=esatti[i]=scartati[i]=scartatiEsatti[i]=scartatiSbagliati[i]=0;
    }
    string nome_file;

//	cout<<"programma di test\n";
	
	
    nome_file=argv;
    
    // Salvatore
    nome_file = "/Users/salvatorecapuozzo/ThresholdForClassifiers/dati/" + nome_file;
    // Filippo
    //nome_file="dati\\" + nome_file;
    
    cout<<"\nFile: "<<nome_file;

    p=fopen(&nome_file[0],"r");
    while(!p) {
        
        cout<<"\nInserisci nome file: ";
        cin>>nome_file;

        //nome_file=argv[1];
        
        // Salvatore
        nome_file = "/Users/salvatorecapuozzo/ThresholdForClassifiers/dati/" + nome_file;
        // Filippo
        //nome_file="dati\\" + nome_file;
        
        cout<<"\nFile: "<<nome_file;
    //    nome_file="test.csv";
        //cin>>nome_file;
        p=fopen(&nome_file[0],"r");
        if(!p)
            cout<<"\nErrore apertura file!";
	}

			
	//cout<<"inserisci il file su cui vuoi salvare i dati (nomefile.csv) : ";
		//	cin>>nome_file;

	nome_file=argv;
	
    // Salvatore
    nome_file = "/Users/salvatorecapuozzo/ThresholdForClassifiers/risultati/Risultati_" + nome_file;
    // Filippo
    //nome_file="risultati\\Risuttati_" + nome_file;
    
    //cout<<nome_file;
    
    FILE* csv;
	//csv=fopen(&nome_file[0],"w");
	//csv=stdout;
	csv=fopen(&nome_file[0],"w");
	
//	analis list[150];
	analis app;
	
	if(p) {
	
        f1();
        n=n-2;
        int ii=0;
        for(int i=0;i<u;i++) {
            if(p) {
                memset (app.attuale,0.0,n);
                f1(app.attuale);
                f1(&app);
                f1(app.probabilita);
                
                if(!control(&app)){
                    cout<<"\terrore: "<<i<<endl;
                    u=i-1;
                    u--;
                }
                for (int j=0;j<N+1;j++){
                    if(app.p_max>=(1.0*j)/N){
                        if(app.corretto)
                            esatti[j]++;
                        else
                            sbagliati[j]++;
                    } else {
                        scartati[j]++;
                        if(app.corretto)
                            scartatiEsatti[j]++;
                        else {
                            scartatiSbagliati[j]++;
                        }
                    }
                    
                    //cout<<"attuale: ";    cout <<list[i].attuale<<endl;
                    //cout<<"coretto: ";    cout <<list[i].corretto<<endl;
                    //cout<<"numeri: ";     //for(int j=0;j<n;j++)cout<<" "<<list[i].probabilita[j]<<endl;

                }
            
            } else{
                u--;
                cout<<"errori I= "<<i<<endl;
            }

    }

    int i=0;

        while(!feof(p)){
            i++;
            memset (app.probabilita,0.0,n);
            f1(app.attuale);
            f1(&app);
            f1(app.probabilita);
            
            if(!control(&app)){
                cout<<"\nErrore ! i= "<<i<<"\n";
            }
            for(int j=0;j<N+1;j++){
                if(app.p_max>=(1.0*j)/N){
                    if(app.corretto)
                        esatti[j]++;
                    else
                        sbagliati[j]++;
                }
                else {
                    if(app.corretto)
                        scartatiEsatti[j]++;
                    else
                        scartatiSbagliati[j]++;
                }
            }

        }

    }
        //else cout<<"errore file non aperto!";
    fclose(p);

    char s1;


        cout<<"\ncoef;\t"<<"scEsatti"<<";\t"<<"scSbagliati"<<";\t\t"<<"esatti;"<<"\t"<<"\tsbagliati"<<";"<<"\taccuratezza"<<";"<<"\tprecisione;"<<"\trecall;"<<"\tf1Score;"<<endl;
    fprintf(csv,"coef;scEsatti;scSbagliati;esatti;sbagliati;accuratezza;precisione;recall;f1Score;\n");
    
    for(int j=0;j<N+1;j++){

    //cout<<"file generat con suecesso, premere un tasto per chiudere!";
        float accuratezza = (esatti[j]+scartatiSbagliati[j])*1.0/(esatti[j]+sbagliati[j]+scartatiEsatti[j]+scartatiSbagliati[j])*1.0;
        float precisione=esatti[j]/((esatti[j]+sbagliati[j])*1.0);
        
        float recall = esatti[j]/(esatti[j]+scartatiEsatti[j]*1.0);
        float f1score = 2*precisione*recall/(precisione+recall);
            //cout<<"precisionerattezza= "<<precisione<<endl;
        
        char str[100];
        printf("%.1f; \t%8d;  \t%11d;    \t  %3d;  \t %8d;  \t\t %.3f; \t\t %.3f; \t%.3f; \t%.3f;\n",j/(N*1.0),scartatiEsatti[j],scartatiSbagliati[j],esatti[j],sbagliati[j],accuratezza,precisione, recall, f1score);
        sprintf(str,"%f;%d;%d;%d;%d;%f;%f;%f;%f;\n",j/(N*1.0),scartatiEsatti[j],scartatiSbagliati[j],esatti[j],sbagliati[j],accuratezza,precisione, recall, f1score);
            //cout<<i<<";"<<scartati<<";"<<esatti<<";"<<sbagliati<<";"<<precisione<<endl;
        char * pch2;
        char * pch3;
        pch2=strchr(str,'.');
        pch3=pch2;
        while (pch2!=NULL) {
        //pch3[0]
            pch2=strchr(pch2+1,'.');
            if(pch3==NULL)break;
            pch3[0]=',';
            pch3=pch2;
        }
      
        //cout<<str;

        fprintf(csv,"%s",str);
        
    }
    //    fine(list);

}
    /*
    void fine(analis* list){
        string nome_file;
        cout<<"inserisci il file su cui vuoi salvare i dati (nomefile.csv) : ";
        cin>>nome_file;
        nome_file="risultati\\" + nome_file;
        FILE* csv;
        //csv=fopen(&nome_file[0],"w");
        //csv=stdout;
        freopen(&nome_file[0],"w",stdout);
            cout<<"coef;"<<"scartati"<<";"<<"esatti"<<";"<<"sbagliati"<<";"<<"precisioneratezza"<<endl;

     
     
        for(float i=0.1;i<1;i+=0.1){
            int scartati=0;
            int esatti=0;
            int sbagliati=0;
     
            for(int j=0;j<u;j++){
            if(list[j].p_max>=i){
                if(list[j].corretto)esatti++;
                else sbagliati++;
            }
            else scartati++;
            }
            //cout<<"cf= "<<i<<"\tscartati= "<<scartati<<"\tesat= "<<esatti<<"\tsbagliat= "<<sbagliati<<endl;
            float precisione=esatti/((u-scartati)*1.0);
            //cout<<"precisionerattezza= "<<precisione<<endl;
     
                char str[100];
     
            sprintf(str,"%f;%d;%d;%d;%f\n",i,scartati,esatti,sbagliati,precisione);
            //cout<<i<<";"<<scartati<<";"<<esatti<<";"<<sbagliati<<";"<<precisione<<endl;
        char * pch2;
        char * pch3;

     
     
     
        pch2=strchr(str,'.');
        pch3=pch2;
      while (pch2!=NULL)
      {
        //pch3[0]
        pch2=strchr(pch2+1,'.');
        if(pch3==NULL)break;
         pch3[0]=',';
         pch3=pch2;
      }
        cout<<str;
     
        }
     
    }
    */
