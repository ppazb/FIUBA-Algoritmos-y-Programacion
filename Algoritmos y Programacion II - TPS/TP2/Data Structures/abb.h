#ifndef ABB_H
#define ABB_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct abb abb_t;
typedef struct nodo nodo_t;
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);
//Crea un ABB, devuelve NULL en caso de fallar, puede recibir una funcion de destruir, para datos que requieran memoria
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);
//Recive una clave y un void* devuelve true si la operacion funciona, false en caso contrario
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
//Recive un arbol y una clave, borra esa clave del ABB y devuelve su dato, devuelve NULL en caso de que la clave no exista
void *abb_borrar(abb_t *arbol, const char *clave);
//Recive un ABB y una clave, devuelve el dato de existir la clave, en caso contrario devuelve NULL
void *abb_obtener(const abb_t *arbol, const char *clave);
//Recive un ABB, una clave, devuelve true si la clave existe, false en caso contrario
bool abb_pertenece(const abb_t *arbol, const char *clave );
//Recive un ABB y devulve su cantidad de elementos
size_t abb_cantidad(abb_t *arbol);
//Recibe un ABB y lo destruye
void abb_destruir(abb_t *arbol);
void nodos_destruir(nodo_t* nodo, abb_t* abb);
//Recive un ABB, una funcion de visitar y un extra, recorre el ABB de manera IN-ORDER, si algun elemento no cumple visitar, corta la iteracion
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);
//Recibe un ABB, una funcion de visitar, un inicio, fin y un extra,recorre el ABB de manera IN-ORDER en el rango indicado, si algun elemento no cumple visitar, corta la iteracion
void abb_in_order_rango(abb_t *arbol,char* inicio, char* fin, bool visitar(const char *, void *, void *), void *extra);
//-----------------------------------------------------------------------------------------------------------------
// ITERADOR EXTERNO
//Recive un ABB y crea un iterador externo para el mismo
typedef struct abb_iter abb_iter_t;
void inicio_in_order(nodo_t* actual, abb_iter_t* iter);
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
//Recive un iterador_abb y hace avanzar el iterador un elemento, el tipo de recorrido es IN-ORDER
bool abb_iter_in_avanzar(abb_iter_t *iter);
//Recibe un iterador_abb y devuelve el elemento actual en la iteracion
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
//Recibe un iterador_abb y lo destruye
void abb_iter_in_destruir(abb_iter_t* iter);
#endif 