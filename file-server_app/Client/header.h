#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <pthread.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/dir.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_operation(char *buffer, int client_socket);
void receive_response(char *buffer);

#endif