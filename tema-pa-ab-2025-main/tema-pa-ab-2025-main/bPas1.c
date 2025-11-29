#include "bPas1.h"

char* process_name(char* nume_linie){
    char* rename=strdup(nume_linie);//fct aloca memorie dinamic pentru un sir de caractere

    for(int i=0; rename[i]; i++){
        if(rename[i]==' ')
            rename[i]='-';
        else if(i==0 || rename[i-1]=='-')
            rename[i]=toupper((unsigned char)rename[i]);
        else
            rename[i]=tolower((unsigned char)rename[i]);
   }
   return rename;
}

statut statut_from_string(char* s){
    char buffer[20];
    int i = 0;

    // Convertim stringul primit la litere mari
    while (s[i] && i < 19) {
        buffer[i] = toupper((unsigned char)s[i]); //se foloseste cu unsigned char pentru a converti in char pozitiv pe care il poate primi toupper
        i++;
    }
    buffer[i] = '\0'; // terminăm stringul

    // Verificăm valoarea
    if (strcmp(buffer, "LORD") == 0)
        return LORD; ///find o functie de tipul statut va rateruna valori intregi 0,1,2 care sunt fiecare asociate unei etichete
    if (strcmp(buffer, "CAVALER") == 0) 
        return CAVALER;
    if (strcmp(buffer, "AVENTURIER") == 0) 
        return AVENTURIER;

    // În caz că e necunoscut
    printf("Statut invalid: %s\n", s);  // am folosit printf în loc de stderr
    return -1; // returnăm o valoare invalidă
}

//trebuie implentata o functie care sa converteasca valorile de tip int in cuvinte care sa fie puse in fisier
char* statut_to_string(statut s){
    if (s == LORD) 
    return "LORD";

    if (s == CAVALER)
     return "CAVALER";

    if (s == AVENTURIER) 
    return "AVENTURIER";

    return "NECUNOSCUT"; // fallback==valoarea de rezerva care este returnata atucni cand nicuuna din celalalte varinate nu este satisfacuta
}

participant parse_line(char* linie){//fct primeste ca parametru o linie citita in main cu fgets care citeste fisierul linie cu linie
    participant p;

    char statut_linie[20], nume_linie[100]; //staut linie este de tip char pentru ca la momentul citirii din fisier
                                           //(acolo unde este intalnit in fct prima data) el este un string iar ulterior
                                           //i se aplica fct statut_from_string care returneaza o valoare de tip statut si o pune in p.s care este tot de tip statut 

    char* token = strtok(linie, ";"); //in linia curenta in care suntem, strtok pune in token tot stringul pana la primul ; inclusiv cu spatii
                                     //la cum sunt organizate datele aici in token ar trb sa fie statutul si toate numele
    if (token == NULL) {
        printf("Lipseste o parte din linie (statut sau nume).\n");
        exit(1);
    }

    sscanf(token, "%s %[^\n]", statut_linie, nume_linie); //fct sparge stringul token in bucati dupa cum ii spun indicatorii 
                                                          //in orima variabuloa va pune ce citeste pana la primul spatiu
                                                          //in adoua va citi tot, inclusiv spatii, pana la new line (imi trb asta pt ca pot fi mai multe nume la un sigur om)
    p.nume = process_name(nume_linie);
    p.s= statut_from_string(statut_linie);//p.s este de tip enum asa ca va trb sa aplicam fact de convertire
                                            // din enum in cuvant in main pe cuvantul care este prelucart in mod curent

    token = strtok(NULL, ";");//se pune NULL pt a relua parcurgerea stringului linie de acolo de unde a ramas 
    p.exp = atof(token);

    token = strtok(NULL, ";");//se pune tot ; pt ca ea nu exista la finalul linie si atunci in token mi
                            // se va pune ultima bucat din string+\n, dar atoi stie sa ignore \n la conversie
    p.var = atoi(token);

    return p;
}
