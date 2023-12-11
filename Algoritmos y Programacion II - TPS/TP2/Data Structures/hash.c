#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CAPACIDAD_INCIAL 101
#define FACTOR_CARGA 0.7
#define REDIMENSION 2

typedef enum estado {
    VACIO, OCUPADO, BORRADO
} estado_t;

typedef struct campo{
  char* clave;
  void* valor;
  estado_t estado;
} campo_t;

struct hash{
  size_t capacidad;
  size_t cantidad;
  hash_destruir_dato_t funcion_destruccion;
  campo_t* tabla;
};



/*------------------------------------------- AUX -------------------------------------------*/


unsigned long hashing(const char *str){ //djb2 by Dan Bernstein. Recomendada en Stack Overflow
    unsigned long hash = 5381;
    long unsigned int c;
    while ((c = (long unsigned int)*str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

bool buscar_pos_clave(const hash_t *hash, const char *clave, void *puntero){
    
    unsigned long  deberia_estar = hashing(clave) % hash->capacidad; //calculo donde deberia estar.
    if(hash->tabla[deberia_estar].estado == OCUPADO && strcmp(hash->tabla[deberia_estar].clave,(char*)clave) == 0){
        if(puntero){
            *(( unsigned long*)puntero) = deberia_estar;
        }
        return true;
    }

    unsigned long posicion = deberia_estar;
    bool vuelta_completa = false;
    while(hash->tabla[posicion].estado != VACIO){
        
        if(posicion+1 >= hash->capacidad){ //Llegue al final, vuelvo a 0 a buscar si es que ya no lo hice.
            if(vuelta_completa == true){
                return false; //ya habia chequeado, no esta
            }
            posicion = 0;
            vuelta_completa = true;
        }

        if(hash->tabla[posicion].estado == OCUPADO && strcmp(hash->tabla[posicion].clave,(char*)clave) == 0){
            if(puntero){
                *((unsigned long*)puntero) = posicion;
            }
            return true;
        }
        posicion++;
    }
    return false;
}

unsigned long calcular_posicion(hash_t *hash, const char *clave){
    unsigned long pos = hashing(clave) % hash->capacidad; //donde deberia estar
    
    while(hash->tabla[pos].estado == OCUPADO){ //paso todos los lugares ocupados.   
        pos++;
        if(pos >= hash->capacidad){ //llegue al final, mando al principio. Se que la pos existe pq redimensiono.
            pos = 0;
        }
    }
    return pos;
}

bool redimensionar(hash_t *hash){
    
    size_t capacidad_anterior = hash->capacidad;
    size_t capacidad_nueva = capacidad_anterior * REDIMENSION;  
    
    campo_t* tabla_anterior = hash->tabla;
    campo_t* tabla_nueva = malloc(capacidad_nueva * sizeof(campo_t));
    if(!tabla_nueva) return false;

    hash->capacidad = capacidad_nueva;
    hash->tabla = tabla_nueva;
    hash->cantidad = 0; //reinicio cantidad, en hash_guardar se vuelve a contar.

    for (long i = 0; i < capacidad_nueva; ++i){ //asigno default a toda mi tabla nueva.
        tabla_nueva[i].estado = VACIO;
        tabla_nueva[i].clave = NULL;
        tabla_nueva[i].valor = NULL;
    }

    for (long i = 0; i < capacidad_anterior; ++i){ //guardo valores.
        if (tabla_anterior[i].estado == OCUPADO){
            hash_guardar(hash,tabla_anterior[i].clave,tabla_anterior[i].valor);
            free(tabla_anterior[i].clave);
        }
    }
    free(tabla_anterior);
    return true;
}

/*------------------------------------------- PRIMITIVAS -------------------------------------------*/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t *hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;

    hash->tabla = malloc(sizeof(campo_t)*CAPACIDAD_INCIAL);
    if (!hash->tabla){
        free(hash);
        return NULL;
    }

    for (int i = 0; i < CAPACIDAD_INCIAL; ++i){
        hash->tabla[i].estado = VACIO;
        hash->tabla[i].clave = NULL;
        hash->tabla[i].valor = NULL;
    }

    hash->capacidad = CAPACIDAD_INCIAL;
    hash->cantidad = 0;
    hash->funcion_destruccion = destruir_dato;

    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    if((hash->cantidad + 1)/ hash->capacidad >= FACTOR_CARGA){
        if(!redimensionar(hash)){
            return false;
        }
    }

    unsigned long pos;
    bool ya_esta = buscar_pos_clave(hash,clave, &pos); //me fijo si esta la clave, la guardo en pos
    if(ya_esta){ //Existe la clave,solo tengo q deshacerme del valor anterior y poner el nuevo.
        if(hash->funcion_destruccion){
            hash->funcion_destruccion(hash->tabla[pos].valor);
        }
    
    }else{ //tengo q encontrarle su lugar y guardar todo
        pos = calcular_posicion(hash,clave); //calculo el valor de pos.
        hash->tabla[pos].clave = strdup(clave);
        hash->tabla[pos].estado = OCUPADO;
        hash->cantidad++;
    }
    hash->tabla[pos].valor = dato;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    long pos;
    bool ya_esta = buscar_pos_clave(hash,clave, &pos);
    if(!ya_esta){ //no esta
        return NULL;
    }
    
    void *valor = hash->tabla[pos].valor; //guardo valor
    free(hash->tabla[pos].clave); //libero clave

    hash->tabla[pos].clave = NULL;
    hash->tabla[pos].estado = BORRADO;
    hash->cantidad--;
    return valor;
}

void *hash_obtener(const hash_t *hash, const char *clave){
    long pos;
    bool ya_esta = buscar_pos_clave(hash,clave, &pos);
    if(!ya_esta){
        return NULL;
    }
    return hash->tabla[pos].valor;
}


bool hash_pertenece(const hash_t *hash, const char *clave){
    return buscar_pos_clave(hash,clave, NULL);; 
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

void hash_destruir(hash_t *hash){
    
    for (int i = 0; i < hash->capacidad; ++i){
        
        free(hash->tabla[i].clave);
        if(hash->funcion_destruccion && hash->tabla[i].estado == OCUPADO){
            hash->funcion_destruccion(hash->tabla[i].valor);
        }
    }
    free(hash->tabla);
    free(hash);
}

/*------------------------------------------- ITERADOR -------------------------------------------*/
struct hash_iter{
  const hash_t* hash;
  campo_t campo_act;
  size_t posicion;
  size_t recorridos;
};
/*------------------------------------------- AUX ITERADOR -------------------------------------------*/
void iter_avanzar_prox_ocupado(hash_iter_t *iter, bool posicionado){
    
    if(!posicionado){ //lo paro en 0 pq no estaba en ningun lado
        iter->posicion = 0;
    }else if((iter->posicion + 1) < iter->hash->capacidad){ 
        iter->posicion++;
    }
    while( iter->hash->tabla[iter->posicion].estado != OCUPADO && (iter->posicion + 1) < iter->hash->capacidad ){
        iter->posicion++;
    }
}
/*------------------------------------------- PRIMITIVAS ITERADOR -------------------------------------------*/

hash_iter_t *hash_iter_crear(const hash_t *hash){
    
    hash_iter_t * iter = malloc(sizeof(hash_iter_t));
    if(!iter) return NULL;
    iter->hash = hash;  

    if(hash->cantidad != 0){
        iter_avanzar_prox_ocupado(iter,false); 
        iter->campo_act = hash->tabla[iter->posicion];
    }else{ //se que va a ser un vacio.
        iter->posicion = 0; 
        iter->campo_act = hash->tabla[iter->posicion];
    }

    iter->recorridos = 0;
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    if(hash_iter_al_final(iter)) return false;
    
    iter_avanzar_prox_ocupado(iter,true); 
    iter->recorridos++;
    iter->campo_act = iter->hash->tabla[iter->posicion];
    
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    return (iter->campo_act).clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return (iter->recorridos == iter->hash->cantidad)? true:false;
}

void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}