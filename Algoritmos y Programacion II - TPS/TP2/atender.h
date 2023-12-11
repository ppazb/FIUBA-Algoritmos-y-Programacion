#ifndef TP2_ATENDER_H
#define TP2_ATENDER_H
#include "Data Structures/hash.h"
#include "Data Structures/heap.h"
#include "Data Structures/cola.h"
#include "mensajes.h"
#include "Data Structures/abb.h"
#include "especialidades.h"
#include "funciones_auxiliares.h"
/* Recibe un nombre del doctor, YA VALIDO, y atiene al siguiente paciente en la cola que se deba atender, segun su especialidad
 * y la prioridad de este, una vez atendido, lo desencola y muestra por salida estandar quien fue atendido y cuantos hay en espera
 * para dicha especialidad, de no haber pacientes el sistema muestra por salida estandar "no hay pacientes en esepra"*/
void atender_siguiente(char* nombre_doctor, doctores_t* doctores, especialidades_t* especialidades);
#endif //TP2_INFORME_DOCTORES_H
