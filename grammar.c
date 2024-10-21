#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct nod1
{
   char *ruleIdentifier;
   char *production;
   struct nod1 *sig;
} TNodo;

TNodo *crea_nodo(const char *ruleIdentifier,const char *production);
void inserta_final(TNodo **cab, char *ruleIdentifier,const char *production);
// int leer_cadena(FILE *archivo,char nomArch[],char dato[],TNodo **cab);
void imprime_lista(TNodo *cab);
void libera_lista(TNodo *cab);
TNodo *crea_lista(FILE *archivo);

int main()
{
    FILE *archivo;
    char nomArch[MAX],dato[MAX];
    TNodo *cab = NULL;

    printf("Escribe el nombre del archivo con todo y .txt \n");
    scanf("%s",nomArch);
    
     archivo = fopen(nomArch, "r");
    if (archivo == NULL) 
    {
        printf("nombre equivocado.\n");
        return EXIT_FAILURE;
    }

    // leer_cadena(archivo,nomArch,dato,&cab);
    cab=crea_lista(archivo);
    imprime_lista(cab);

    return EXIT_SUCCESS;
}

/*int leer_cadena(FILE *archivo,char nomArch[],char *ruleIdentifier,const char *production,TNodo **cab)
{
    char parrafo[MAX];

    archivo = fopen(nomArch, "r");
    if (archivo == NULL) 
    {
        printf("nombre equivocado.\n");
        return EXIT_FAILURE;
    }

    while(fgets(parrafo,sizeof(parrafo),archivo)>0)
    {
            parrafo[strcspn(parrafo,"\n")]='\0';
            strcpy(dato,parrafo);
            inserta_final(cab,ruleIdentifier,production);
    }

    fclose(archivo);
}
*/

TNodo *crea_nodo(const char *ruleIdentifier,const char *production)
{
    TNodo *newNode = (TNodo*)malloc(sizeof(TNodo));

    newNode->ruleIdentifier = strdup(ruleIdentifier);
    newNode->production = strdup(production);
    newNode->sig=NULL;
    return newNode;
}
    

void inserta_final(TNodo **cab, char *ruleIdentifier,const char *production)
{
    TNodo *corre;
    if (*cab == NULL)
    {
        *cab = crea_nodo(ruleIdentifier,production);
    }
    else
    {
        corre = *cab;
        while (corre->sig != NULL)
        {
            corre = corre->sig;
        }
        corre->sig = crea_nodo(ruleIdentifier,production);
    }
}

void imprime_lista(TNodo *cab)
{
    TNodo *actual=cab;
    while (actual != NULL)
    {
        printf("%s \n", actual->ruleIdentifier);
        printf("%s \n", actual->production);
        actual = actual->sig;
    }
}

void libera_lista(TNodo *cab)
{
    TNodo *actual=cab;
    TNodo *sigNodo;

    while(actual!=NULL)
    {
        sigNodo=actual->sig;
        free(actual->ruleIdentifier);
        free(actual->production);
        free(actual);
        actual = sigNodo;
    }
}

TNodo *crea_lista(FILE *archivo)
{
    TNodo *cab=NULL;
    char parrafo[MAX];
    char ruleIdentifier[MAX];
    char production[MAX];

    while(fgets(parrafo,sizeof(parrafo),archivo))
    {
        parrafo[strcspn(parrafo,"\n")]='\0';
        inserta_final(&cab,"",parrafo);
    }
    return cab;
}