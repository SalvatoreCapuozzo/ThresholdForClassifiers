int n;
FILE* p;
char ss[1000];

char a;
char * pch;


typedef string arrayHtml[100];

struct analis{
	char attuale[12];
	bool corretto;
	float probabilita[k];
	float p_max;
	
};

struct dato {
    int scartati;
    int esatti;
    int sbagliati;
    float accurat;
};

typedef dato arrayDati[11];

void f1() {

    fscanf(p,"%s",ss);

    pch = strtok(ss,",");
    while (pch != NULL) {
        n++;
        printf("%s\n", pch);
        //sprintf(&s[0],"%s\n",pch);
        pch = strtok(NULL, ",");
    }
			  //n--;
}
/*
char * f2(arrayDati ad) {
    fscanf(p,"%s",ss);
    
    pch = strtok(ss,"CellData");
    int i = 0;
    while (pch != NULL) {
        //printf ("%s",pch);

        arrayHtml[i] = pch;
        i++;
        
        pch = strtok(NULL, ",");
    }
    char * pch2;
    strcpy(pch2, "");
    int j = 0;
    for (int i = 0; i < 100; i++) {
        strcat(pch2, arrayHtml[i]);
        strcat(pch2, ad[j]->scartati);
        i++;
        strcat(pch2, arrayHtml[i]);
        strcat(pch2, ad[j]->esatti);
        i++;
        strcat(pch2, arrayHtml[i]);
        strcat(pch2, ad[j]->sbagliati);
        i++;
        strcat(pch2, arrayHtml[i]);
        strcat(pch2, ad[j]->accurat);
        j++;
    }
    return pch2;
}
*/
bool control(analis* s){
	float a=0;
	s->p_max=0.0;
	for (int i=0; i<n; i++) {
		if (s->probabilita[i] > s->p_max)
            s->p_max = s->probabilita[i];
		a += s->probabilita[i];
	}
	if (a > 0.999 && a < 1.001)
        return true;
	cout << " a= " << a;
	return false;
}

void f1(analis* s) {

    fscanf(p,"%s",ss);
	
    pch = strtok (ss,",");
    while (pch != NULL) {
			   //printf ("%s",pch);
        if (strcmp(s->attuale,pch))
            s->corretto = false;
        else
            s->corretto = true;
        pch = strtok(NULL, ",");
    }
}

void f1(char* s) {

    fscanf(p,"%s",ss);
	
    pch = strtok(ss,",");
    while (pch != NULL) {
			   //printf ("%s",pch);
        sprintf(s,"%s",pch);
		
        pch = strtok(NULL, ",");
    }
}

void f1(float* n) {
    int i=0;
    fscanf(p,"%s",ss);
	
    pch = strtok(ss,",");
    while (pch != NULL) {
			   //printf ("%s\n",pch);
        n[i++] = atof(pch);
        pch = strtok(NULL, ",");
    }
}

