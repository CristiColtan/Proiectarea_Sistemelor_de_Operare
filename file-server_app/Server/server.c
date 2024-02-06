#include "header.h"
// Apare accept failed deoarece inainte de a se inchide complet, server ul mai intra o data in accept,
// dar functioneaza cum trebuie
// (incearca sa mai serveasca un client)

size_t total_clients = 0;
pthread_t tids[MAX_CLIENTS];

fileStats f[MAX_FILES];
int numar_fisiere = 0;
int need_update = 0;
int server_socket;

volatile sig_atomic_t shutdown_flag = 0;

int main(int argc, char *argv[])
{
    printf("Welcome!\n");

    struct sockaddr_in server_addr;
    int setsock_opt = 1;

    int signal_fd = setup_signal_fd();

    pthread_t specialised_thread, listener_thread;
    specThreadData data = {f, &numar_fisiere};

    pthread_create(&listener_thread, NULL, listener_thread_function, NULL);
    pthread_create(&specialised_thread, NULL, index_thread_function, &data);

    // Create socket.
    // AF_INET -> IPv4;
    // SOCK_STREAM -> TCP (garanteaza livrarea);
    // INADDR_ANY -> Orice conexiune e acceptata.

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket fail!");
        exit(EXIT_FAILURE);
    } // Daca avem valoarea 0 se alege un protocol automat.
      // Daca valoarea IF ului e -1 avem eroare.

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &setsock_opt, sizeof(setsock_opt)))
    {
        perror("Setsockopt fail!\n");
        exit(EXIT_FAILURE);
    }

    // Configure socket.
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to port 8080.
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind fail!");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_socket, 3) < 0)
    {
        perror("Listen fail!");
        exit(EXIT_FAILURE);
    } // Ascultam maxim 3 in acelasi timp.

    printf("Listening on port 8080\n");
    while (!shutdown_flag)
    { // Ascultam la infinit pentru noi clienti
        // Client info
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int *client_socket = malloc(sizeof(int));

        // Accept client connection
        if ((*client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0)
        {
            perror("Accept failed!\n");
            continue;
        }

        printf("Client connection accepted!\n");

        pthread_create(&tids[total_clients], NULL, handle_client, client_socket);
        total_clients++;
    }
    printf("Shutting down...\n");

    pthread_join(listener_thread, NULL);
    if (total_clients > 0)
    {

        for (int i = 0; i < total_clients - 1; i++)
        {
            pthread_join(tids[i], NULL);
        }
    }
    printf("Application terminated gracefully.\n");
    return 0;
}

void *listener_thread_function(void *vargp)
{
    int signal_fd = setup_signal_fd();

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        perror("Epoll_create1 fail!\n");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    memset(&ev, 0, sizeof(ev));

    ev.events = EPOLLIN;
    ev.data.fd = signal_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, signal_fd, &ev) == -1)
    {
        perror("Epoll_ctl fail! (SIGNAL_FD)\n");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1)
    {
        perror("Epoll_ctl fail! (STDIN)\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == signal_fd)
            {
                struct signalfd_siginfo fdsi;
                ssize_t s = read(signal_fd, &fdsi, sizeof(struct signalfd_siginfo));
                if (s != sizeof(struct signalfd_siginfo))
                    continue;

                if (fdsi.ssi_signo == SIGINT || fdsi.ssi_signo == SIGTERM)
                {
                    printf("Received signal, shutting down.\n");
                    shutdown_flag = 1;
                    shutdown(server_socket, SHUT_RDWR);
                    close(server_socket);
                    close(epoll_fd);
                    return NULL;
                }
            }
            else if (events[n].data.fd == STDIN_FILENO)
            {
                char buf[256];
                ssize_t count = read(STDIN_FILENO, buf, sizeof(buf));
                if (count == -1)
                {
                    perror("Read fail! (EPOLL)\n");
                    continue;
                }

                if (strncmp(buf, "quit\n", 5) == 0)
                {
                    shutdown_flag = 1;
                    printf("Received quit command, shutting down.\n");
                    shutdown(server_socket, SHUT_RDWR);
                    close(server_socket);
                    close(epoll_fd);
                    return NULL;
                }
            }
        }
    }
    return NULL;
}
