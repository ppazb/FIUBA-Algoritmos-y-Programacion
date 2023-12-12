from TDA_grafo import *
import random
from biblioteca import *
D = 0.85
MAX_ITER = 15
CANT_PR_PERSONALIZADO = 10

def mas_importantes(grafo, cantidad, canciones, pagerank):
	"""Recibe un grafo bipartito con las cancion y usuarios, la cantidad de recomendacones deseadas, todas la canciones y un pagerank de
	las mismas y printea las canciones mas importantes"""
	resultado = []
	contador = 0
	actual = 0

	while contador < cantidad:
		if (pagerank[actual][0] in canciones):
			resultado.append(pagerank[actual][0])
			contador += 1
		actual += 1
	print(*resultado, sep="; ", end="\n")

def recomendaciones(grafo, elementos, n, canciones_iniciales):
	"""Recibe un grafo bipartito de usuarios y canciones, el grupo de elementos que se desea recomendar, la cantidad de recomendaciones
	y las canciones a partir de las cuales se realiza la recomendacion y printea las n recomendaciones"""
	pagerank_p = pagerank_personalizado(grafo, canciones_iniciales, n)
	resultado = []
	contador = 0
	actual = 0

	while contador < n:
		if (pagerank_p[actual][0] in elementos) and pagerank_p[actual][0] not in canciones_iniciales:
			resultado.append(pagerank_p[actual][0])
			contador += 1
		actual += 1

	print(*resultado, sep="; ", end="\n")

def _pagerank(grafo, dic_pagerank, dic_nuevo, vertice, cant_total_v, grado_v, adyacentes):
	suma = 0
	for ady in adyacentes[vertice]:
		suma += dic_pagerank[ady] / grado_v[ady]
	dic_nuevo[vertice] = (1 - D) / cant_total_v + D * suma


def generar_pagerank(grafo):
	"""Recibe el grafo con canciones y usuarios y genera su pagerank"""
	dic_pagerank = {}
	dic_nuevo = {}
	cant_v = len(grafo)
	lista_vertices = grafo.obtener_vertices()
	grados_v = dic_grados(grafo, lista_vertices)
	adyacentes = dic_adyacentes(grafo, lista_vertices)

	for v in lista_vertices:
		dic_pagerank[v] = (1) / cant_v  # inicializo

	for i in range(0, MAX_ITER):
		for vertice in lista_vertices:
			_pagerank(grafo, dic_pagerank, dic_nuevo, vertice, cant_v, grados_v, adyacentes)
		dic_pagerank = dic_nuevo

	lista_grafo = list([*dic_pagerank.items()])
	lista_grafo = sorted(lista_grafo, key=lambda x: x[1], reverse=True)
	return lista_grafo


def pagerank_personalizado(grafo, canciones_iniciales, n):
	"""Recibe un grafo de canciones y usuarios, las canciones a partir de las cuales realizar el pagerank y un numero n relacionado a 
	la cantidad de random walks deseados (Cantidad de RW = n*100)"""
	dic_pagerank = {}
	vertices = grafo.obtener_vertices()
	grados_v = dic_grados(grafo, vertices)
	adyacentes = dic_adyacentes(grafo, vertices)

	for vertice in vertices:
		dic_pagerank[vertice] = 0

	for vertice in canciones_iniciales:
		for i in range(0, CANT_PR_PERSONALIZADO):
			_pagerank_randomwalk(grafo, vertice, dic_pagerank, n, grados_v, adyacentes)

	lista_grafo = list([*dic_pagerank.items()])
	lista_grafo = sorted(lista_grafo, key=lambda x: x[1], reverse=True)
	return lista_grafo


def _pagerank_randomwalk(grafo, vertice_i, dic_pagerank, n, grados_v, adyacentes):
	padre = vertice_i
	transfiere_padre = 1 / grados_v[vertice_i]

	for x in range(0, n * 100):
		adyacente_random = random.choice(adyacentes[padre])
		dic_pagerank[adyacente_random] += transfiere_padre
		padre = adyacente_random
		transfiere_padre /= grados_v[adyacente_random]