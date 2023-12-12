#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include "Data Structures/strutil.h"
#include "mensajes.h"
#include "funciones_auxiliares.h"
#include "doctores.h"
#include "paciente.h"
#include "especialidades.h"
#include "csv.h"
#include "Data Structures/cola.h"
#include "Data Structures/heap.h"
#include "pedir_turno.h"
#include "atender.h"
#include "informe_doc.h"
#define CADENA_VACIA ""
#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"
#define REGULAR "REGULAR"
#define URGENTE "URGENTE"
#define CANT_PARAMETROS_INFORME 2
#define CANT_PARAMETROS_PEDIR_TURNO 3
#define CANT_PARAMETROS_ATENDER 1

//----------------------------------------------------------------------------------------------------------------------
void procesar_comando(char* comando,  char** parametros, doctores_t* doctores, pacientes_t* pacientes, especialidades_t* especialidades);
void procesar_entrada(doctores_t* dict_doctores, pacientes_t* pacientes, especialidades_t* especialidades);
void cargar_doctores_Yespecialidades(lista_iter_t* iter_doc,especialidades_t* especialidades, doctores_t* dict_doctores);
void cargar_pacientes(lista_iter_t* iter_pac, pacientes_t* pacientes);
void destruir_estructuras(pacientes_t* pacientes, especialidades_t* especialidades, doctores_t* doctores);

void procesar_comando(char* comando,  char** parametros, doctores_t* doctores, pacientes_t* pacientes, especialidades_t* especialidades)
{
    /* Se recibe el comando desde procesar entrada, y efectua la respectiva operacion, en caso de error, muestra por salida estandar, el res
     * pectivo error*/
    bool se_puede_operar = true;
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0)
	{
        if (!pacientes_pertenece(pacientes,parametros[0]))
        {
            printf(ENOENT_PACIENTE, parametros[0]);
            se_puede_operar = false;
        }
        if (!especialidades_pertenece(especialidades, parametros[1]))
        {
            printf(ENOENT_ESPECIALIDAD, parametros[1]);
            se_puede_operar = false;
        }
        if (strcmp(parametros[2],REGULAR ) != 0 && strcmp(parametros[2], URGENTE) != 0)
        {
            printf(ENOENT_URGENCIA, parametros[2]);
            se_puede_operar = false;
        }
        if (cantidad_parametros_valida(parametros) != CANT_PARAMETROS_PEDIR_TURNO)
        {
        	printf(ENOENT_PARAMS, comando);
        	se_puede_operar = false;
        }
        if (se_puede_operar) procesar_turno(parametros[0], parametros[1], parametros[2], pacientes, especialidades);

	} else if (strcmp(comando, COMANDO_ATENDER) == 0)
	{
        if (!doctores_pertenece(doctores, parametros[0]))
        {
            printf(ENOENT_DOCTOR,parametros[0]);
            se_puede_operar = false;
        } 
        if (cantidad_parametros_valida(parametros) != CANT_PARAMETROS_ATENDER)
        {
        	printf(ENOENT_PARAMS, comando);
        	se_puede_operar = false;
        }
        if(se_puede_operar) atender_siguiente(parametros[0],doctores, especialidades);
	} else if (strcmp(comando, COMANDO_INFORME) == 0)
	{
        char* doctor1 = parametros[0];
        char* doctor2 = parametros[1];
        if (!doctor2)
        {
        	printf(ENOENT_PARAMS,comando);
        	se_puede_operar = false;
        }
        if(se_puede_operar) informe_doctor(doctores, doctor1, doctor2);
	} else
	    {
            printf(ENOENT_CMD,comando);
	}
}

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

void procesar_entrada(doctores_t* doctores, pacientes_t* pacientes, especialidades_t* especialidades)
{
    /*Procesa por el comando ingresado por teclado y llama a procesar entrada para efectuar, la operacion correspondiente
     * en caso de entrar un comando en formato erroneo, lo comunica por salida estandar*/
	char* linea = NULL;
	size_t c = 0;
	while (getline(&linea, &c, stdin) > 0) {
		eliminar_fin_linea(linea);
        if (strcmp(linea,CADENA_VACIA) == 0) break;
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;	
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], parametros, doctores, pacientes, especialidades);
		free_strv(parametros);
		free_strv(campos);

	}
	free(linea);
}

void cargar_doctores_Yespecialidades(lista_iter_t* iter_doc, especialidades_t* especialidades, doctores_t* doctores)
{
    /*Recibe un iterador de lista, con los doctores cargados en el sitema, 3 diccionarios, doctores, especialidades, especialidades urgente
     * respectivamente y procede a cargar dichos diccionarios con la informacion necesarioa para operar el sistema*/
    char** campos_actual = NULL;
    char* nombre_doctor = NULL;
    char* especialidad = NULL;
    while(!lista_iter_al_final(iter_doc))
    {
        campos_actual = (char**)lista_iter_ver_actual(iter_doc);
        nombre_doctor = campos_actual[0];
        especialidad = campos_actual[1];
        if (!doctores_pertenece(doctores, nombre_doctor))
        {
            doctor_agregar(doctores, nombre_doctor, especialidad);
        }
        if (!especialidades_pertenece(especialidades, especialidad))
        {
            especialidades_agregar(especialidades, especialidad);
        }
        lista_iter_avanzar(iter_doc);
    }
    lista_iter_destruir(iter_doc);
}

/*Es probable que esto cuente como repiticion de codigo, pero nos parecio una solucion mas eficiente y entendible
  hacerlo de esta manera que confecionar todo en una funcion */

void cargar_pacientes(lista_iter_t * iter_pac, pacientes_t* pacientes){
    /*Recibe un iterador de lista, con los pacientes cargados en el sitema y un diccionario de pacientes,
     * procede a cargar dicho diccionario con la informacion necesaria para operar el sistema*/
    char** campos_actual = NULL;
    char* nombre_paciente = NULL;
    char* antiguedad = NULL;
    while(!lista_iter_al_final(iter_pac))
    {
        campos_actual = (char**)lista_iter_ver_actual(iter_pac);
        nombre_paciente = campos_actual[0];
        antiguedad = campos_actual[1];
        if (!pacientes_pertenece(pacientes, nombre_paciente))
        {
            pacientes_guardar(pacientes, nombre_paciente, antiguedad);
        }
        lista_iter_avanzar(iter_pac);
    }
    lista_iter_destruir(iter_pac);
}


void destruir_estructuras(pacientes_t* pacientes, especialidades_t* especialidades, doctores_t* doctores)
{
    /*llama a las respectivas funciones de destruccion de cada estructura utilizada*/
    destruir_pacientes(pacientes);
    especialidades_destruir(especialidades);
    destruir_doctores(doctores);
}

int main(int argc, char** argv) 
{
    for (int i = 0; i < 2; ++i) {
        if (!argv[i]){
            printf(ENOENT_CANT_PARAMS);
            return -1;
        }
    }
	lista_t* lista_doc = lectura_csv(argv[1]);
	lista_t* lista_paciente = lectura_csv(argv[2]);
	if (!lista_doc || !lista_paciente ) return -1; //es necesario comprobarlo antes ya que de otra manera se puede dar error en el iterador
	lista_iter_t* iter_doc = lista_iter_crear(lista_doc);
	lista_iter_t* iter_pac = lista_iter_crear(lista_paciente);
	pacientes_t* pacientes = crear_pacientes();
	doctores_t* dict_doctores = doctores_crear();
	especialidades_t* especialidades = especialidades_crear();
    if (!iter_doc || !iter_pac || !pacientes || !especialidades || !dict_doctores) return -1;
    cargar_doctores_Yespecialidades(iter_doc, especialidades, dict_doctores);
    cargar_pacientes(iter_pac, pacientes);
    lista_destruir(lista_doc, borrar_creador); //las destruimos de manera aparte porque una vez cargadas las estructuras en el sistema
    lista_destruir(lista_paciente, borrar_creador);// no son necesarias y consumen memoria, sin ningun uso
    procesar_entrada(dict_doctores, pacientes, especialidades);
    destruir_estructuras(pacientes, especialidades, dict_doctores);
	return 0;
}
