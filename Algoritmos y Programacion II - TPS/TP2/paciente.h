#ifndef TP2_PACIENTE_H
#define TP2_PACIENTE_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Data Structures/hash.h"


typedef struct pacientes pacientes_t;
//Crea y retorna una estructura pacientes, si falla devuelve NULL
pacientes_t* crear_pacientes();

//Destruye la estructura pacientes
void destruir_pacientes(pacientes_t* pacientes);

//Recibe el nombre de un paciente y su antiguedad, garda al paciente en la estructura si, en caso de exito devuelve true, caso contrario false
bool pacientes_guardar(pacientes_t* pacientes, const char* nombre_paciente, char* antiguedad);

//Recibe el nombre de un paciente y borra, dicho paciente, en caso de exito devuele true, false en caso contrario
bool pacientes_borrar(pacientes_t* pacientes, const char* nombre_paciente);

//Recibe el nombre de un paciente y devuelve su antiguedad, NULL en caso de no existir
char* pacientes_obtener_antiguedad(pacientes_t* pacientes, char* nombre_paciente);

//Recibe el nombre de un paciente y devuelve true si el paciente pertence a la estructura, false en caso contrario
bool pacientes_pertenece(pacientes_t* pacientes, const char* nombre_paciente);
#endif //TP2_PACIENTE_H
