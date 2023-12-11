#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "especialidades.h"
#include "mensajes.h"
#define REGULAR "REGULAR"
#define URGENTE "URGENTE"
void borrar_cola(void* cola);
void borrar_heap(void* heap);
int cmp_func(const void* a, const void* b);

typedef struct paciente
{
    char* nombre;
    char* antiguedad;
}paciente_t;

paciente_t* crear_paciente(const char* nombre, const char* antiguedad)
{
    paciente_t* paciente = malloc(sizeof(paciente_t));
    if (!paciente) return NULL;
    paciente->nombre = strdup(nombre);
    paciente->antiguedad = strdup(antiguedad);
    return paciente;
}

void destruir_paciente(paciente_t* paciente)
{
    free(paciente->antiguedad);
    free(paciente->nombre);
    free(paciente);
}

int cmp_func(const void* a, const void* b)
{
    paciente_t* paciente_a = (paciente_t*) a;
    paciente_t* paciente_b = (paciente_t*) b;
    int antiguedad_a = atoi(paciente_a->antiguedad);
    int antiguedad_b = atoi(paciente_b->antiguedad);
    if (antiguedad_a < antiguedad_b) return 1;
    else if (antiguedad_a > antiguedad_b) return -1;
    else return 0;

}
//-----------------------------------------------------------------------------------------------------
struct especialidades{
    hash_t* colas_regulares;
    hash_t* colas_urgentes;
    size_t en_espera;
};


especialidades_t* especialidades_crear(){
    especialidades_t* especialidades = malloc(sizeof(especialidades_t));
    if (!especialidades) return NULL;
    especialidades->colas_urgentes = hash_crear(borrar_cola);
    especialidades->colas_regulares = hash_crear(borrar_heap);
    if (!especialidades->colas_urgentes || !especialidades->colas_regulares) return NULL;
    especialidades->en_espera = 0;
    return especialidades;
}

void especialidades_destruir(especialidades_t* especialidades){
    hash_destruir(especialidades->colas_urgentes);
    hash_destruir(especialidades->colas_regulares);
    free(especialidades);
}

bool especialidades_agregar(especialidades_t* especialidades, char* nombre_especialidad){
    if (hash_guardar(especialidades->colas_regulares, nombre_especialidad, heap_crear(cmp_func)) && hash_guardar(especialidades->colas_urgentes, nombre_especialidad,cola_crear()))return true;
    return false;
}

bool especialidades_borrar(especialidades_t* especialidades, char* nombre_especialidad){
    if (hash_borrar(especialidades->colas_urgentes, nombre_especialidad) && hash_borrar(especialidades->colas_regulares, nombre_especialidad)) return true;
    else return false;
}

bool especialidades_pertenece(especialidades_t* especialidades, char* nombre_especialidad){
    if (hash_pertenece(especialidades->colas_regulares, nombre_especialidad)) return true;
    return false;
}
char* especialidades_siguiente(especialidades_t* especialidades, char* nombre_especialidad){
    cola_t* cola = hash_obtener(especialidades->colas_urgentes, nombre_especialidad);
    heap_t* heap = hash_obtener(especialidades->colas_regulares, nombre_especialidad);
    char* siguiente = NULL;
    if (!cola_esta_vacia(cola)) siguiente = cola_desencolar(cola);
    else if (!heap_esta_vacio(heap)){

        paciente_t* aux = heap_desencolar(heap);
        siguiente = aux->nombre;
        free(aux->antiguedad);
        free(aux);
    }
    else siguiente = NULL;
    return siguiente;

}

bool especialidades_pedir_turno(especialidades_t* especialidades, char* nombre_especialidad, char* nombre_paciente, char* antiguedad, char* urgencia){
    if (strcmp(urgencia, REGULAR) == 0){
        heap_t* heap = hash_obtener(especialidades->colas_regulares, nombre_especialidad);
        if(heap_encolar(heap,crear_paciente(nombre_paciente, antiguedad))) return true;
    } else{
        cola_t* cola = hash_obtener(especialidades->colas_urgentes, nombre_especialidad);
        if(cola_encolar(cola, strdup(nombre_paciente))) return true;
    }
    return false;
}


size_t especialidades_cantidad_en_espera(especialidades_t* especialidades, char* nombre_especialidad){
    return cola_cantidad(hash_obtener(especialidades->colas_urgentes,nombre_especialidad)) + heap_cantidad(hash_obtener(especialidades->colas_regulares, nombre_especialidad));

}



void borrar_paciente(void* paciente)
{
    destruir_paciente( (paciente_t*) paciente);
}

void borrar_cola(void* cola)
{
    cola_destruir((cola_t*) cola, free);
}

void borrar_heap(void* heap)
{
    heap_destruir((heap_t*) heap, borrar_paciente);
}
