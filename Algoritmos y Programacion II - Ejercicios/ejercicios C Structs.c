
typedef struct fraccion{
	int numerador;
	int denominador;
} fraccion_t;


void simplificar_fracion(int* num, int*den);

fraccion_t* fraccion_crear(int numerador, int denominador){
	/*No puede ser 0 el denominador
	Puede se tanto positivo como negativo
	Despues la simplifico*/
	fraccion_t* fraccion = malloc(sizeof(fraccion_t));
	if(!fraccion) return NULL;

	if(denominador == 0){
		free(fraccion);
		return NULL;
	}

	if(numerador<0 && denominador<0){ //queda positivo
		numerador *= -1;
		denominador *= -1;
	}
	if(numerador * denominador < 0 && denominador<0){ //siempre pongo nomin negativo.
		denominador *= -1;
		numerador *= -1;
	}

	simplificar_fracion(&numerador,&denominador);
	fraccion->denominador = denominador;
	fraccion->numerador = numerador;
	return fraccion_t;
}

//Devuelve el valor absoluto
int absoluto(int valor){
	int (valor<0? valor * (-1) : valor );
}

//Devuelve el minimo absoluto
int min(int n1, int n2){
	int num1 = absoluto(n1);
	int num2 = absoluto(n2);
	return (num1<num2? num1 : num2);
}

void simplificar_fracion(int* num, int*denom){
	//Busco comun denominador y de ahi divido. Siempre es al menor absoluto lamitad del minimo.
	int actual = min(*num,*denom);

	if(*num%actual == 0 && *denom%actual == 0){
		*num /= actual;
		*denom /= actual;
	}else{
		actual -= 1;
	}
}

//pre: ambas fracciones existen.
fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2){
	//Suma: nom1*den2 + nom2*dom1 / dom1*dom2
	fraccion_t* suma = malloc(sizeof(fraccion_t));
	if(!suma) return NULL;

	int denominador = f1->denominador * f2->denominador;
	int n1 = f1->numerador * f2->denominador;
	int n2 = f2->numerador * f2->denominador;

	suma->numerador = n1+n2;
	suma->denominador = denominador;
	return suma;
}


char* fraccion_representacion(fraccion_t* fraccion);
//tengo que calcular el largo del buffer: si es fraccion /, si es negativo un espacio, etc
int fraccion_parte_entera(fraccion_t* fraccion){
	return fraccion->numerador/fraccion->denominador;
}


/*********************************************************************************************************************/
/* Implementar en C el TDA ComposiciónFunciones que emula la composición de funciones (i.e. f(g(h(x))).
 * Se debe definir la estructura del TDA, y las siguientes primitivas:
 * -----composicion_t* composicion_crear()
 * -----void composicion_destruir(composicion_t*)
 * -----bool composicion_agregar_funcion(composicion_t*, double (*f)(double))
 * -----double composicion_aplicar(composicion_t*, double)
 * Considerar que primero se irán agregando las funciones como se leen, pero tener en cuenta el correcto
 * orden de aplicación. Por ejemplo: para emular f(g(x)), se debe hacer:
 * 1) composicion_agregar_funcion(composicion, f);
 * 2) composicion_agregar_funcion(composicion, g);
 * 3) composicion_aplicar(composicion, x);
 * Indicar el orden de las primitivas.
*/

typedef struct composicion{
	pila_t * funciones;
}composicion_t;


composicion_t* composicion_crear(){
	composicion_t* composicion = malloc(sizeof(composicion_t));
	if(!composicion_t) return NULL;

	pila_t *funciones = pila_crear();
	if(!funciones){
		free(composicion);
		return NULL
	}

	composicion->funciones = funciones;
	return composicion;
}

void composicion_destruir(composicion_t* composicion){
	pila_destruir(composicion->funciones);
	free(composicion);
}
bool composicion_agregar_funcion(composicion_t* cmp, double (*f)(double)){
	if(!f) return false;
	return pila_apliar(composicion->funciones,f);
}

double composicion_aplicar(composicion_t* composicion, double x){
	double resultado;
	while(pila_esta_vacia(composicion->funciones) == false){
		resultado = (double)(pila_desapilar(composicion->funciones))(resultado);
	}
	return resultado;
}

/*
ERRORES:
	- Castear la funcion a (double) una vez que la desapilo. NO TIENE QUE SER DOUBLE*
	- No necesito dejar la pila como antes, sino tendria que usar cola aux.
	- No checkee si f existia antes de apilarla. 
	- No hacer return pila_apilar, que de por si no puedo saber q va a ser true siempre.*/
