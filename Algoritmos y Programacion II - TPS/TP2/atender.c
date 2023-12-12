#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "doctores.h"
#include "atender.h"
#include <stdio.h>

void atender_siguiente(char* nombre_doctor, doctores_t* doctores, especialidades_t* especialidades)
{
    char* especialidad = doctores_obtener_especialidad(doctores, nombre_doctor);
    char* paciente = especialidades_siguiente(especialidades, especialidad);
    if (paciente) doctores_se_atendio(doctores,nombre_doctor);
    else{
        printf(SIN_PACIENTES);
        return;
    }
    printf(PACIENTE_ATENDIDO, paciente);
    printf(PACIENTE_ATENDIDO2, especialidades_cantidad_en_espera(especialidades, especialidad),especialidad);
    free(paciente);
}
