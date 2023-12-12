#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


/*
Implementar una primitiva void ab_espejar(ab_t* ab) que dado un árbol binario, devuelva el mismo
árbol espejado. Indicar y justificar el orden.
 */

//Arbol binario: ab_t*{ nodo_t* raiz}
//nodo_t*{ dato,clave,izq,der}

void ab_espejar(ab_t* ab){
    _ab_espejar(ab->raiz);
    return
}

void _ab_espejar(nodo_t* nodo){
    if(!nodo) return;
    nodo_t * aux = nodo->der;
    nodo->der = nodo->izq;
    nodo->izq = aux;
    _ab_espejar(nodo->der);
    _ab_espejar(nodo->izq);
}

/*
Definimos como quiebre en un arbol binario cuando ocurre que un hijo derecho
tiene un hijo izquierdo, o viceversa.
Implementar una primitiva para el arbol binario size_t ab_quiebres(const ab_t*) que
dado un arbol binario nos devuelva la cantidad de quiebres que tiene. La primitiva no
debe modificar el arbol. La estructura del tipo ab_t es:
typedef struct ab {

	struct ab* izq;
	struct ab* der;
} ab_t;
Indicar y justifcar el orden de la primitiva e indicar el tipo de recorrido implementado.
*/
//Asumo que el primer elemento no puede generar un quiebre puesto que no es hijo de nadie.



void quiebres(ab_t* ab, size_t* total, bool es_nodo_derecho){
    if(!nodo) return;
    if(es_nodo_derecho && ab->izq!=NULL) *total += 1;
    if(!es_nodo_derecho && ab->der!=NULL) *total += 1;

    quiebres(ab->der,total,true);
    quiebres(ab->izq,total,false);
}

size_t ab_quiebres(const ab_t*){
    size_t total = 0;
    quiebres(ab->izq, &total,false); //Recorro medio arbol
    quiebres(ab->der,&total,true); //Recorro la otra mitad -> Termino recorriendo todo el arbol ->  O(n)
    return total;
}

/* Calcular altura de un arbol binario de busqueda */

size_t altura(ab_t* ab){
    if(!ab) return 0;
    return max(altura(ab->der), altura(ab->izq))+ 1;
}

/*
Implementar una primitiva para el ABB, que reciba el ABB y devuelva una lista con las claves del mismo
ordenadas tal que si insertáramos las claves en un ABB vacío (con la misma función de comparación),
dicho ABB tendría la misma estructura que el árbol original. ¿Qué tipo de recorrido utilizaste?
Indicar el orden de la primitiva. Justificar.
*/


void guardar_claves(ab_t* ab, lista_t* lista){
    if(!ab) return;

    lista_insertar_ultimo(lista,(void*) ab->clave);
    guardar_lista(ab->izq,lista);
    guardar_lista(ab->der,lista);
}


lista_t* claves_en_orden (ab_t* ab){
    lista_t* lista = lista_crear();
    if(!lista) return NULL;

    guardar_claves(ab,lista);
    return lista;
}

/*
Se tiene un árbol binario de búsqueda con cadenas como claves y función de comparación strcmp.
Implementar una primitiva lista_t* abb_mayores(const abb_t* abb, const char* cadena) que dado
un ABB y una cadena, devuelva una lista ordenada que contenga las claves del árbol que sean mayores a la
cadena recibida por parámetro (que no necesariamente está en el árbol).
Suponer que la estructura del TDA es:
typedef struct abb {
    const char* clave;
    struct abb* izq;
    struct abb* der;
} abb_t;
Aclaración: se debe realizar la menor cantidad posible de comparaciones
 */

void guardar_mayores(abb_t* abb, lista_t* lista, const char* cadena){
    if(!abb) return;

    if(strcmp(abb->clave,cadena) >= 0){
        guardar_mayores(abb->izq,lista,cadena);
        lista_insertar_ultimo(lista,abb->clave);
    }
    guardar_mayores(abb->der,lista,cadena);
}

lista_t* abb_mayores(const abb_t* abb, const char* cadena){
    lista_t* lista = lista_crear();
    if(!lista) return NULL;

    guardar_mayores(abb,lista,cadena);
    return lista;
}




int main() {
    printf("Hello, World!\n");
    return 0;
}
