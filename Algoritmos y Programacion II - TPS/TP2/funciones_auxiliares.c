#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "funciones_auxiliares.h"
#include <string.h>
//---------------------------------CREADOR-------------------------------------------

struct creador
{
    char* campo1;
    char* campo2;
};
creador_t* creador_crear(char** campos)
{
    creador_t* creador = malloc(sizeof(creador_t));
    if (!creador) return NULL;
    creador->campo1 = strndup(campos[0], 100);
    creador->campo2 = strndup(campos[1], 100);
    return creador;
}

void destruir_creador(creador_t* creador)
{
    free(creador->campo1);
    free(creador->campo2);
    free(creador);
}

size_t cantidad_parametros_valida(char** parametros)
{
    size_t contador_parametros = 0;
    for (int i = 0; parametros[i] != NULL; ++i)
    {
        contador_parametros++;
    }
    return contador_parametros;
}


void borrar_creador(void* creador)
{
    destruir_creador( (creador_t*) creador);
}