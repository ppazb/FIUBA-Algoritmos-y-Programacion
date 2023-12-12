#include "calc_helper.h"
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ESPACIO_INICIAL 250
#define BASE_MINIMA 2
#define ARGUMENTO_MINIMO 0
#define MINIMO_EXP_POT 0 
#define DIVISION_CERO 0

bool validar(char **cadena);
bool cuentas(struct calc_token *token, pilanum_t *pila);
bool calcular(char **strv, calc_num *final);
size_t largo_cadena(char ** strv);


//Calculadora con notacion postfix
//Ejemplo: recibe por consola "2 2 +" devuelve: 4
//requiere espacios entre numeros y operadores.

int main(int argc, char const *argv[]){
	char *recibido = malloc(sizeof(char)* ESPACIO_INICIAL);
	if (!recibido){
		fprintf(stdout, "Memoria insuficiente\n");
		free(recibido);
		return 1;
	}

	while(fgets(recibido,ESPACIO_INICIAL,stdin)){
		char ** calculo = dc_split(recibido);

		if (calculo != NULL){
			bool valido = validar(calculo);
			if(valido == true){
				calc_num n;
				bool sin_error = calcular(calculo,&n);
				if (sin_error==true){
					printf("%ld\n",n);
				}
			}
		}
		free_strv(calculo);
	}
	free(recibido);
	return 0;
}

/*----------------------------------------Funciones Auxiliares----------------------------------------*/
//Recibe un char ** y devuelve el largo de la cadena principal, sin contar el NULL.
size_t largo_cadena(char ** strv){
    size_t contador = 0;
    for (int i = 0; strv[i] != NULL; ++i){
        contador++;
    } 
    return contador;
}

//Recibe un char** con los operandos y operadores que seran usados para el calculo.
//Valida que la entrada sea valida, es decir que sea un token y que no tenga parentesis. Devuelve true y de no ser valido false.
bool validar(char **cadena){

	struct calc_token *token = malloc(sizeof(struct calc_token));
	for (int i = 0; i<largo_cadena(cadena); ++i){
		bool valido = calc_parse(cadena[i],token);
		
		if (valido == false || token->type == TOK_LPAREN || token->type == TOK_RPAREN){//algun caracter no es valido
			free(token);
			fprintf(stdout, "ERROR\n");
			return false;
		}
	}
	free(token);
	return true;
}

//Calcula la potencia de un numero. Recibe la base y el exponente. Devuelve el resultado (calc_num=long int)
calc_num potencia(calc_num a, calc_num b){
	if (b == 0){ 
		return 1;
	}
    return a*potencia(a,b-1);
}

/*----------------------------------------Funciones para calculos----------------------------------------*/


bool calcular(char **strv, calc_num *final){
	
	pilanum_t *pila = pilanum_crear();
	if(!pila){
		pilanum_destruir(pila);
		fprintf(stdout, "Memoria insuficiente\n");
		return false;
	}

	for (int i = 0; i<largo_cadena(strv); ++i){
		
		struct calc_token *token = malloc(sizeof(struct calc_token));
		calc_parse(strv[i],token);

		if (token->type == TOK_NUM){
			apilar_num(pila, token->value);
		}else{ //es operador
			if (cuentas(token,pila) == false){
				fprintf(stdout, "ERROR\n");
				pilanum_destruir(pila);
				free(token);
				return false;
			}
		}
		free(token);
	}
	desapilar_num(pila,final);
	if (!pila_esta_vacia(pila)){ //sobran numeros.
		fprintf(stdout, "ERROR\n");
		pilanum_destruir(pila);
		return false;
	}
	pilanum_destruir(pila);
	return true;
}

//Calcula los valores al recibir un token = operando y una pila con numeros. De faltar numeros o 
//no cumplir con requisitos matematicos, devuelve false. 
bool cuentas(struct calc_token *token, pilanum_t *pila){ 
	if (token->oper.op == OP_RAIZ){ //Raiz: solo desapilo un valor
		calc_num n;
		bool num = desapilar_num(pila, &n);
		if ( num==false || n<0){ //No existe o es negativo.
			return false;
		}else{
			double valor_double = sqrt((double)n);
			calc_num v_final= (calc_num) valor_double;
			apilar_num(pila, v_final); //raiz
			return true;
		}
	}

	calc_num n1,n2; //necesito dos valores.
	bool num1 = desapilar_num(pila, &n2);
	bool num2 = desapilar_num(pila, &n1);
	if (num1==false || num2==false){
		return false;
	}

	if (token->oper.op == OP_ADD){ //suma
		apilar_num(pila, n1+n2);

	}else if(token->oper.op == OP_SUB){ //resta
		apilar_num(pila, n1-n2);
	
	}else if(token->oper.op == OP_MUL){ //multipl
		apilar_num(pila, n1*n2);

	}else if(token->oper.op == OP_DIV){ //division
		if (n2 == DIVISION_CERO){
			return false;
		}
		apilar_num(pila, n1/n2);

	}else if (token->oper.op == OP_POW){//potencia
		if(n2< MINIMO_EXP_POT){
			return false;
		}
		apilar_num(pila, potencia(n1,n2));

	}else if (token->oper.op == OP_LOG){ //log
		if (n1< ARGUMENTO_MINIMO || n2< BASE_MINIMA){
			return false;
		}else{
			double valor = (log((double)n1)/log((double)n2));
			calc_num final= (calc_num) valor;
			apilar_num(pila, final);
		}	
	
	}else{ //Ternario
		calc_num n0;
		bool num0 = desapilar_num(pila, &n0);
		if (num0 == false){
			return false;
		}else{
				apilar_num(pila, n0?n1:n2);
		}	
	}
	return true; //No entro en ningun false.
}


