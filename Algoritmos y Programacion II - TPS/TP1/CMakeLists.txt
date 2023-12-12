cmake_minimum_required(VERSION 3.21)
project(Algoritmos C)

set(CMAKE_C_STANDARD 23)

#Para correr Infix.c (Conversor desde notación infija)
add_executable(Algoritmos infix.c
        "calc_helper.c"
        "calc_helper.h"
        "pila.c"
        "pila.h"
        "strutil.c"
        "strutil.h")

#Para correr DC.c ( Calculadora en notación posfija)
#add_executable(Algoritmos dc.c
#        "calc_helper.c"
#        "calc_helper.h"
#        "pila.c"
#        "pila.h"
#        "strutil.c"
#        "strutil.h")
