#ifndef TP2_PEDIR_TURNO_H
#define TP2_PEDIR_TURNO_H
#include "Data Structures/hash.h"
#include "Data Structures/abb.h"
#include "paciente.h"
#include "especialidades.h"
/* Recibe el nombre de un paciente, YA VALIDO, una especialidad, YA VALIDA, y su urgencia y encola a este en la especialidad y urgencia
 * correcta, luego de esto muestra quien fue el que pidio el turno por salida estandar y la cantidad de pacientes a la esperar para dicha
 * especicalidad*/
void procesar_turno(char* nombre, char* especialidad, char* urgencia, pacientes_t* pacientes, especialidades_t* especilidades);


#endif //TP2_PEDIR_TURNO_H
