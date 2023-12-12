from biblioteca import recorrido_bfs
from collections import deque
from mensajes import*
import sys
PLAYLISTS = "playlists"
CANCIONES = "canciones"


def camino_mas_corto(grafo_usuarios_canciones, desde_cancion, hasta_cancion, canciones):
    """Recibe un grafo de canciones_usuarios, una cancion inicial, y una destino, junto al diccionario de canciones
    y devuelve por salida estandar el camino mas corto a la cancion destino(de existir) en caso contrario devuelve no se encontro recorrido"""
    padres, orden = recorrido_bfs(grafo_usuarios_canciones, desde_cancion, hasta_cancion, esta_en_playlist)
    if hasta_cancion not in padres or desde_cancion == hasta_cancion:
        print(NO_SE_ENCONTRO_RECO)
        return
    inicio = desde_cancion
    actual = hasta_cancion
    l = deque()
    while actual != inicio:
        l.appendleft(actual)
        actual = padres[actual]
    l.appendleft(actual)
    usuario = l[1]
    cadena = f"{l[0]} --> aparece en playlist --> {playlist_a_la_que_pertenece(canciones, l[0], usuario)} --> de --> {usuario}"
    for elemento in range(2, len(l)):
        if l[elemento] in canciones:
            cadena += f" --> tiene una playlist --> {playlist_a_la_que_pertenece(canciones,l[elemento], usuario)} --> donde aparece --> {l[elemento]}"
        else:
            usuario = l[elemento]
            cadena += f" --> aparece en playlist --> {playlist_a_la_que_pertenece(canciones, l[elemento-1], usuario)} --> de --> {usuario}"
    sys.stdout.write(f"{cadena}\n")


def esta_en_playlist(grafo, cancion1, cancion2):
    """Devuelve true si la cancion esta en la playlist, false en caso contrario"""
    return grafo.estan_unidos(cancion1, cancion2)


def playlist_a_la_que_pertenece(canciones, cancion, usuario):
    """Recive el diccionario de canciones, una cancion y un usario y devuelve el nombre de la playlist a la que pertenece la cancion"""
    for cancion in canciones[cancion][CANCIONES]:
        if cancion.ver_nombre_user() == usuario:
            return cancion.ver_nombre_playlist()
    return False

