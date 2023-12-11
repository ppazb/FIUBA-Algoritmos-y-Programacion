import collections
from TDA_grafo import Grafo
def recorrido_bfs(grafo, vertice, vertice_buscado=None, funcion_extra=None):
	"""Recive un grafo, un vertice y opcionalmente un vertice buscado, con una funcion de corte y realiza un recorrido BFS en el grafo
	y devuelve un diccionario de padres y uno de ordenes, de los vertices en relacion al vertice pasado. En caso de encontrar el vertice
	buscado, corta la iteracion"""
	padres,orden = {},{}
	visitados = set()
	padres[vertice] = None
	visitados.add(vertice)
	orden[vertice] = 0
	cola = collections.deque()
	cola.append(vertice)
	while cola:
		vertice_actual = cola.popleft()
		for vertice_adyacente in grafo.adyacentes(vertice_actual):
			if vertice_adyacente not in visitados:
				padres[vertice_adyacente] = vertice_actual
				visitados.add(vertice_adyacente)
				orden[vertice_adyacente] = orden[vertice_actual] + 1
				cola.append(vertice_adyacente)
			if funcion_extra and funcion_extra(grafo, vertice_adyacente, vertice_buscado):
				orden[vertice_buscado] = orden[vertice_actual] + 1
				padres[vertice_buscado] = vertice_adyacente
				return padres, orden
	return padres, orden


def coeficiente_clustering_vertice(grafo, vertice):
	"""Recibe un grafo, y un vertice y devuelve el coeficiente de clustering de dicho vertice"""
	grado = 0
	adyacentes =grafo.adyacentes(vertice)
	largo = len(adyacentes)
	if largo < 2: return round(grado,3)
	for adyacente in adyacentes:
		for w in adyacentes:
			if grafo.estan_unidos(adyacente, w): grado += 1
	grado = grado / (largo * (largo - 1) )
	return round(grado, 3)

def coeficiente_clustering_red(grafo):
	"""Recive un grafo y devuelve el coeficiente de clustering de la red"""
	coeficiente = 0
	cantidad_vertices = len(grafo.obtener_vertices())
	for vertice in grafo.obtener_vertices():
		coeficiente += coeficiente_clustering_vertice(grafo, vertice)
	coeficiente *= (1 / cantidad_vertices)
	return round(coeficiente,3)

def vertice_n_rango(grafo, vertice, rango):
	"""Recibe un grafo, un vertice y un rango N y devuelve la cantidad de vertices a esa N distancia"""
	resultado = 0
	orden = recorrido_bfs(grafo, vertice)[1]
	for clave in orden.keys():
		if orden[clave] == rango: resultado += 1
	return resultado

def encontrar_ciclo_n(grafo, vertice, largo):
	"""Recive un grafo, un vertice y un largo N y devuelve una lista del ciclo pedido, en caso de no encontrar devuelve lista vacia"""
	return _encontrar_ciclo_n(grafo, vertice, largo, 0, vertice, collections.deque(), set()) #utilizo deque, para tener en 0(1) el insert primero

def _encontrar_ciclo_n(grafo, vertice, largo, contador, inicio, ciclo_listado, visitados):
	visitados.add(vertice)
	if vertice == inicio and largo == contador:
		return True
	if vertice == inicio and contador != 0: return False
	if contador >= largo:
		visitados.discard(vertice)
		return False
	for adyacente in grafo.adyacentes(vertice):
		if adyacente not in visitados or adyacente == inicio:
			if _encontrar_ciclo_n(grafo, adyacente, largo, contador + 1, inicio, ciclo_listado, visitados):
				ciclo_listado.appendleft(adyacente)
				return ciclo_listado
	return ciclo_listado


def dic_grados(grafo, vertices):
	"""Recibe un grafo y los vertices deseados pertenecientes al mismo y devuelve un diccionario donde las claves son los vertices
	y el valor su grado. Solo para grafo no dirigido"""
	dic = {}
	for v in vertices:
		dic[v] = len(grafo.adyacentes(v))
	return dic


def dic_adyacentes(grafo, vertices):
	"""Recibe un grafo y los vertices deseados pertenecientes al mismo y devuelve un diccionario donde las claves son los vertices
	y el valor los vertices adyacentes al mismo. Solo para grafo no dirigido"""
	dic = {}
	for v in vertices:
		dic[v] = grafo.adyacentes(v)
	return dic
