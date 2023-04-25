import socket
import random
import threading

HOST = ''  # Escucha todas las interfaces
PORT = 65432  # Puerto para la conexión
NUM_PLAYERS = 5  # Número de jugadores

# Colores para Simon Says
colors = ["red", "green", "blue", "yellow"]

# Definir los colores en formato RGB
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

# Mapa de colores para Pygame
color_map = {
    "red": RED,
    "green": GREEN,
    "blue": BLUE,
    "yellow": YELLOW
}

# Función para ejecutar el juego con un cliente en particular
def run_game(conn, addr):
    print("Conectado por", addr)
    # Loop principal del juego
    while True:
        # Seleccionar un color aleatorio
        color = random.choice(colors)
        # Enviar el color al cliente
        conn.sendall(color.encode())

        # Esperar la respuesta del cliente
        data = conn.recv(1024).decode()
        # Verificar si el cliente siguió la instrucción de Simon Says
        if data == color:
            print(f"El jugador {addr} ha seguido la instrucción correctamente")
        else:
            print(f"El jugador {addr} no ha seguido la instrucción correctamente")
            break

# Crear el socket y comenzar a escuchar
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print("Esperando jugadores...")
    # Loop principal del servidor
    while True:
        # Esperar la conexión de un nuevo cliente
        conn, addr = s.accept()
        print("Se ha conectado un nuevo cliente:", addr)
        # Crear un nuevo hilo para manejar el cliente
        client_thread = threading.Thread(target=run_game, args=(conn, addr))
        client_thread.start()

