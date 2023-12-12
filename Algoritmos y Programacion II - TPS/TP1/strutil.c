#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *strndup(char *str, int chars){
    char *buffer;
    int n;

    buffer = (char *) malloc(chars +1);
    if (buffer)
    {
        for (n = 0; ((n < chars) && (str[n] != 0)) ; n++) buffer[n] = str[n];
        buffer[n] = 0;
    }

    return buffer;
}

/* --------------------------------Estructuras Auxiliares--------------------------------*/
/*Cuenta la cantidad de separadores en una cadena. Recibe el separador que se desee contar y la cadena,
devuelve la cantidad de apariciones en la cadena.*/
int cantidad_sep(const char *str, char sep){
    int cant_sep = 0;
    for (size_t i = 0; i < strlen(str); ++i){
        if (str[i]==sep){
            cant_sep++;
        }
    }
    return cant_sep;
}

/*Devuelve un size_t que indica el largo de la cadena principal, sin contar la ultima posicion (NULL)*/
size_t largo_cadena_principal(char ** strv){
    size_t contador = 0;
    for (int i = 0; strv[i] != NULL; ++i){
        contador++;
    } 
    return contador;
}

/*Devuelve el largo de las subcadenas considerando el separador a usar, en caso de ser "\0",como los separadores
no usaran un espacio, el numero difiere. Se tiene en cuenta el \0 final.*/
size_t largo_subcadenas (char **strv, size_t largo_strv,char separador){
    size_t total = 0;
    for (int i = 0; i < largo_strv; ++i){
        total += strlen(strv[i]);
        if (separador != '\0'){
            total++;
        }
    }
    return (separador != '\0')? total: total+1;
}

/* -------------------------------- Funciones a implementar --------------------------------*/

char *substr(const char *str, size_t n){
    char *cadena = strndup(str,n);
    return cadena;
}


char **split(const char *str, char sep){

    int cant_sep = cantidad_sep(str,sep);    
    char **cadena = malloc((cant_sep+2)*sizeof(char*));
    if (cadena == NULL){
        return NULL;
    }
    
    int largo = (int) strlen(str);
    int ultimo_sep = -1;
    int actual = 0;
    for (int j = 0;j < largo; ++j){
       
        if (str[j]==sep){     
            if (ultimo_sep == -1){ //copio desde el principio al separador
                cadena[actual] = strndup(str, j);
            }else{
                cadena[actual] = strndup(str+ultimo_sep+1, j-ultimo_sep-1); //copio del separador+1 al prox separador-1
            }
            ultimo_sep = j;    
            actual++;                
        }
    }
    if(ultimo_sep != largo){
      cadena[actual]= strndup(str+ultimo_sep+1, largo-ultimo_sep); //copio del ultimo sep+1 hasta el final
      actual++;
    }
    cadena[actual] = NULL;
    return cadena;
}

char *join(char **strv, char sep){
   
    char separador[] = {sep,'\0'};
    size_t largo_strv = largo_cadena_principal(strv);
    if (largo_strv == 0){
        char *vacia = malloc(sizeof(char));
        vacia[0] = '\0';
        return vacia;
    }
    
    size_t largo_final = largo_subcadenas(strv,largo_strv,separador[0]);
    char *cadena = malloc(sizeof(char)*(largo_final));
    if (cadena == NULL){
        return NULL;
    }

    int i=0;
    int j=0;
    int pos_char = 0;
    while(i<largo_strv){
        if (strv[i][j] != '\0'){
          cadena[pos_char]= strv[i][j];
          pos_char++;
          j++;
        
        }else{
          if(i+1 < largo_strv && separador[0]!='\0'){ //Coloco separador
            cadena[pos_char]= separador[0];
            pos_char++;
          } 
          i++; //reinicio j y avanzo en 1 en i.
          j=0;
        }
    }
    cadena[largo_final-1]='\0'; //Termino la cadena
    return cadena;
}  

void free_strv(char *strv[]){
	size_t largo_strv = largo_cadena_principal(strv);
	for (int i = 0; i < largo_strv; ++i){
		free(strv[i]);
	}
	free(strv);
}

