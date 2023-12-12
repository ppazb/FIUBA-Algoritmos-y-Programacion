#ifndef TP2_FUNCIONES_AUXILIARES_H
#define TP2_FUNCIONES_AUXILIARES_H
#include "Data Structures/heap.h"
#include "Data Structures/cola.h"
#include "csv.h"

void borrar_creador(void* creador);
//---------------------------------CREADOR-------------------------------------------
typedef struct creador creador_t;
//crea una estructura auxiliar para utilizar en carga de csv devuelve un creador y NULL en caso de error
creador_t* creador_crear(char** campos);
//destruye el creador
void destruir_creador(creador_t* creador);

//-----------------------------COMPROBACION CANTIDAD DE  PARAMETROS VALIDA----------
size_t cantidad_parametros_valida(char** parametros);


#endif //TP2_FUNCIONES_AUXILIARES_H
