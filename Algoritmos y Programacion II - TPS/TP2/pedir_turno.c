#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "pedir_turno.h"
#include "mensajes.h"
#include "funciones_auxiliares.h"
#include "paciente.h"
#include <stdio.h>
#include <string.h>


void procesar_turno(char* nombre, char* especialidad, char* urgencia, pacientes_t* pacientes, especialidades_t* especialidades)
{
    especialidades_pedir_turno(especialidades,especialidad,nombre, pacientes_obtener_antiguedad(pacientes, nombre),urgencia);
    printf(PACIENTE_ENCOLADO,nombre);
    printf(CANT_PACIENTES_ENCOLADOS, especialidades_cantidad_en_espera(especialidades,especialidad),especialidad);
    return;
}
