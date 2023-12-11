#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "cola.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
struct nodo;
typedef struct nodo nodo_t;
 struct nodo
{
	void* dato;
	struct nodo* prox;
};

nodo_t* nodo_crear_2(void* valor)
{
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo ==  NULL){return NULL;}
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}


struct cola
{
	nodo_t* prim;
	nodo_t* ulti;
	size_t cant;
};
/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

cola_t* cola_crear(void)
{
	cola_t* cola = malloc(sizeof(cola_t));
	if (cola == NULL){return NULL;}
	cola->prim = NULL;
	cola->ulti = NULL;
	cola->cant = 0;
	return cola;
}

bool cola_esta_vacia(const cola_t* cola)
{
	
	return cola->prim == NULL ? true : false;
}

void* cola_ver_primero(const cola_t *cola)
{
	if (cola_esta_vacia(cola))
	{
		return NULL;
	}
	return cola->prim->dato;
}
bool cola_encolar(cola_t *cola, void *valor)
{
    cola->cant += 1;
	if (cola_esta_vacia(cola))
	{
		cola->prim = nodo_crear_2(valor);
		cola->ulti =  cola->prim;
		return true;
	}
	if (cola->ulti == cola->prim)
	{
		cola->ulti = nodo_crear_2(valor);
		cola->prim->prox = cola->ulti;
		return true;
	}
	cola->ulti->prox = nodo_crear_2(valor);
	cola->ulti = cola->ulti->prox;
	return true;
}
void *cola_desencolar(cola_t *cola)
{
	if (cola_esta_vacia(cola))
	{
		return NULL;
	}
	cola->cant -= 1;
	void* valor = cola->prim->dato;
	nodo_t* proximo = cola->prim->prox;
	free(cola->prim);
	cola->prim = proximo;
	return valor;
}
size_t cola_cantidad(cola_t* cola)
{
    return cola->cant;
}
void cola_destruir(cola_t *cola, void (*destruir_dato)(void *))
{	

	nodo_t* actual = cola->prim;
	while(actual != NULL)
	{
		nodo_t* prox = actual->prox;
		if (destruir_dato != NULL)
		{
			destruir_dato(actual->dato);

		}
		free(actual);
		actual = prox;
	}
	free(cola);

}