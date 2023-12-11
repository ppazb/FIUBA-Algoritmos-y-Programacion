#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define  MULTIPLICADOR 2
#define  REDIMENCIONADOR 4
#define  CAPACIDAD_INICIAL 1
#define PRIMERA_POS 0
#define LINEA_VACIA ""
size_t traer_padre(size_t pos);
size_t hijo_izq(size_t pos);
size_t hijo_der(size_t pos);
void upheap(heap_t* heap, size_t pos);
void downheap(heap_t* heap, size_t pos);
void heapfy(heap_t* heap);
size_t max(heap_t* heap, size_t pos_actual);
bool heap_redimensionar(heap_t* heap, size_t valor);
void swap(void *elementos_a[], void* elementos_b[], size_t n, size_t posicion);

struct heap{
    void** prioridades;
    size_t size;
    cmp_func_t cmpFunc;
    size_t capacidad;
};

heap_t* heap_crear(cmp_func_t cmpFunc)
{
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;
    heap->prioridades = malloc(sizeof(void*));
    if (!heap->prioridades)
    {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->cmpFunc = cmpFunc;
    heap->capacidad = CAPACIDAD_INICIAL;
    return heap;
}

size_t heap_cantidad(const heap_t *heap)
{
    return heap->size;
}

bool heap_esta_vacio(const heap_t *heap)
{
    return heap->size == 0 ? (true) : (false);
}

void *heap_ver_max(const heap_t *heap)
{
    return heap->size != 0 ? (heap->prioridades[PRIMERA_POS]) : NULL;
}

bool heap_encolar(heap_t *heap, void *elem)
{
    bool redimensiono = true;
    if (heap->size == heap->capacidad) redimensiono = heap_redimensionar(heap, heap->capacidad * MULTIPLICADOR);
    if (!redimensiono) return false;
    heap->prioridades[heap->size] = elem;
    upheap(heap, heap->size);
    heap->size += 1;
    return true;
}



void *heap_desencolar(heap_t *heap)
{
    if (heap_esta_vacio(heap))
    {
        return NULL;
    }


    swap(heap->prioridades, heap->prioridades, heap->size, PRIMERA_POS);
    void* prioridad = heap->prioridades[heap->size - 1];
    heap->size -= 1;
    downheap(heap, PRIMERA_POS);
    if (heap->size * REDIMENCIONADOR <= heap->capacidad)
    {
        heap_redimensionar(heap, heap->capacidad / MULTIPLICADOR);
    }

    return  prioridad;

}



void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e))
{
    for (size_t i = 0; i < heap->size ; ++i)
    {
        if (destruir_elemento) destruir_elemento(heap->prioridades[i]);

    }
    free(heap->prioridades);
    free(heap);
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp)
{
    heap_t* heap = heap_crear_arr(elementos, cant, cmp);
	//heap_t* heap = heap_crear(cmp);
	heap->size = cant;
    //heap->prioridades = elementos;
	//heapfy(heap);

	for ( size_t i = cant; i > 0 ; --i)
	{
        swap(heap->prioridades, heap->prioridades, i, PRIMERA_POS);
        swap(elementos, heap->prioridades, i, cant-1);
		cant -= 1;
		heap->size -= 1;
		downheap(heap, PRIMERA_POS);
		
	}


	heap_destruir(heap, NULL);

	return;
}



heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp)
{
    heap_t* heap = heap_crear(cmp);
    heap_redimensionar(heap, n);
    //void* aux  = realloc(heap->prioridades, sizeof(void*) * n);
    heap->capacidad = n;
    for (size_t j = 0; j < n ; ++j)
    {
        heap->prioridades[j] = arreglo[j];
    }
    heap->size = n;
    heapfy(heap);
    return heap;
}


bool heap_redimensionar(heap_t* heap, size_t valor)
{
    if (valor < CAPACIDAD_INICIAL) valor = CAPACIDAD_INICIAL;
    void* prioridades_aux = realloc(heap->prioridades, valor * sizeof(void*));
    if (!prioridades_aux) return false;
    heap->prioridades = prioridades_aux;
    heap->capacidad = valor;
    return true;
}
//-------------------------------------Funciones auxiliares-------------------------------


void swap(void *elementos_a[], void* elementos_b[], size_t n, size_t posicion)
{
    void* aux = elementos_a[n-1];
    elementos_a[n-1] = elementos_b[posicion];
    elementos_b[posicion] = aux;
}

void downheap(heap_t* heap, size_t pos)
{
    size_t pos_max = max(heap, pos);
    if (pos_max == pos || heap->size == 1) return;
    void* aux = heap->prioridades[pos];
    heap->prioridades[pos] = heap->prioridades[pos_max];
    heap->prioridades[pos_max] = aux;
    downheap(heap, pos_max);
    return;



}

void upheap(heap_t* heap, size_t pos)
{
    if (pos == 0) return;
    size_t pos_padre = traer_padre(pos);
    void* actual = heap->prioridades[pos];
    void* padre = heap->prioridades[pos_padre];
    if (heap->cmpFunc(actual, padre) > 0)
    {
        heap->prioridades[pos] = padre;
        heap->prioridades[pos_padre] = actual;
        upheap(heap, pos_padre);
    }
    return;

}

//aplica downheap, n/2 veces para armar el heap, donde n es el size del arreglo prioridades del heap
void heapfy(heap_t* heap)
{
    for (int i = (int) heap->size / 2; i >= 0  ; --i)
    {
        downheap(heap, i);
    }
}

//recibe una posicion y devuelve su padre
size_t traer_padre(size_t pos)
{
    return (pos - 1) / 2;
}

//recibe una posicion y devuelve su hijo izquierdo
size_t hijo_izq(size_t pos)
{
    return 2 * pos + 1;
}

//recibe una posicion y devuelve su hijo derecho
size_t hijo_der(size_t pos)
{
    return 2 * pos + 2;
}

size_t max(heap_t* heap, size_t pos)
{
    //Funcion auxiliar, devuelve la posicion de la prioridad mas alta
    size_t tam = heap->size;
    size_t pos_h_izq = hijo_izq(pos);
    size_t pos_h_der = hijo_der(pos);
    void* actual = heap->prioridades[pos];
    void* h_izq = pos_h_izq < tam ? ( heap->prioridades[pos_h_izq]) : (heap->prioridades[pos]);
    void* h_der = pos_h_der < tam ? (heap->prioridades[pos_h_der]) : (heap->prioridades[pos]);
    if (pos_h_der >= tam && pos_h_izq >= tam) return pos;
    if (heap->cmpFunc(h_izq, actual) > 0 && heap->cmpFunc(h_izq, h_der) > 0) return pos_h_izq;
    else if (heap->cmpFunc(h_der, actual) > 0 && heap->cmpFunc(h_der, h_izq) > 0) return pos_h_der;
    else return pos;


}

