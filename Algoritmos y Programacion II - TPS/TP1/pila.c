#include "pila.h"

#include <stdlib.h>
#define CAPACIDAD_INICIAL 10
#define REDIMENCIONAR 2
bool redimensionar_pila(pila_t *pila,size_t nueva_capacidad);

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){

	pila_t *pila = malloc(sizeof(pila_t));

	if (pila == NULL){
		return NULL;
	}
	
	pila-> datos = malloc(sizeof(void*) * CAPACIDAD_INICIAL);
	if (pila->datos == NULL){
		free(pila); 
		return NULL;
	}

	pila -> cantidad = 0; 
	pila -> capacidad = CAPACIDAD_INICIAL;
	return pila;
}

void pila_destruir(pila_t *pila){

	free(pila -> datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad == 0)? true:false;
}

/*FUNCION AUXILIAR*/
bool redimensionar_pila(pila_t *pila,size_t nueva_capacidad){
	/*Recibe una pila y su nueva capacidad, devuelve true y en caso de no poder hacerlodevuelve false*/
	void* datos_nuevos = realloc(pila->datos, sizeof(void*) * nueva_capacidad);

	if (datos_nuevos == NULL){
		return false;
	}

	pila-> datos = datos_nuevos;
	pila-> capacidad = nueva_capacidad;
	return true;
}

bool pila_apilar(pila_t *pila, void *valor){
	
	if ((pila->cantidad) == pila->capacidad ){
		if (redimensionar_pila(pila, pila->capacidad * REDIMENCIONAR)== false){
			return false;
		}
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

void *pila_ver_tope(const pila_t *pila){
	return pila->cantidad == 0? NULL : pila->datos[(pila->cantidad) - 1];
}

void *pila_desapilar(pila_t *pila){
	if (pila->cantidad == 0){
		return NULL;
	}
	void *tope = pila_ver_tope(pila);
	pila->cantidad--;

	if ((pila->cantidad *4 <= pila->capacidad) && ((pila->capacidad /REDIMENCIONAR) > CAPACIDAD_INICIAL)){
		redimensionar_pila(pila, (pila->capacidad / REDIMENCIONAR));
	}
	return tope;
}
