#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* --------------------------------LISTA--------------------------------*/
typedef struct lista lista_t;
// Crea una lista.
// Post: devuelve una nueva lista vacía. En caso de no poder crearla devuelve NULL
lista_t *lista_crear(void);
//Devuelve verdadero si la lista esta vacia, falso de lo contrario.
//Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

//Inserta el dato en la primera posicion de la lista y devuelve true, de haber un error devuelve false.
//Pre: la lista fue creada.
//Post: se inserto el elemento al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

//Inserta el dato en la ultima posicion de la lista y devuelve true, de haber un error devuelve false.
//Pre: la lista fue creada.
//Post: se inserto el elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//Borra el primer dato de la lista y devuelve el valor. De estar vacia devuelve NULL.
//Pre: la lista fue creada.
//Post: se devolvió el primer elemento de la cola, cuando no está vacía y lo elimina de la lista.
void *lista_borrar_primero(lista_t *lista);

//Devuelve el primer dato de la lista. De estar vacia devuelve NULL.
//Pre: la lista fue creada.
//Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

//Devuelve el primer dato de la lista. De estar vacia devuelve NULL.
//Pre: la lista fue creada.
//Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);


//Devuelve el largo de la lista.
//Pre: la lista fue creada.
//Post: se devolvió el largo de la lista.
size_t lista_largo(const lista_t *lista);

//Destruye la lista.
//Pre: la lista fue creada.
//Post: se destruye la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* --------------------------------ITERADOR EXTERNO--------------------------------*/

typedef struct lista_iter lista_iter_t;

//Pre: la lista existe.
//Post: se crea un iterador de la lista ubicado en la primera posicion. De no poderse, se devuelve NULL
lista_iter_t *lista_iter_crear(lista_t *lista);

//avanza una posicion en el iterador, devuelve true una vez realizado, false de no poder.
//Pre:existe el iterador.
//Post: avanza una posicion. De no poder devuelve false.
bool lista_iter_avanzar(lista_iter_t *iter);

//Pre: existe el iterador.
//Post: Devuelve el valor actual donde se encuentra el iterador. De no haber actual, devuelve NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Pre: existe el iterador.
//Post: devuelve true en caso de haber llegado al final, false de lo contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

//Pre:existe el iterador.
//Post:se destruye el iterador.
void lista_iter_destruir(lista_iter_t *iter);

//Pre: existe el iterador.
//PostL se inserta el dato en la posicion actual en la que se encuentre y devuelve true. De no poder devuelve false.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra el elemento del iterador.
//Pre: el iterador existe.
/*Post: el elemento es eliminado y se devuelve su valor. En caso de no poder realizarlo, ya sea por 
estar vacia o en la posicion final devuelve NULL*/
void *lista_iter_borrar(lista_iter_t *iter);

/* --------------------------------ITERADOR INTERNO--------------------------------*/
//Visita todas las posiciones de la lista y aplica visitar al dato, en caso de que no se aplique(false), se corta la iteracion.
//Pre:la lista existe.
//post: se modificaron los datos hasta el corte control.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);
#endif
