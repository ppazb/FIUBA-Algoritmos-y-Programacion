#ifndef TP2_INFORME_DOCTORES_H
#define TP2_INFORME_DOCTORES_H
#include "Data Structures/hash.h"
#include "Data Structures/heap.h"
#include "Data Structures/cola.h"
#include "mensajes.h"
#include "Data Structures/abb.h"
#include "Data Structures/lista.h"

/*Recibe un ABB con los doctores y un rango e imprime por salida estandar alfabeticamente los nombres,especialidad y cantidad de atendidos
que se encuentren entre los dos nombres dados. De no recibir uno de los dos nombres, se toma desde el principio/fin.*/
void informe_doctor(doctores_t* doctores, char* inicio, char* fin);
/* Recibe un ABB, una lista vacia, un contador y un rango, y almacena alfabticamente en la lista los nombres que se encuentren en ese rango.
La cantidad de nombres almacenados se guarda en el contador.*/
#endif //TP2_INFORME_DOCTORES_H

