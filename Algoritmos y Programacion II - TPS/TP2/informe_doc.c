#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include "doctores.h"
#include "informe_doc.h"
#include <stdio.h>
void _hash_destruir(void* hash);

void _hash_destruir(void* hash){ //wrapper
    hash_destruir((hash_t *)hash);
}

void informe_doctor(doctores_t* doctores, char* inicio, char* fin)
{
    lista_t* lista_doctores = lista_crear();
    
    recorrer_doctores(doctores, inicio, fin, guardar_visitados, lista_doctores);

    size_t cantidad = lista_largo(lista_doctores);
    printf(DOCTORES_SISTEMA, cantidad);

    lista_iter_t *iter = lista_iter_crear(lista_doctores);
    size_t n_doctor = 1;
    hash_t* hash = NULL;

    while(!lista_iter_al_final(iter)){
        hash = (hash_t *) lista_iter_ver_actual(iter);
        char* doc_nombre = (char*)hash_obtener(hash,"nombre");
        char* doc_especialidad = (char*)hash_obtener(hash,"especialidad");
        size_t* doc_atendidos = (size_t*) hash_obtener(hash,"atendidos");
        
        printf(INFORME_DOCTOR, n_doctor,doc_nombre,doc_especialidad,*doc_atendidos);

        n_doctor++;
        lista_iter_avanzar(iter);

    }

    lista_iter_destruir(iter);
    lista_destruir(lista_doctores, _hash_destruir);
}