#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct nod1
{
   char *ruleIdentifier;
   char *productions;
   struct nod1 *sig;
} TNodo;

TNodo *crea_nodo(const char *ruleIdentifier,const char *production);
void inserta_final(TNodo **cab, char *ruleIdentifier,const char *production);
void imprime_lista(TNodo *cab);
void libera_lista(TNodo *cab);
TNodo *crea_lista(FILE *archivo);
TNodo *encuentraNodo(TNodo *cab,const char *ruleIdentifier);
void agregaProduction(TNodo *nodo,const char *production);
void agrega_actualizaNodo(TNodo **cab, char *ruleIdentifier,const char *production);
void dividirlinea(const char *linea,char *ruleIdentifier,char  *production);


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

    cab=crea_lista(archivo);
    imprime_lista(cab);

    return EXIT_SUCCESS;
}

TNodo *crea_nodo(const char *ruleIdentifier,const char *production)
{
    TNodo *nuevoNodo = (TNodo*)malloc(sizeof(TNodo));

    nuevoNodo->ruleIdentifier = strdup(ruleIdentifier);
    nuevoNodo->productions = strdup(production);
    nuevoNodo->sig=NULL;
    return nuevoNodo;
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
        printf("%s \n", actual->productions);
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
        free(actual->productions);
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

TNodo *encuentraNodo(TNodo *cab,const char *ruleIdentifier)
{
    TNodo *actual = cab;

    while(actual != NULL)
    {
        if(strcmp(actual->ruleIdentifier,ruleIdentifier)==0)
        {
            return actual;
        }
       actual=actual->sig; 
    }
    return NULL;
}

void agregaProduction(TNodo *nodo,const char *production)
{
    size_t nuevoTAM=strlen(nodo->productions)+strlen(production)+4;

    nodo->productions=(char *)realloc(nodo->productions,nuevoTAM);

    strcat(nodo->productions," | ");
    strcat(nodo->productions,production);
}

void agrega_actualizaNodo(TNodo **cab, char *ruleIdentifier,const char *production)
{
    TNodo *nodoExistente = encuentraNodo(*cab,ruleIdentifier);

    if(nodoExistente != NULL)
    {
        agregaProduction(nodoExistente,production);
    }
    else
    {
        TNodo *nuevoNodo = crea_nodo(ruleIdentifier,production);
        if(*cab==NULL)
        {
            *cab=nuevoNodo;
        }
        else
        {
            TNodo *temp=*cab;
            while(temp->sig !=NULL)
            {
                temp = temp->sig;
            }
            temp->sig=nuevoNodo;
        }
    }

}