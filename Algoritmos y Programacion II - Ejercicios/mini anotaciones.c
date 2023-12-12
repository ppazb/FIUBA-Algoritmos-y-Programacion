GALERIAS
- #include <stdio.h> //printf , vscanf , fopen , fclose
- #include <stdbool.h> //bool
- #include <stddef.h> //NULL size_t etc
- #include <string.h>
///////////////////////////////////////////////////////

SIEMPRE PONER: #include "archivo.h"
#define VACIO NULL
#define CANTIDAD 5  //no poner ;
///////////////////////////////////////////////////////

PRINTF - Format specifiers
int numero = 5;
printf("%i \n", numero);

- %p direc puntero.
- %c char
- %d unsigned int 
- %f float
- %lf long double
- %s string 
///////////////////////////////////////////////////////

OPERADOR TERNARIO
condicion? true : false;
///////////////////////////////////////////////////////

RETURN DE UNA LINEA
if (condicion)return valor;
	si la funcion es void no hay que poner return.
///////////////////////////////////////////////////////

OPERADORES
&& and
|| or 
///////////////////////////////////////////////////////

DECLARAR VARIABLES 
Del mismo tipo: int a=2, b=3;
Cadenas:
	char cadena[2] ="ab";
	char cadena[] = {"a","b"};
		//En ambos casos son char* a la hora de usarlos como variable

	char valor = 'A' + 1 = 'B';
///////////////////////////////////////////////////////

MEMORIA
- int *vector = malloc(sizeof(int)*10); //vector dinamico
- int vector[10] //vector estatico, no lo puedo modificar en tiempo de ejecucion
- *(vector+3) = valor;
- vector[3] = valor;

+ char *cadena = malloc(sizeof(char)*n)
+ cadena[0 a n] = caracter / "\0" (caso declarar cadena vacia)

char cadena[] = {'h', 'o', 'l', 'a', '\n'};
char cadena[] = "hola\n";
char* cadena = "hola\n";


- funcion ( void* array[]) //Puntero a array de punteros (no existe void** como parametro, si existe char** etc)

- Calloc(cantidad, sizeof()) //lo inicializa en 0
- Malloc(cantidad*sizeof())

Realloc es in-place, si no puede modificar no modifica lo original y devuelve NULL.
Sino devuelve un puntero a la nueva memoria.

Tengo que inicializar los void* /int* con malloc, pq si 
simplemente declaro int*puntero no reserve memoria, solo sabe
que va a haber un puntero ahi. Podria si hacer int numero y dsps int*pnum = &numero


Yo inicializo a NULL para saber que esta en un puntero invalido, por lo que puedo
verificar si salio bien o mal el proceso y no acceder a lo que tiene adentro.
///////////////////////////////////////////////////////

FUNCION: NO ES PRIMITIVA, NO PUEDO ACCEDER A LA ESTRUCTURA.


///////////////////////////////////////////////////////


TDAS 

+ VECTOR: tam y datos void* //(datos como puntero continuo en memoria)

+ PILA: cantidad , capacidad , void** datos //(como serie de punteros continuos en memoria q almacenan 
	//direciones en memoria)
	//Redimenciono cndo cantidad*4<capacidad o capaciodad==cantidad
	//La REDIMENCION=2 -> es capacidad */ REDIMENCION * sizeof(void*)

+ NODO: void*dato , nodo_t* nodo_prox (u struct nodo* prox so no declare arriba)

+ COLA: nodo_t*primero , nodo_t*ultimo

+ LISTA: nodo_t*prim , nodo_t*ult , size_t largo
			
		+ ITER EXTERNO: nodo_t*anterior , nodo_t*actual , lista_t*lista.
			-crear iter
			-avanzar
			-ver actual
			-al_final
			-destruir
			-insertar
			-borrar actual

		+ ITER INTERNO: recorre y aplica funcion
			- lista_iterar(lista_t* lista, bool visitar(void))

+ HASH: diccionario: tiene calve y valor DICCIONARIO. funciona con funcion de hashing.
		- Ventaja de funcionar en O(1)
		- Destruir es en O(n) por liberar claves primero. 


+ ABB:

	- Pre order: raiz, izq, derecha.
	- Post order: izq , derecha, raiz.
	- In order: todo izq, raiz, derecha.
	//Siempre va primero la izquierda y dsps la derecha- la Raiz va en el pos 
	//indicada por pre,in,post.

///////////////////////////////////////////////////////


PARAMETRO FUNCION:
void (*destruir_dato)(void*):
	- void: que devuelve la funcion
	- nombre que toma la variable
	- (void*) que datos recibe la funcion

Dentro de la funcion:
	-destruir_dato(valor);

Modificar numero en struct (++,--):
- lista -> largo += 1;
///////////////////////////////////////////////////////


FUNCIONES UTILES:

	strndup(char*,n) = /*recibe un puntero a un str y un numero y genera una copia de los 
primeros n caracteres. Si n es 0, devuelve una cadena vacia (termina todo en \0)*/
	
	int matriz1[5][5];
	memset(matriz,0,5*5*sizeof(int)); 
	Acceder1 [3][2] = matriz[3][2];

	tambien puedo hacer:
	int** matriz = malloc(sizeof(int)*5)
	for (int i = 0; i < 5; ++i)
	{
		matriz[i] = malloc(sizeof(int)*5)
	}

	int sprintf(char *buffer_str, const char *string,etc);
	str buffer[20];
	sprintf(buffer, "La fraccion es: %d/%d",numerador,denominador);

///////////////////////////////////////////////////////

 
COMPLEJIDAD - Utilizacion de tiempo y espacio.
- Es un modelo no dice cuanto va a tardar, eso tambien depiende del hardware y otros factores
, no da un valor absoluto, sino que me da una forma de comparar, en la realidad no va a tardar
lo que nos da T(n) [tiempo de ejecucion con entrada de tamaño n].

- medicion comparativa no absoluta = la medida q me da no es tiempo, es para comparar
medida comparativa de algoritmos.

- Los /*tiempos de ejecicion*/ entre dos algoritmos es c.T(n) vs T(n)

- Big O ->T(n) = O(f(n)) = notacion asintotica, acota superiormente el tiempo de ejecucion. 
Describe el comportamiento de una funcion en el infinito.

 				T(n) = a.T(n/b) + f(n)
 				a: cant de llamadas recursivas.
 				b: en cuanto divido el problema
 				f(n): suele ser , es el costo de dividir el problema y unir la solucion.

 				/*logb(a) < c:*/ O( n^c)
 				/*logb(a) = c:*/ O( n^c * logb(n))
 				/*logb(a) > c:*/ O( n^logb(a))

BACKTRAKING


ARBOL
ARBOL BINARIO: cada nodo solo puede tener 2 hijos.