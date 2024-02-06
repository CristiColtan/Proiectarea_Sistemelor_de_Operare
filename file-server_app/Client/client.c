#include "header.h"

int main()
{
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char buffer_primit[BUFFER_SIZE];

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket fail!\n");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection fail!\n");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server!\n");
    printf("> ");

    fgets(buffer, BUFFER_SIZE, stdin);
    send_operation(buffer, client_socket);

    int bytesRead = recv(client_socket, buffer_primit, BUFFER_SIZE, 0);
    printf("Am primit de la server: %s\n", buffer_primit);

    receive_response(buffer_primit);

    close(client_socket);
}