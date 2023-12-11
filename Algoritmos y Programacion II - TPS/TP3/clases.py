import csv,biblioteca
from TDA_grafo import Grafo
from collections import deque
from mensajes import *
from pagerank import *
PLAYLISTS = "playlists"
CANCIONES = "canciones"
class Cancion:
    def __init__(self, nombre_cancion, compositor, nombre_user, generos, playlist_nombre):
        """Recibe todos los datos de cancion e inicializa una cancion con dichos parametros"""
        self.nombre = nombre_cancion
        self.compositor = compositor
        self.nombre_user = nombre_user
        self.generos = generos
        self.playlist_nombre = playlist_nombre

    def __str__(self):
        """Metodo str de la cancion, devuelve su nombre"""
        return self.nombre

    def obtener_generos(self):
        """Devuelve la lista de generos de la cancion"""
        return self.generos

    def ver_compositor(self):
        """Devuelve el compositor de la cancion"""
        return self.compositor

    def ver_nombre_user(self):
        """Devuelve el nombre de usuario, que agrego esta cancion """
        return self.nombre_user

    def ver_nombre_playlist(self):
        """Devuelve el nombre de la playlist en la que aparece la cancion"""
        return self.playlist_nombre

    def ver_nombre(self):
        """Devuelve el nombre de la cancion"""
        return self.nombre
