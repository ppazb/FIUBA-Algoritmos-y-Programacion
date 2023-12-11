#!/usr/bin/python3
import sys, time
from clases import *

PLAYLISTS = "playlists"
CANCIONES = "canciones"
from TDA_grafo import Grafo
from mensajes import *
from clases import *
from pagerank import *
from camino import *
from clustering import *
from ciclo import *
from rango import *
import csv

IMPORTANTES = "mas_importantes"
CLUSTERING = "clustering"

CAMINO = "camino"  
RECOMENDACION_C = "recomendacion canciones"
RECOMENDACION_U = "recomendacion usuarios"
CICLO = "ciclo"
RANGO = "rango"

SEPARADORES = {CAMINO: " >>>> ", RECOMENDACION_C: " >>>> ", RECOMENDACION_U: " >>>> ", CICLO: " - ", CLUSTERING: " "}

CADENA_VACIA = ""


def generar_usuarios_canciones(ruta):
	with open(ruta, "r") as file:
		file.readline()
		spotify = csv.reader(file, delimiter='\t', quoting=csv.QUOTE_NONE)
		canciones = {}
		grafo_canciones_usuarios = Grafo()
		usuarios = set()
		for linea in spotify:
			user_id, nombre_cancion, compositor, id_playlist, nombre_playlist, generos = linea[1], linea[2], linea[3], \
																						 linea[4], linea[5], linea[6]
			nombre = f"{nombre_cancion} - {compositor}"
			cancion = Cancion(nombre, compositor, user_id, generos, nombre_playlist)
			if not grafo_canciones_usuarios.pertenece_vertice(user_id):
				grafo_canciones_usuarios.agregar_vertice(user_id)
				usuarios.add(user_id)
			if not grafo_canciones_usuarios.pertenece_vertice(nombre):
				grafo_canciones_usuarios.agregar_vertice(nombre)
				canciones[nombre] = {}
				canciones[nombre][PLAYLISTS] = []
				canciones[nombre][PLAYLISTS].append(nombre_playlist)
				canciones[nombre][CANCIONES] = []
				canciones[nombre][CANCIONES].append(cancion)
			else:
				canciones[nombre][CANCIONES].append(cancion)
				canciones[nombre][PLAYLISTS].append(nombre_playlist)
			grafo_canciones_usuarios.agregar_arista(user_id, nombre)
	return canciones, usuarios, grafo_canciones_usuarios


def generar_canciones_en_playlist(ruta):
	with open(ruta, "r") as file:
		file.readline()
		spotify = csv.reader(file, delimiter='\t', quoting=csv.QUOTE_NONE)
		playlists = {}
		canciones = {}
		grafo_canciones_en_lista = Grafo()
		for linea in spotify:
			user_id, nombre_cancion, compositor, id_playlist, nombre_playlist, generos = linea[1], linea[2], linea[3], \
																						 linea[4], linea[5], linea[6]
			nombre = f"{nombre_cancion} - {compositor}"
			cancion = Cancion(nombre, compositor, user_id, generos, nombre_playlist)
			if nombre not in canciones:
				grafo_canciones_en_lista.agregar_vertice(nombre)
				canciones[nombre] = {}
				canciones[nombre][PLAYLISTS] = []
				canciones[nombre][PLAYLISTS].append(nombre_playlist)
				canciones[nombre][CANCIONES] = []
				canciones[nombre][CANCIONES].append(cancion)
			else:
				canciones[nombre][CANCIONES].append(cancion)
				canciones[nombre][PLAYLISTS].append(nombre_playlist)
			if nombre_playlist not in playlists:
				playlists[nombre_playlist] = []
				playlists[nombre_playlist].append(nombre)
			else:
				playlists[nombre_playlist].append(nombre)
			for c in playlists[cancion.ver_nombre_playlist()]:
				if cancion.ver_nombre_playlist() in canciones[c][PLAYLISTS] and c != nombre:
					grafo_canciones_en_lista.agregar_arista(nombre, c)
	return canciones, grafo_canciones_en_lista


def es_igual(cadena, comando):
	largo_com = len(comando)
	largo_cad = len(cadena)
	return (largo_cad >= largo_com) and (cadena[0:len(comando)] == comando)


def es_comando(recibido):
	if es_igual(recibido, CAMINO):
		return CAMINO
	elif es_igual(recibido, IMPORTANTES):
		return IMPORTANTES
	elif es_igual(recibido, RECOMENDACION_C):
		return RECOMENDACION_C
	elif es_igual(recibido, RECOMENDACION_U):
		return RECOMENDACION_U
	elif es_igual(recibido, CICLO):
		return CICLO
	elif es_igual(recibido, RANGO):
		return RANGO
	elif es_igual(recibido, CLUSTERING):
		return CLUSTERING
	return None


def procesar_comando(parametros, comando, pagerank, grafo_canciones_usuarios, grafo_canciones_en_lista, canciones,
					 usuarios):
	if comando == CLUSTERING:
		clustering(grafo_canciones_en_lista, parametros)

	elif comando == CAMINO:
		parametro_canciones = parametros.split(SEPARADORES[comando])
		if (len(parametro_canciones) != 2) or not (
				parametro_canciones[0] in canciones and parametro_canciones[1] in canciones):
			print(ERROR_ENT_CAMINO)
		else:
			camino_mas_corto(grafo_canciones_usuarios, parametro_canciones[0], parametro_canciones[1], canciones)

	else:
		parametros = parametros.split(" ", 1)
		n = parametros[0]

		if comando == IMPORTANTES:
			mas_importantes(grafo_canciones_usuarios, int(n), canciones, pagerank)

		else:
			cancion = parametros[1]

			if comando == RANGO:
				todas_en_rango(grafo_canciones_en_lista, cancion, int(n))
			elif comando == CICLO:
				if cancion not in canciones: print(NO_SE_ENCONTRO_RECO)
				else:ciclo_de_n_canciones(grafo_canciones_en_lista, cancion, int(n))
			else:
				canciones_iniciales = cancion.split(SEPARADORES[comando])
				if comando == RECOMENDACION_C:
					recomendaciones(grafo_canciones_usuarios, canciones, int(n), canciones_iniciales)
				else:
					recomendaciones(grafo_canciones_usuarios, usuarios, int(n), canciones_iniciales)


def main():
	pagerank = None
	grafo_canciones_usuarios = None
	grafo_canciones_en_lista = None
	canciones = None
	usuarios = None

	for recibido in sys.stdin:
		recibido = recibido.rstrip("\n")
		if recibido == CADENA_VACIA:
			break

		comando = es_comando(recibido)
		if not comando:
			print(COMANDO_INVALIDO)
			continue

		if (comando == CLUSTERING or comando == RANGO or comando == CICLO) and not grafo_canciones_en_lista:
			canciones, grafo_canciones_en_lista = generar_canciones_en_playlist(sys.argv[-1])
		else:
			if not grafo_canciones_usuarios:
				canciones, usuarios, grafo_canciones_usuarios = generar_usuarios_canciones(sys.argv[-1])

		if comando == IMPORTANTES and not pagerank:
			pagerank = generar_pagerank(grafo_canciones_usuarios)
		procesar_comando(recibido[len(comando) + 1:], comando, pagerank, grafo_canciones_usuarios,
						 grafo_canciones_en_lista, canciones, usuarios)
	return


main()
