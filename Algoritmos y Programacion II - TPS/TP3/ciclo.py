from biblioteca import encontrar_ciclo_n
from mensajes import *
import sys
import time

def ciclo_de_n_canciones(grafo, cancion, n ):
	"""Recive una grafo, una cancion y un numero entero y devuelve por salida estandar un ciclo de longitud N, en caso de no encontrar ciclo,
	devuelve por salida estandar no se encontro recorrido"""
	lista_resultado = encontrar_ciclo_n(grafo, cancion, n)
	if not lista_resultado:
		sys.stdout.write(f"{NO_SE_ENCONTRARON}\n")
	else:
		cadena = f"{cancion}"
		for resultado in lista_resultado:
			cadena += " --> "
			cadena += f"{resultado}"
		sys.stdout.write(f"{cadena}\n")