#include "pila.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define  MULTIPLICADOR 2
#define  REDIMENCIONADOR 4
#define  CAPACIDAD_INICIAL 1
bool dimensionar(pila_t* pila, size_t valor);

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
pila_t *pila_crear(void)
{
	pila_t* pila = malloc(sizeof(pila_t));
	if (pila == NULL){return NULL;}
	pila->datos = malloc(sizeof(void*));
	if (pila->datos == NULL){return NULL;}
	pila-> cantidad = 0;
	pila-> capacidad = CAPACIDAD_INICIAL;
	return pila;
}
bool pila_esta_vacia(const pila_t* pila)
{	
	return  pila->cantidad == 0; //No me quedo claro si con a una linea te referias a esto, lo vimos hoy en clase
}
void pila_destruir(pila_t* pila)
{
	free(pila->datos);
	free(pila);
}
void *pila_ver_tope(const pila_t *pila)
{
	if (pila_esta_vacia(pila))
	{
		return NULL;
	}
	return pila->datos[pila->cantidad-1];
}
bool pila_apilar(pila_t *pila, void *valor)
{	bool modifico = true;

	if (pila->cantidad == pila->capacidad)
	{
		modifico = dimensionar(pila, MULTIPLICADOR * pila->capacidad);
	}
	if (modifico)
	{
		pila->datos[pila->cantidad] = valor;
		pila->cantidad += 1;
		return true;
	}
	return false;
	

}
void* pila_desapilar(pila_t* pila)
{
	
	void* valor;
	if (pila_esta_vacia(pila))
	{
		return NULL;
	}
	valor = pila->datos[pila->cantidad-1];
	pila->cantidad -= 1;
	if (pila->cantidad * REDIMENCIONADOR <= pila->capacidad)
	{
		 dimensionar(pila, pila->capacidad / MULTIPLICADOR);
	}
	return valor;
}
bool dimensionar(pila_t* pila, size_t valor)
{	valor < CAPACIDAD_INICIAL ? valor = CAPACIDAD_INICIAL : false;
	void* datosAux = realloc(pila->datos, valor * sizeof(void*));
	if (datosAux == NULL)
	{
		return false;
	}
	pila->datos = datosAux;
	pila->capacidad = valor;
	return true;
}
