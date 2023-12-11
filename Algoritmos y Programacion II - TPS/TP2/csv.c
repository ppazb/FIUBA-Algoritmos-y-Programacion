#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"
#include "funciones_auxiliares.h"
#define SEPARADOR ','

struct creador
{
	char* campo1;
	char* campo2;
};

static void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}
lista_t* lectura_csv(const char* ruta_csv)
{

	FILE* file = fopen(ruta_csv, "r");
	if (!file) return NULL;
	lista_t* lectura = lista_crear();
	size_t s = 0;
	char* line = NULL;
	while(getline(&line,&s,file) >= 0)
	{
		eliminar_fin_linea(line);
		char** campos = split(line, SEPARADOR);
		creador_t* creador = creador_crear(campos);
		lista_insertar_ultimo(lectura, creador);
        free_strv(campos);

	}
	free(line);
	fclose(file);
	return lectura;
}



