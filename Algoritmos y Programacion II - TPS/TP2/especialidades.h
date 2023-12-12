#ifndef TP2_ESPECIALIDAD_H
#define TP2_ESPECIALIDAD_H
#include "Data Structures/cola.h"
#include "Data Structures/heap.h"
#include "Data Structures/hash.h"
#include <stdbool.h>
#include <string.h>
typedef struct especialidades especialidades_t;

//Crea y devuelve una estructura especiacilidad inicialmente vacia, devuelve NULL en caso de fallar
especialidades_t* especialidades_crear();

//Reicbe la estructura especialidades y al destruye
void especialidades_destruir(especialidades_t* especialidades);

//Recibe el nombre de una especialidad y la agrega a especialidades
bool especialidades_agregar(especialidades_t* especialidades, char* nombre_especialidad);

//Recibe el nombre de una especialidad y al borra, devuelve true en caso de exito, false en caso contrario
bool especialidades_borrar(especialidades_t* especialidades, char* nombre_especialidad);

//Recibe el nombre de una especialidad y devuelve el nombre del proximo en espera
char* especialidades_siguiente(especialidades_t* especialidades, char* nombre_especialidad);

//Recibe el nombre,antiguedad, urgencia de un paciente, y la especialidad deseada y agrega en espera a dicho paciente.
//Devuelve true en caso de exito, falso en caso contrario
bool especialidades_pedir_turno(especialidades_t* especialidades, char* nombre_especialidad, char* nombre_paciente, char* antiguedad, char* urgencia);

//Recibe el nombe de una especialidad y devuelve la cantidad de pacientes en espera de la misma.
size_t especialidades_cantidad_en_espera(especialidades_t* especialidades, char* nombre_especialidad);

//Recibe el nombre de una especialidad y devuelve true en caso de pertenecer a la estructura, false en caso contrario.
bool especialidades_pertenece(especialidades_t* especialidades, char* nombre_especialidad);

#endif //TP2_ESPECIALIDAD_H
