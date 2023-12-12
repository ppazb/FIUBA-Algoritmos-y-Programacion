#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
/* --------------------------------Estructuras Auxiliares--------------------------------*/
typedef struct nodo{
	void *dato;
	struct nodo* prox;
}nodo_t;

nodo_t *crear_nodo(void* dato){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL){
		return NULL;
	}
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}

/* --------------------------------Primitivas Lista--------------------------------*/

struct lista{
	struct nodo *prim;
	struct nodo *ult;
	size_t largo;
};


lista_t *lista_crear(void){
	lista_t *lista = malloc(sizeof(lista_t));

	if (lista == NULL){
		return NULL;
	}
	lista ->prim = NULL;
	lista ->ult = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	return (lista->prim==NULL);
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	
	nodo_t *nodo_nuevo = crear_nodo(dato);
	if (nodo_nuevo == NULL){
		return false;
	}

	lista->largo +=1;
	if (lista_esta_vacia(lista)==true){
		lista->prim = nodo_nuevo;
		lista->ult = nodo_nuevo;
	}else{
		nodo_nuevo->prox = lista->prim;
		lista->prim = nodo_nuevo;
	}
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t *nodo_nuevo = crear_nodo(dato);
	if (nodo_nuevo == NULL){
		return false;
	}

	lista->largo +=1;
	if (lista_esta_vacia(lista)==true){
		lista->prim = nodo_nuevo;
		lista->ult = nodo_nuevo;
	}else{
		lista->ult->prox = nodo_nuevo;
		lista->ult = nodo_nuevo;
	}
	return true;
}


void *lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista)){
		return NULL;
	}

	void *valor = lista->prim->dato;
	nodo_t *nuevo_prim = lista->prim->prox;
	free(lista->prim);
	lista->prim = nuevo_prim;

	lista->largo -=1;

	if (lista_esta_vacia(lista)){
		lista->ult = NULL;
	}

	return valor;
}

void *lista_ver_primero(const lista_t *lista){
	return lista_esta_vacia(lista)==true? NULL: lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	return lista_esta_vacia(lista)==true? NULL: lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
	while (!lista_esta_vacia(lista)){
		nodo_t *nodo = lista->prim;
		lista->prim = lista->prim->prox;

		if (destruir_dato != NULL){
			void *valor = nodo->dato;
			destruir_dato(valor);
		}
		free(nodo);
	}
	free(lista);
}

/* --------------------------------Primitivas Iterador Externo--------------------------------*/
struct lista_iter
{
	nodo_t *anterior;
	nodo_t *actual;
	lista_t *lista;
};


lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t *iter=malloc(sizeof(lista_iter_t));
	if (iter==NULL){
		return NULL;
	}

	iter->actual = lista->prim;
	iter->anterior = NULL;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	
	nodo_t *anterior_actual = iter->actual;
	if (anterior_actual==NULL){
		return false;
	}

	iter->anterior = anterior_actual;
	iter->actual = anterior_actual->prox;;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	return iter->actual==NULL? NULL : iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return (iter->actual == NULL);
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if (lista_esta_vacia(iter->lista)==true){
		if(lista_insertar_primero(iter->lista,dato)==false){
			return false;
		}
		iter->actual = iter->lista->prim;	
		return true;
	}
	nodo_t *nodo_nuevo = crear_nodo(dato);
	if (nodo_nuevo==NULL){
		return false;                                               
	}
	
	iter->lista->largo +=1;
	if(iter->actual == NULL){
		iter->anterior->prox = nodo_nuevo;
		iter->lista->ult = nodo_nuevo;
	
	}else{
		nodo_nuevo->prox = iter->actual;

		if(iter->anterior == NULL){
			iter->lista->prim = nodo_nuevo;
		}else{
			iter->anterior->prox = nodo_nuevo;
		}
	}
	iter->actual = nodo_nuevo;
	return true;
}


void *lista_iter_borrar(lista_iter_t *iter){
	if ((lista_esta_vacia(iter->lista)==true) || (iter->actual==NULL)){
		return NULL;
	}
	void* dato = iter->actual->dato;

	if(iter->anterior == NULL){
		lista_borrar_primero(iter->lista);
		iter->actual = iter->lista->prim;
	}else{
		iter->lista->largo -=1;
		nodo_t *nodo_a_borrar= iter->actual;
		nodo_t *actual_prox = iter->actual->prox;

		iter->anterior->prox= actual_prox;
		iter->actual = iter->anterior->prox;

		if(actual_prox==NULL){
			iter->lista->ult = iter->anterior;
		}
		free(nodo_a_borrar);
	}
	return dato;
}

/* --------------------------------Primitivas Iterador Interno--------------------------------*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	if (visitar == NULL){
		return;
	}

	nodo_t *nodo= lista->prim;
	while (nodo != NULL){
		bool visitado = visitar(nodo->dato,extra);
		if (visitado ==false){
			return;
		}
		nodo = nodo->prox;
	}
}