from biblioteca import vertice_n_rango
import sys
def todas_en_rango(grafo_canciones_en_playlist, cancion, rango):
	""" Recibe un grafo de canciones en playlist, una cancion, y un rango entero y devuelve por 
	salida estandar todas las canciones a ese N rango"""
	sys.stdout.write(f"{vertice_n_rango(grafo_canciones_en_playlist, cancion, rango)}\n")