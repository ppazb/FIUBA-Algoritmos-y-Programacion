#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "Data Structures/pila.h"
#include "Data Structures/cola.h"
#include "Data Structures/lista.h"

/*
Implementar la primitiva void** cola_multiprimeros(const cola_t* cola, size_t k) que dada una cola
y un numero k, devuelva los primeros k elementos de la cola, en el mismo orden en el que habrian salido de la cola.
En caso de que la cola tenga menos de k elementos, rellenar con NULL. La cola debe quedar en el mismo estado
que al invocarse la primitiva.
Indicar el orden de ejecucion del algoritmo. Justificar.*/


void** cola_multiprimeros(const cola_t* cola, size_t k){
    //devuelve los primeros k elementos del orden q hubiese salido. DE haber menos rellena con NULL
    //Primitiva = puedo utilizar la estructura interna
    void **vector = malloc(sizeof(void*)*k);
    size_t faltan = k;
    nodo_t* actual = cola->prim;
    size_t i = 0;
    while(faltan > 0) {
        if (actual) {
            vector[i] = actual->dato;
            actual = actual->prox;
        } else {
            vector[i] = NULL;
        }
        faltan -= 1;
        i++;
    }
}

/*
Se tiene un arreglo tal que [1, 1, 1, ..., 0, 0, ...] (es decir, “unos seguidos de ceros”). Se pide:
a) una función de orden O(logn) que encuentre el indice del primer 0. Si no hay ningún 0 (solo
hay unos), debe devolver -1.
b) demostrar con el Teorema Maestro que la función es, en efecto, O(log n).
Ejemplos:
[1, 1, 0, 0, 0] -> 2
[0, 0, 0, 0, 0] -> 0
[1, 1, 1, 1, 1] -> -1
*/

// Debo implementar una funcion tal que su orden sea O(logn) --> similar a Busqueda binaria.

int primer_cero(int arr[], size_t inicio, size_t fin){
    if(inicio>fin){ //primera condicion de corte: no lo encontre
        return -1;
    }

    int medio = (inicio+fin)/2;
    if(arr[medio] == 0 && (medio == 0 || arr[medio-1] == 1)){
        return medio;
    }
    if(arr[medio] == 0) {
        return primer_cero(arr, inicio, medio);
    }else{
        return primer_cero(arr,medio+1,fin);
    }
}

/*
En un colegio de Villa General Belgrano, los alumnos deben formar de la siguiente manera: primero las
niñas ordenadas por altura de menor a mayor. Luego los niños, también ordenados por altura de menor a
mayor. Escribir una función en C que reciba una cola de enteros (representando las alturas de los alumnos
en centímetros), y devuelva true si es posible que estén bien formados (considerando sólo las alturas) o
false en caso contrario. Se puede vaciar la cola sin necesidad de dejarla como se la recibió. Por ejemplo:
• Primero -> [ 125, 128, 129, 124, 134, 138, 140 ]: true
• Primero -> [ 125, 128, 129, 133, 134, 138, 140 ]: true
• Primero -> [ 125, 120, 129, 133, 124, 138, 140 ]: false
Indicar el orden del algoritmo.



Escribir una primitiva que invierta el contenido de una Lista Enlazada sin usar ninguna
estructura auxiliar.
*/

void invertir_lista(lista_t* lista){
    nodo_t* primero = lista ->prim; //los guardo para modificar la lista
    nodo_t* ultimo = lista ->ult;

    nodo_t* actual = lista->prim;
    nodo_t* siguiente = actual->siguiente;
    while(siguiente){
        nodo_t* aux = siguiente->prox;
        siguiente->prox = actual;
        actual = siguiente;
        siguiente = aux;
    }

    lista->prim = ultimo;
    primero->prox = NULL;
    lista->ultimo = primero;
}


/*Implementar la funcion void** pila_multipop(pila_t* pila, size_t n) que
devuelve un arreglo de tamaño n con los primeros n elementos de la pila
(completando con NULL si la cantidad de elementos de la pila es menor a n)
El arreglo a devolver debe tener en las primeras posiciones a los ultimos
elementos apilados, y debe eliminarlos de la pila.
Indicar el orden de la funcion implementada*/


void** pila_multipop(pila_t* pila, size_t n){
    void** arr = malloc(sizeof(void*) * n);
    if(!arr) return NULL;

    for (int i = 0; i < n; ++i) {
        if(!pila_esta_vacia(pila)){
            arr[i] = pila_desapilar(pila);
        }else{
            arr[i] = NULL;
        }
    }
}

/*
Se tiene un arreglo tal que [1, 1, 1, ..., 0, 0, ...] (es decir, “unos seguidos de ceros”). Se pide:
a) una función de orden O(logn) que encuentre el indice del primer 0. Si no hay ningún 0 (solo
hay unos), debe devolver -1.
b) demostrar con el Teorema Maestro que la función es, en efecto, O(log n).
Ejemplos:
[1, 1, 0, 0, 0] -> 2
[0, 0, 0, 0, 0] -> 0
[1, 1, 1, 1, 1] -> -1
*/

int pos_cero(int arr[],int inicio, int fin){
    if(inicio>fin)return -1; //condicion de corte falla

    int medio = (inicio+fin)/2;
    if((arr[medio] == 0) && (medio == 0 || arr[medio-1] == 1)){ //cond corte exitosa
        return medio;
    }


    if(arr[medio] == 0){
        return pos_cero(arr,inicio,medio);
    }else{
        return pos_cero(arr,medio+1,fin);
    }
}

/*
En un colegio de Villa General Belgrano, los alumnos deben formar de la siguiente manera: primero las
niñas ordenadas por altura de menor a mayor. Luego los niños, también ordenados por altura de menor a
mayor. Escribir una función en C que reciba una cola de enteros (representando las alturas de los alumnos
en centímetros), y devuelva true si es posible que estén bien formados (considerando sólo las alturas) o
false en caso contrario. Se puede vaciar la cola sin necesidad de dejarla como se la recibió. Por ejemplo:
• Primero -> [ 125, 128, 129, 124, 134, 138, 140 ]: true
• Primero -> [ 125, 128, 129, 133, 134, 138, 140 ]: true
• Primero -> [ 125, 120, 129, 133, 124, 138, 140 ]: false
Indicar el orden del algoritmo.*/


bool ordenados_altura(cola_t* cola){

    int ultima_altura = *((int*)cola_desencolar(cola));
    bool reinicio = false;

    while(!cola_esta_vacia(cola)){

        int valor = *((int*)cola_desencolar(cola));

        if(valor > ultima_altura) {
            ultima_altura = valor;
        }else if(!reinicio){
            reinicio = true;
            ultima_altura = valor;
        }else{
            return false;
        }
    }
    return true;
}


/*
Escribir una función que reciba una pila y un parámetro n con la cantidad de elementos
en la pila y la “parta” en dos: La que es recibida por parámetro contendrá la primera mitad
(elementos de 0 a n/2 - 1), y la pila devuelta por la función tendrá los elementos de n/2 a n-1,
manteniendo el orden de la pila original. (Se pueden usar las estructuras auxiliares que crean
convenientes)*/

pila_t* partir_pila(pila_t* pila, int n){
    pila_t* aux1 = pila_crear();
    if(!aux1) return NULL;
    pila_t* final = pila_crear();
    if(!final){
        pila_destruir(aux1);
        return NULL;
    }

    for(int i=0; i < (n/2); i++){
        pila_apilar(aux1,pila_desapilar(pila));
    }
    while(!pila_esta_vacia(aux1)){
        pila_apilar(final,pila_desapilar(aux1));
    }
    pila_destruir(aux1);
    return final;
}

/*
Dada una pila de enteros, escribir una función que determine si es piramidal. Una pila de enteros es
piramidal si cada elemento es menor a su elemento inferior (en el sentido que va desde el tope de la pila
hacia el otro extremo). La pila no debe ser modificada al terminar la función.
Indicar el orden del algoritmo propuesto.
*/

void _es_piramidal(pila_t* pila, bool* piramidal, int* ultimo_valor){
    if(pila_esta_vacia(pila)) return;

    void* aux = pila_desapilar(pila);
    int valor = *((int*)aux);
    if(ultimo_valor == NULL){
        _es_piramidal(pila,piramidal,(int*)aux);
    }
    else{
        if ((*ultimo_valor) > valor) {
            *piramidal = false;
            return;
        }
        _es_piramidal(pila,piramidal,aux);
    }
    pila_apilar(pila,aux);
}

bool es_piramidal(pila_t* pila){
    bool piramidal = true;
    _es_piramidal(pila,&piramidal,NULL);
    return piramidal;
}


/*
Escriba una función recursiva para calcular de forma eficiente la potencia de un número
con exponente entero positivo.
*/

int potencia(int numero, int exponente){
    if(exponente == 0){
        return 1;
    }
    return numero * potencia(numero,exponente-1);
}

/*
Dada una lista enlazada, implementar una primitiva (lado Alan) que elimine todas las ocurrencias
del dato pasado por parametro y devuelva True si encontró al menos 1, o False si no encontro ninguno.*/


bool eliminar_valor(lista_t* lista, void *dato){
    nodo_t* anterior = NULL;
    nodo_t* actual = lista->prim;
    bool eliminado = false;


    while(actual){
        if(*(actual->dato) == *dato){
            eliminado = true;

            nodo_t* aux = actual;
            nodo_t* siguiente = actual->prox;
            if(!anterior) {
                lista->prim = actual-
            }
            anterior->prox = siguiente;
            actual = siguiente;
            nodo_destruir(actual);

        }else {
            anterior = actual;
            actual = actual->prox;
        }
    }
    return eliminado;
}


/*
Se pide implementar una función recursiva que calcule el largo de una pila sin utilizar
estructuras auxiliares ni acceder a su estructura interna (que no sabemos cuál es). El prototipo
de la función es:
size t largo pila(pila t *pila);
Se puede llamar a cualquier primitiva de la pila, incluyendo aquellas que la modifiquen,
pero siempre la pila debe quedar en su estado original al terminar la ejecución de la función.
*/


int largo_pila(pila_t* pila){
    if (pila_esta_vacia(pila)) return 0;

    void* dato = pila_desapilar(pila);
    int largo = 1 + largo_pila(pila);
    pila_apilar(pila,dato);
    return largo;
}


int main() {
    //int valor = potencia(4,5);
    //printf("%i", valor);
    /*
    int arr[5] = {1,1,1,0,0};
    int arr2[5] ={1,1,1,1,1};
    int arr3[5] = {0,0,0,0,0};

    printf("1: %i \n", pos_cero( arr, 0,4));
    printf("2: %i \n", pos_cero( arr2, 0,4));
    printf("3: %i \n", pos_cero( arr3, 0,4));

    int arr4[6] = {1,1,1,0,0,0};
    printf("4 %i \n", pos_cero( arr4, 0,5));

    int arr5[2] = {1,0};
    int arr6[2] = {0,0};
    int arr7[2] = {1,1};
    printf("5: %i \n", pos_cero( arr5, 0,1));
    printf("6: %i \n", pos_cero( arr6, 0,1));
    printf("7: %i \n", pos_cero( arr7, 0,1));

    int arr8[1] = {1};
    int arr9[1] = {0};
    printf("8: %i \n", pos_cero( arr8, 0,0));
    printf("9: %i \n", pos_cero( arr9, 0,0));*/ //Pruebas primer cero.

    /*
     pila_t* pila = pila_crear();
     int a=1,b=2,c=3,d=4,e=5,f=6;

    pila_apilar(pila,&f);
    pila_apilar(pila,&e);
    pila_apilar(pila,&d);
    pila_apilar(pila,&c);
    pila_apilar(pila,&b);
    pila_apilar(pila,&a);
    int largo = largo_pila(pila);
    printf("largo = %i",largo);
    while(!pila_esta_vacia(pila)){

        int valor = *((int*)pila_desapilar(pila));
        printf("%i ",valor);
    }

    //bool piramidal = es_piramidal(pila);
    //printf(" %s\n", piramidal ? "true" : "false");
    pila_destruir(pila); *///piramidal


    return 0;
}
