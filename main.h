#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct nod1
{
    char *info;
    struct nod1 *sig;
} TNodo;

TNodo *crea_nodo(char dato[]);
void inserta_final(TNodo **cab, char dato[]);
void leer_cadena(FILE *archivo,char nomArch[],char dato[],TNodo **cab);
void imprime_lista(TNodo *cab);
