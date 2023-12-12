#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "paciente.h"

//-----------------------------------------------------------------------------------
struct pacientes{
    hash_t* dict_pacientes;

};

pacientes_t* crear_pacientes(){
    pacientes_t* pacientes = malloc(sizeof(pacientes_t));
    if (!pacientes) return NULL;
    pacientes->dict_pacientes = hash_crear(free);
    return pacientes;
}

void destruir_pacientes(pacientes_t* pacientes){
    hash_destruir(pacientes->dict_pacientes);
    free(pacientes);
}

bool pacientes_guardar(pacientes_t* pacientes, const char* nombre_paciente, char* antiguedad){
    /*paciente_t* nuevo_paciente = crear_paciente(nombre_paciente, antiguedad);
    if(!nuevo_paciente) return false;*/
    if(hash_guardar(pacientes->dict_pacientes, nombre_paciente, strdup(antiguedad))) return true;
    return false;
}

bool pacientes_borrar(pacientes_t* pacientes, const char* nombre_paciente){
    if(!hash_borrar(pacientes->dict_pacientes, nombre_paciente)) return false;
    return true;

}

bool pacientes_pertenece(pacientes_t* pacientes, const char* nombre_paciente){
    return hash_pertenece(pacientes->dict_pacientes, nombre_paciente);
}

char* pacientes_obtener_antiguedad(pacientes_t* pacientes, char* nombre_paciente){
    char* antiguedad = hash_obtener(pacientes->dict_pacientes, nombre_paciente);
    return antiguedad;

}