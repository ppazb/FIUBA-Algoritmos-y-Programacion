#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "doctores.h"
//  Doctor ////////////////////////////////////////////////////////////////

typedef struct datos_doc{
    char* especialidad;
    size_t cant_atendidos;
} datos_doc_t;

datos_doc_t* crear_doctor(char* especialidad){
    datos_doc_t* doctor = malloc(sizeof(datos_doc_t));
    if (!doctor) return NULL;
    doctor->especialidad = strdup(especialidad);
    doctor->cant_atendidos = 0;
    return doctor;
}

void destruir_datos_doc (datos_doc_t* datos_doc){
    free(datos_doc->especialidad);
    free(datos_doc);
}
void _destruir_datos_doc(void* datos_doc);

// /////////////////////////////////////////////////////////////////

struct doctores{
	abb_t * listado_doctores;
};



doctores_t * doctores_crear(void){
	doctores_t * doctores = malloc(sizeof(doctores_t));
	if(!doctores) return NULL;
	doctores->listado_doctores = abb_crear(strcmp, _destruir_datos_doc);
	if(!doctores->listado_doctores){
		free(doctores);
		return NULL;
	}
	return doctores;
}


bool doctor_agregar (doctores_t * doctores, char * nombre, char* especialidad){
	datos_doc_t * datos_doc = crear_doctor(especialidad);
	if (!datos_doc) return false;
	if(!abb_guardar(doctores->listado_doctores, nombre, datos_doc)){
	    destruir_datos_doc(datos_doc);
        return false;
	}
	return true;
}


bool doctor_borrar (doctores_t * doctores, char* nombre){
 	if(!abb_borrar(doctores->listado_doctores, nombre)) return false;
 	return true;
}

char* doctores_obtener_especialidad(doctores_t * doctores, char* nombre){
	datos_doc_t* datos_doc = abb_obtener(doctores->listado_doctores,nombre);
	if(!datos_doc) return NULL;
	return datos_doc->especialidad;
}

bool doctores_pertenece(doctores_t* doctores, char* nombre_doctor){
    if (abb_pertenece(doctores->listado_doctores, nombre_doctor)) return true;
    return false;
}

size_t doctores_ver_atendidos(doctores_t* doctores, char* nombre_doctor){
    datos_doc_t* datos_doc = abb_obtener(doctores->listado_doctores, nombre_doctor);
    if (!datos_doc) return 0;
    return datos_doc->cant_atendidos;
}

size_t doctores_se_atendio(doctores_t* doctores, char* nombre_doctor){
    datos_doc_t* datos_doc = abb_obtener(doctores->listado_doctores, nombre_doctor);
    if (!datos_doc) return 0;
    datos_doc->cant_atendidos++;
    return datos_doc->cant_atendidos;

}


void _destruir_datos_doc(void* datos_doc){
    destruir_datos_doc(datos_doc);
}

//Recive doctores, una funcion de visitar, los nombres entre los cuales recorrer y un extra, recorre los doctores en orden alfabetico, si algun elemento no cumple visitar, corta la iteracion
//De recibir una cadena vacia por rango, se recorre desde el principio y/o hasta el fin.
void recorrer_doctores(doctores_t * doctores, char* inicio, char* fin, bool visitar(const char *, void *, void *), void *extra){
	abb_in_order_rango(doctores->listado_doctores, inicio, fin, visitar, extra);

}

void destruir_doctores(doctores_t *doctores){
	abb_destruir(doctores->listado_doctores);
	free(doctores);
}

bool guardar_visitados(const char * clave , void * dato, void * lista){
	lista_t * lista_docs = (lista_t*) lista;
	datos_doc_t* datos = (datos_doc_t*) dato;

	hash_t * doctor_agregar = hash_crear(NULL);
	if(!doctor_agregar) return false;

	hash_guardar(doctor_agregar, "nombre", (void*)clave);
	hash_guardar(doctor_agregar, "especialidad", (void*)datos->especialidad);
	hash_guardar(doctor_agregar, "atendidos", (void*)&datos->cant_atendidos);
	lista_insertar_ultimo(lista_docs,doctor_agregar);
	return true;
}

