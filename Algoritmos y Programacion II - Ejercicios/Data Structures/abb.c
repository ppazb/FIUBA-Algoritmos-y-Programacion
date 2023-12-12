extern char* strdup(const char*);
#include "abb.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define POS_PADRE 0
#define POS_HIJO 1
#define CADENA_VACIA ""


struct abb
{
    struct nodo* hijo_izq;
    struct nodo* hijo_der;
    struct nodo* raiz;
    const char* clave;
    void* dato;
    int (*abb_comparar_clave_t) (const char *, const char *);
    void (*destruir_dato)(void*);
    size_t cantidad;

};


//--------------------------------Estructura auxiliar-Nodo---------------------------------
struct nodo
{
    char* clave;
    void* dato;
    struct nodo* prox_izq;
    struct nodo* prox_der;
};

nodo_t* nodo_crear(void* valor)
{
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo ==  NULL)return NULL;
    nodo->clave = NULL;
    nodo->dato = valor;
    nodo->prox_izq = NULL;
    nodo->prox_der = NULL;
    return nodo;
}
void nodo_destruir(nodo_t* actual, abb_t* arbol)
{
    if (arbol->destruir_dato) arbol->destruir_dato(actual->dato);
    free(actual->clave);
    free(actual);
}

//----------------------------------------------------------------------------------------------------




void nodos_destruir(nodo_t* nodo, abb_t* abb);
nodo_t** minimo_mayor(nodo_t** nodo);
void apilar_izq(nodo_t* actual, pila_t* pila);
void nodo_destruir(nodo_t* actual, abb_t* arbol);
nodo_t** padre(nodo_t** resultado, const abb_t* arbol, const char* clave);
void _abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, nodo_t* actual, bool* continuar);
void _abb_in_order_rango(abb_t *arbol, char* inicio, char* fin, bool visitar(const char *, void *, void *), void *extra, nodo_t* actual, bool* continuar);
void borrar_dos_hijos(abb_t* arbol,nodo_t* actual, nodo_t* resu[]);
void borrar_sin_hijos(abb_t* arbol,nodo_t* actual, nodo_t* padre);
void borrar_un_hijos(abb_t* arbol, nodo_t* actual, nodo_t* padre);

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato)
{
    abb_t* abb = malloc(sizeof(abb_t));
    if (!abb) return NULL;
    abb->hijo_der = NULL;
    abb->hijo_izq = NULL;
    abb->raiz = NULL;
    abb->abb_comparar_clave_t = cmp;
    abb->destruir_dato = destruir_dato;
    abb->cantidad = 0;
    return	abb;
}



bool abb_guardar(abb_t *arbol, const char *clave, void *dato)
{
    int comparacion = 0;
    nodo_t * resultado[2];
    resultado[POS_PADRE] = arbol->raiz;
    resultado[POS_HIJO] = arbol->raiz;
    char* clave_agregar = strdup(clave);
    padre(resultado, arbol, clave_agregar);
    nodo_t* actual = resultado[POS_HIJO];
    nodo_t* padre = resultado[POS_PADRE];
    if (abb_pertenece(arbol, clave_agregar))
    {
        if (arbol->destruir_dato) arbol->destruir_dato(actual->dato);
        actual->dato = dato;
        free(clave_agregar);
        return true;
    }
    else if (arbol->cantidad == 0)
    {
        arbol->raiz = nodo_crear(dato);
        arbol->raiz->clave = clave_agregar;
        arbol->cantidad += 1;
        return true;
    }
    comparacion = arbol->abb_comparar_clave_t(padre->clave, clave_agregar);
    actual = nodo_crear(dato);
    if (!actual) return false;
    if (comparacion < 0)
    {
        padre->prox_der = actual;
        actual->clave = clave_agregar;
    }
    else
        {
            padre->prox_izq = actual;
            actual->clave = clave_agregar;
        }
    arbol->cantidad += 1;
    return  true;
}

void* abb_borrar(abb_t *arbol, const char *clave) {
    nodo_t *resu[2];
    resu[POS_PADRE] = arbol->raiz;
    resu[POS_HIJO] = arbol->raiz;
    char *clave_borrar = strdup(clave);
    padre(resu, arbol, clave_borrar);
    nodo_t *actual = resu[POS_HIJO];
    nodo_t *padre = resu[POS_PADRE];
    if (!actual)
    {
        free(clave_borrar);
        return NULL;
    }
    void *dato = actual->dato;
    if (actual->prox_izq && actual->prox_der)
    {
        borrar_dos_hijos(arbol, actual, resu);
    } else if (actual->prox_der || actual->prox_izq)
    {
        borrar_un_hijos(arbol, actual, padre);
    } else borrar_sin_hijos(arbol, actual, padre);
    arbol->cantidad -= 1;
    free(clave_borrar);
    return dato;
}


void *abb_obtener(const abb_t *arbol, const char *clave)
{
    nodo_t* resu[2];
    resu[POS_PADRE] = arbol->raiz;
    resu[POS_HIJO] = arbol->raiz;
    padre(resu, arbol, clave);
    return resu[POS_HIJO] ? (resu[POS_HIJO]->dato) : (NULL);
}

bool abb_pertenece(const abb_t *arbol, const char *clave)
{
    nodo_t* resu[2];
    resu[POS_PADRE] = arbol->raiz;
    resu[POS_HIJO] = arbol->raiz;
    padre(resu,arbol, clave);
    if (resu[POS_HIJO]) return true;
    return false;
}


size_t abb_cantidad(abb_t* abb)
{
    return abb->cantidad;
}


void abb_destruir(abb_t *arbol)
{

    if (arbol->raiz) nodos_destruir(arbol->raiz, arbol);
    free(arbol);
}



void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra)
{
    bool continuar = true;
    _abb_in_order(arbol, visitar, extra,arbol->raiz,  &continuar);
}

void _abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra, nodo_t* actual, bool* continuar)
{
    if (!actual || !*continuar) return;
    if (actual->prox_izq)  _abb_in_order(arbol, visitar, extra, actual->prox_izq, continuar);
    if (*continuar && !visitar(actual->clave, actual->dato, extra))
    {

        *continuar = false;
        return;

    }

    if (actual->prox_der)  _abb_in_order(arbol, visitar, extra, actual->prox_der,continuar);
}


void abb_in_order_rango(abb_t *arbol,char* inicio, char* fin, bool visitar(const char *, void *, void *), void *extra)
{
    bool continuar = true;
    _abb_in_order_rango(arbol, inicio, fin,visitar, extra,arbol->raiz,  &continuar);
}

void _abb_in_order_rango(abb_t *arbol,char* inicio, char* fin, bool visitar(const char *, void *, void *), void *extra, nodo_t* actual, bool* continuar)
{
    if (!actual || !*continuar) return;
    if (actual->prox_izq)  _abb_in_order_rango(arbol, inicio, fin,visitar, extra, actual->prox_izq, continuar);
    if((strcmp(inicio,CADENA_VACIA) == 0 || strcmp(actual->clave,inicio) >= 0) && (strcmp(fin,CADENA_VACIA) == 0 || strcmp(actual->clave,fin) <= 0)){
        
        if ((*continuar && !visitar(actual->clave, actual->dato, extra)) || (strcmp(fin, actual->clave) == 0)){

            *continuar = false;
            return;
        }
    }

    if (actual->prox_der)  _abb_in_order_rango(arbol, inicio,fin, visitar, extra, actual->prox_der,continuar);
}
//--------------------------------------------------------------------------------------------------------------------
//Iterador externo
struct abb_iter
{
    const abb_t* arbol;
    pila_t* pila;
};

abb_iter_t *abb_iter_in_crear(const abb_t *arbol)
{
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    iter->pila = pila_crear();
    if(arbol->raiz)
    {
        pila_apilar(iter->pila, arbol->raiz);
        apilar_izq(arbol->raiz->prox_izq, iter->pila);
    }
    iter->arbol = arbol;
    return iter;
}

void apilar_izq(nodo_t* actual, pila_t* pila)
{
    if (!actual) return;
    pila_apilar(pila, actual);
    if (actual->prox_izq)  apilar_izq(actual->prox_izq, pila);

}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter)
{
    nodo_t* nodo = pila_ver_tope(iter->pila);
    if (!nodo) return NULL;
    return nodo->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter)
{
    if (pila_esta_vacia(iter->pila)) return true;

    return false;
}

bool abb_iter_in_avanzar(abb_iter_t *iter)
{
    if (abb_iter_in_al_final(iter)) return  false;
    nodo_t* actual = pila_desapilar(iter->pila);

    if (actual->prox_der)
    {
        pila_apilar(iter->pila,actual->prox_der);
        apilar_izq( actual->prox_der->prox_izq, iter->pila);
    }
    return true;
}

void abb_iter_in_destruir(abb_iter_t* iter)
{
    pila_destruir(iter->pila);
    free(iter);
}


//-------------------------------Funciones auxiliares----------------------------------------------------------

void borrar_dos_hijos(abb_t* arbol, nodo_t* actual, nodo_t* resu[])
{
    resu[POS_PADRE] = resu[POS_HIJO];
    resu[POS_HIJO] = resu[POS_HIJO]->prox_der;
    char *clave_reemplazo = strdup(minimo_mayor(resu)[POS_HIJO]->clave);
    void *dato_reemplazante = abb_borrar(arbol, clave_reemplazo);
    if (arbol->destruir_dato) arbol->destruir_dato(actual->dato);
    actual->dato = dato_reemplazante;
    free(actual->clave);
    actual->clave = clave_reemplazo;
    arbol->cantidad += 1;
    return;
}


void borrar_un_hijos(abb_t* arbol,nodo_t* actual, nodo_t* padre)
{
    if (padre == actual) actual->prox_der ? (arbol->raiz = actual->prox_der) : (arbol->raiz = actual->prox_izq);
    if (padre->prox_izq == actual) actual->prox_der ? (padre->prox_izq = actual->prox_der) : (padre->prox_izq = actual->prox_izq);
    else actual->prox_der ? (padre->prox_der = actual->prox_der) : (padre->prox_der = actual->prox_izq);
    nodo_destruir(actual, arbol);
}


void borrar_sin_hijos(abb_t* arbol,nodo_t* actual, nodo_t* padre)
{
    if (padre == actual) arbol->raiz = NULL;
    padre->prox_izq == actual ? (padre->prox_izq = NULL) : (padre->prox_der = NULL);
    nodo_destruir(actual, arbol);
}

void nodos_destruir(nodo_t* nodo, abb_t* arbol)
{
    if (!nodo) return;
    if (nodo->prox_izq) nodos_destruir(nodo->prox_izq,arbol);
    if (nodo->prox_der) nodos_destruir(nodo->prox_der,arbol);
    if (arbol->destruir_dato) arbol->destruir_dato(nodo->dato);
    free(nodo->clave);
    free(nodo);
}



nodo_t** padre(nodo_t** resultado, const abb_t* arbol, const char* clave)
{
    nodo_t* actual = resultado[POS_HIJO];
    int comparacion = 0;
    if (!actual) return  resultado;
    comparacion = arbol->abb_comparar_clave_t(actual->clave, clave);
    if (comparacion < 0 )
    {
        resultado[POS_PADRE] = actual;
        resultado[POS_HIJO] = actual->prox_der;
        resultado = padre(resultado, arbol, clave);


    }
    else if (comparacion > 0 )
    {
        resultado[POS_PADRE] = actual;
        resultado[POS_HIJO] = actual->prox_izq;
        resultado = padre(resultado, arbol, clave);
    }
    return resultado;
}

nodo_t** minimo_mayor(nodo_t** resu)
{
    nodo_t* actual = resu[POS_HIJO];
    if (!actual->prox_izq) return resu;
    resu[POS_PADRE] = actual;
    resu[POS_HIJO] = actual->prox_izq;
    resu = minimo_mayor(resu);
    return resu;
}


