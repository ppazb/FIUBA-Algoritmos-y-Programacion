#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool _son_iguales (int arr[], int inicio, int fin){
    if(inicio+1 == fin){  //condicion de corte a checkear si true o false
        return arr[inicio] == arr[fin];
    }
    int medio = (inicio + fin) / 2;
    return (_son_iguales(arr,inicio,medio ) && _son_iguales(arr,medio, fin));
}
//Teorema maestro: T(n) = a.T(n/b) + f(n)
// a=2 (cant de llamadas recursivas) b= 2 (cuanto se divida el problema) c= 0 costo de dividir y unir = 0
//T(n) = 2*T(n/2) + o(1)
//logb(a) = log2(2) = 1 > c => O(n^log2(2) = O(n)


bool son_iguales (int arr[], int largo){
    if(largo <= 1) return true; //siempre va a ser true //Es o(1) no toma complejidad
    return  _son_iguales(arr, 0, largo-1); //largo-1 pq no puedo evaluar en largo.
}

//Recibe un array, su posicion inicial y final y devuelve su maximo.
int maximo(int arr[], int inicio, int fin){
    if(inicio == fin){
        return arr[inicio];
    }
    int medio = (inicio+fin)/2;
    int max_der = maximo(arr,inicio,medio);
    int max_izq = maximo(arr,medio+1,fin);
    return max_der >= max_izq? max_der : max_izq;
}


/*
Se tiene un arreglo en forma de "pico". Esto quiere decir, que inicialmente es estrictamente creciente
hasta una determinada posicion, y a partir de alli es estrictamente decreciente (suponer que el arreglo tiene al menos 3 elementos)
Por ejemplo: [1 2 3 1 0 -2] tiene pico en la posicion 2.
a) Implementar en C un algoritmo de Division y Conquista, de orden O(logn) siendo n el tamaño del arreglo que
permita encontrar la posicion del arreglo en la que se encuentra dicho pico: size_t posicion_pico(int* arreglo, size_t inicio, size_t fin)
b) Utilizando el Teorema Maestro, justificar el orden del algoritmo.
*/


size_t posicion_pico(int* arr, size_t inicio, size_t fin){
    size_t medio = (inicio+fin) /2; //me aseguro tener a la derecha e izquierda
    if (arr[medio] > arr[medio+1]  &&  arr[medio-1] < arr[medio]){
        //printf("arr medio: %i, arr medio+1= %in medio:%i \n", arr[medio], arr[medio+1],medio);
        return medio;
    }

    if( arr[medio] < arr[medio+1]){
        return  posicion_pico(arr,medio,fin);
    }else{
        return posicion_pico(arr,inicio,medio);
    }
}
//T(n) = a.t(n/b) + O(n^c)
//a = 1 b = 2 c = 0
// logb(a) = log2(1) = 0 = c => O(n^c * logb(n)) = O(log2(n))

int main(void){

    //Son iguales
    int arr0[1] = {1};
    int arr1[9]={2,2,2,2,2,2,2,2,4};
    int arr2[11]={1,1,1,1,1,1,1,1,1,1,1};
    bool a = son_iguales(arr1,9);
    bool b = son_iguales(arr2,11);
    bool limite = son_iguales(arr0,1);

    printf("arr0 Resultado son iguales: %s - Tiene que ser true\n", limite ? "true" : "false");
    printf("arr1 Resultado son iguales: %s - Tiene que ser false\n", a ? "true" : "false");
    printf("arr2 Resultado son iguales: %s - Tiene que ser true\n\n", b ? "true" : "false");




    int arr4[11]={1,1,1,1,1,1,1,1,1,1,1};
    int arr5[2]={1,2};
    int arr6[12]={1,1,1,1,1,2,1,1,1,1,1,4};
    int arr7[12]={1,1,1,3,1,1,6,1,1,9,1,1};
    int arr8[3]={1,2,1};
    int arr9[3]={3,2,2};

    int c = maximo(arr4,0,10);
    printf("maximo arr4 es 1, obtengo = %i \n",c);

    int d= maximo(arr5,0,1);
    printf("maximo arr5 es 2, obtengo = %i \n",d);

    int e= maximo(arr6,0,11);
    printf("maximo arr6 es 4, obtengo = %i \n",e);

    int f = maximo(arr7,0,11);
    printf("maximo arr7 es 9, obtengo = %i \n",f);

    int g = maximo(arr8,0,2);
    printf("maximo arr8 es 2, obtengo = %i \n",g);

    int h = maximo(arr9,0,2);
    printf("maximo arr9 es 3, obtengo = %i \n\n",h);


    int array1[11]={1,2,3,4,5,6,5,4,3,2,1};
    int array2[12]={2,3,4,5,6,7,8,7,6,5,4,3};
    int array3[12]={2,3,4,5,6,7,8,9,6,5,4,3};
    int array4[3]={0,1,0};

    int resa = (int)posicion_pico(array1,0,8);
    printf("pico array 1 tiene que ser posicion 5, obtengo = %i \n",resa);
    int resb = (int) posicion_pico(array2,0,11);
    printf("pico array 2 tiene que ser posicion 6, obtengo = %i \n",resb);
    int resc = (int)posicion_pico(array3,0,11);
    printf("pico array 3 tiene que ser posicion 7, obtengo = %i \n",resc);
    int resd = (int)posicion_pico(array4,0,3);
    printf("pico array 4 tiene que ser 1, obtengo = %i \n",resd);

    return 0;
}
