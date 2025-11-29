#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef BPAS1_H
#define BPAS1_H

typedef enum statut{LORD, CAVALER, AVENTURIER} statut;

typedef struct participant
{
   char* nume;
   int var;
   float exp;
   statut s;
}participant;

char* process_name(char nume_linie[100]);

statut statut_from_string(char* s);

char* statut_to_string(statut s);

participant parse_line(char* linie);

#endif