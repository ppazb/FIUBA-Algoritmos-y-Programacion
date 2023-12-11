#include "Data Structures/abb.h"
#include "Data Structures/lista.h"
#include "Data Structures/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct doctores doctores_t;

//Crea la estructura doctores, en caso de no poder devuelve NULL.
doctores_t * doctores_crear(void);

//Recibe un doctor y su especialidad y se lo agrega a la estructura doctores. Devuelve true, o false de no poder agregarlo.
bool doctor_agregar (doctores_t * doctores, char * nombre, char* especialidad);

//Recibe la estructura doctores y el nombre de un doctor: borra al doctor recibido de doctores. De no poder realizarse devuelve false.
bool doctor_borrar (doctores_t * doctores, char* nombre);

//Recibe la estructura doctores y el nombre del doctor y devuelve su especialiad.
char * doctores_obtener_especialidad(doctores_t * doctores, char* nombre);

//Recibe la estructura doctores y el nombre del doctor y devuelve la cantidad de pacientes que atendio.
size_t doctor_cant_atendidos(doctores_t *doctores, char *nombre);

//Recive doctores, una funcion de visitar, los nombres entre los cuales recorrer y un extra y recorre los doctores en orden alfabetico, si algun elemento no cumple visitar, corta la iteracion
//De recibir una cadena vacia por rango, se recorre desde el principio y/o hasta el fin.
void recorrer_doctores(doctores_t * doctores, char* inicio, char* fin, bool visitar(const char *, void *, void *), void*extra);

//Funcion visitar opcional. Recibe la clave, el dato y una una lista provista por extra. Devuelve una lista de diccionarios (lista de hash) con los doctores recorridos
//El diccionario presente en cada lista contiene tres claves "nombre", "especialidad" y "atendidos", con sus respectivos datos de cada doctor.
bool guardar_visitados(const char * clave , void * dato, void * lista);

//Devuleve true, si el doctor pertenece a la estructura, falso en caso contrario
bool doctores_pertenece(doctores_t* doctores, char* nombre_doctor);

//Recibe el nombre de un doctor y devuelve su cantidad de atendidos
size_t doctores_ver_atendidos(doctores_t* doctores, char * nombre_doctor);

//Recibe el nombre de un doctor y suma en 1 la cantidad de atendidos, devuelve la cantidad de atendidos modificada
size_t doctores_se_atendio(doctores_t* doctores, char * nombre_doctor);

//Recibe la estructura doctores y la destruye.
void destruir_doctores(doctores_t *doctores);