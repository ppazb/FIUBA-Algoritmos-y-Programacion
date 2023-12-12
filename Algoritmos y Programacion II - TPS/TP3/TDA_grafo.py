
import random


class Grafo:

	def __init__(self, grafo_es_dirigido = False):
		"""Inicializador de grafo, recibe si el grafo es dirigido o no. De no recibir parametro, se crea un grafo
		no dirigido"""
		self.es_dirigido = grafo_es_dirigido
		self.vertices = {}

	def __str__(self):
		"""Printea el grafo en formato vertice : adyacentes"""
		cadena = ""
		for v in self.obtener_vertices():
			ady = ",".join(map(str, self.adyacentes(v)))
			cadena += str(v) + ":" + ady + "\n"
		return cadena

	def __len__(self):
		"""Devuelve el len del grafo (La cantidad de vertices)"""
		return len(self.vertices.keys())

	def obtener_vertices(self):
		"""Devuelve una lista con los vertices del grafo"""
		return [*self.vertices.keys()]

	def pertenece_vertice(self, v):
		"""Devuelve True or False en base a si el vertice recibido pertenece al grafo"""
		return v in self.vertices

	def agregar_vertice(self, v):
		"""Recibe un vertice, lo agrega al grafo y devuelve True. De no poder hacerlo devuelve False."""
		if self.pertenece_vertice(v):
			return False

		self.vertices[v] = {}
		return True

	def borrar_vertice(self, v):
		"""Borra el vertice recibido del grafo y devuelve True. De no poder hacerlo devuelve False"""
		if not self.pertenece_vertice(v):
			return False

		del self.vertices[v]
		return True

	def estan_unidos(self, v, w):
		"""Recibe dos vertices y devuelve True si estan unidos por una arista. De lo contrario devuelve False"""
		if (w in self.vertices[v]) or (v in self.vertices[w]):
			return True
		return False

	def agregar_arista(self, v, w, peso=0):
		"""Recibe dos vertices y un peso (En caso de tenerlo), agrega una arista y devuelve True. En caso de que algun vertice no pertenezca
		al grafo devuevle False"""
		if not (self.pertenece_vertice(v) or self.pertenece_vertice(w)):
			return False

		self.vertices[v][w] = peso
		if not self.es_dirigido:
			self.vertices[w][v] = peso

		return True

	def borrar_arista(self, v, w):
		"""Recibe dos vertices, borra la arista que los une y devuelve True. De no haber arista devuelve False"""
		if w not in self.vertices[v]:  # W no esta en el dic de vert a los q v esta unido
			return False

		del self.vertices[v][w]
		if not self.es_dirigido:
			del self.vertices[w][v]

		return True

	def peso_arista(self, v, w):
		"""Devuelve el peso de la arista entre dos vertices. De no existir la arista devuelve None"""
		if w not in self.vertices[v]:
			return None
		return self.vertices[v][w]

	def modificar_peso_arista(self, v, w, peso):
		"""Recibe dos vertices, el peso nuevo de la arista y devuelve True. De no haber arista devuelve False"""
		if w not in self.vertices[v]:
			return False  # no existe la arista

		self.vertices[v][w] = peso
		if not self.es_dirigido:
			self.vertices[w][v] = peso
		return True

	def vertice_aleatorio(self):
		"""Devuelve un vertice aleatorio"""
		n = random.randint(0, len(self) - 1)
		return self.obtener_vertices()[n]

	def adyacentes(self, v):
		"""Recibe un vertice y devuelve sus adyacentes. De no pertenecer al grafo devuelve None"""
		if not self.pertenece_vertice(v):
			return None
		return [*self.vertices[v].keys()]
