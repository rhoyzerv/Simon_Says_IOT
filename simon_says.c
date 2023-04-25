#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 65432

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char color[10];

    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("10.55.0.1"); // Dirección IP del servidor
    servaddr.sin_port = htons(PORT);

    // Conectar al servidor
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }

    // Loop principal del juego
    while (1) {
        // Recibir el color de Simon Says
        if (recv(sockfd, color, sizeof(color), 0) == -1) {
            perror("Error al recibir datos del servidor");
            exit(EXIT_FAILURE);
        }

        // Imprimir el color recibido
        if (strncmp(color, "red", 4) == 0) {
            printf("\033[1;31mSimon Says: %s\033[0m\n", color);
        } else if (strncmp(color, "green", 5) == 0) {
            printf("\033[1;32mSimon Says: %s\033[0m\n", color);
        } else if (strncmp(color, "blue", 4) == 0) {
            printf("\033[1;34mSimon Says: %s\033[0m\n", color);
        } else if (strncmp(color, "yellow", 8) == 0) {
            printf("\033[1;33mSimon Says: %s\033[0m\n", color);
        } else {
            printf("Simon Says: %s\n", color);
        }

        // Leer la entrada del usuario
        printf("Tu turno: ");
        scanf("%s", color);

        // Enviar la respuesta al servidor
        if (send(sockfd, color, strlen(color), 0) == -1) {
            perror("Error al enviar datos al servidor");
            exit(EXIT_FAILURE);
        }
    }

    // Cerrar el socket
    close(sockfd);

    return 0;
}
