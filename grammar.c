#include "main.h"



int main()
{
    FILE *archivo;
    char nomArch[50],dato[100];
    TNodo *cab = NULL;

    printf("Escribe el nombre del archivo con todo y .txt \n");
    scanf("%s",nomArch);
    
    leer_cadena(archivo,nomArch,dato,&cab);
    imprime_lista(cab);

    return EXIT_SUCCESS;
}

void leer_cadena(FILE *archivo,char nomArch[],char dato[],TNodo **cab)
{
    char parrafo[100];

    archivo = fopen(nomArch, "r");
    if (archivo == NULL) 
    {
        printf("nombre equivocado.\n");
        return EXIT_FAILURE;
    }

    while(fgets(parrafo,sizeof(parrafo),archivo)>0)
    {
            strcpy(dato,parrafo);
            inserta_final(cab,dato);
    }
    fclose(archivo);
}

TNodo *crea_nodo(char dato[])
{
    TNodo *aux;

    aux = (TNodo *)malloc(sizeof(TNodo));
    if (aux != NULL)
    {
        strcpy(aux->info,dato);
        aux->sig = NULL;
    }
    return aux;
}

void inserta_final(TNodo **cab, char dato[])
{
    TNodo *corre;
    if (*cab == NULL)
    {
        *cab = crea_nodo(dato);
    }
    else
    {
        corre = *cab;
        while (corre->sig != NULL)
        {
            corre = corre->sig;
        }
        corre->sig = crea_nodo(dato);
    }
}

 void imprime_lista(TNodo *cab)
{
    while (cab != NULL)
    {
        printf("%s ", cab->info);
        cab = cab->sig;
    }
}

