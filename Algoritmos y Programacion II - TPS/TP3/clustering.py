from biblioteca import coeficiente_clustering_vertice,coeficiente_clustering_red
VACIA = ""
import sys
def clustering(grafo, cancion=None):
	"""Recibe un grafo, y opcionalmente una cancion, si se recibe una cancion, devuelve por salida estandar el coeficiente de clustering
	de la cancion en el grafo, en caso contrario devuelve el coeficiente de clustering de la red"""
	if cancion == VACIA:sys.stdout.write(f"{coeficiente_clustering_red(grafo)}\n")
	else: sys.stdout.write(f"{coeficiente_clustering_vertice(grafo, cancion)}\n")

