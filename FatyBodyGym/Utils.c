#include <stdio.h>
#include <stdlib.h>

char* lerTexto(char* shell, int tamanho);

int lerInteiro(char* shell);

void* liberarPonteiro(void* ponteiro);

int lerInteiro(char* shell)
{
    int inteiro;
    printf("%s",shell);
    scanf("%d", &inteiro);
    return inteiro;
}

char* lerTexto(char* shell, int tamanho)
{
    char* texto = (char*) calloc(tamanho, sizeof(char));
    printf("%s: ", shell);
    gets(texto);
    return texto;
}

void* liberarPonteiro(void* ponteiro)
{
    if (ponteiro != NULL)
    {
        free(ponteiro);
        ponteiro = NULL;
    }
    return NULL;
}
