#include "calc_helper.h"
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ESPACIO_INICIAL 10000

const char* operacion[] = {"+","-", "*","/", "^"};

int prec(struct calc_token *token);
bool convertor(char **strv);


//Recibe notacion infix y devuelve notacion postfix
// EJ: recibe por consola "2 + 2" devuelve: "2 2 +"
//requiere espacios entre numeros y operadores.

int main(int argc, char const *argv[]){
	char *recibido = malloc(sizeof(char)* ESPACIO_INICIAL);

	while(fgets(recibido,ESPACIO_INICIAL,stdin)){
		char ** convertir = infix_split(recibido);

		if (convertir != NULL){
			convertor(convertir);
			printf("\n");
		}

		free_strv(convertir);
	}
	free(recibido);
	return 0;
}


/*----------------------------------------Funciones Auxiliares----------------------------------------*/

int prec(struct calc_token *token){
	return token->oper.prec;
}

/*---------------------------------------- Convertor ----------------------------------------*/

bool convertor(char **strv){ //ya esta validado 

	pila_t *op = pila_crear();
	if(!op){
		free(op);
		return false;
	}

	int actual = 0;

	while(strv[actual]){
		
		struct calc_token *token = malloc(sizeof(struct calc_token));		

		calc_parse(strv[actual],token);
		
		if (token->type == TOK_NUM){
			fprintf(stdout,"%ld ",token->value);
			free(token);
		
		}else if (token->type == TOK_OPER){
			
			struct calc_token* tope_op = pila_ver_tope(op);
			
			while(tope_op && (prec(tope_op)>prec(token) || (prec(tope_op)==prec(token) && token->oper.op != OP_POW)) && (token->type!=TOK_LPAREN)){
				struct calc_token* mostrar = pila_desapilar(op);
				fprintf(stdout,"%s ",operacion[mostrar->oper.op]);
				free(mostrar);
				tope_op = pila_ver_tope(op);

			}
			pila_apilar(op,token);	

		}else if(token->type == TOK_LPAREN){
			pila_apilar(op,token);

		}else if(token->type == TOK_RPAREN){

			struct calc_token* tope_op = pila_ver_tope(op);
			while(tope_op->type != TOK_LPAREN && tope_op!=NULL){

				struct calc_token* mostrar = pila_desapilar(op);
				fprintf(stdout,"%s ",operacion[mostrar->oper.op]);
				free(mostrar);
				tope_op = pila_ver_tope(op);
			}
			if (tope_op->type == TOK_LPAREN){
				struct calc_token* parentesis = pila_desapilar(op);
				free(parentesis);
			}
			free(token);	
		}
		actual++;
	}
	while(!pila_esta_vacia(op)){
		struct calc_token* mostrar = pila_desapilar(op);
		fprintf(stdout,"%s ",operacion[mostrar->oper.op]);
		free(mostrar);
	}
	pila_destruir(op);
	return true;
}

