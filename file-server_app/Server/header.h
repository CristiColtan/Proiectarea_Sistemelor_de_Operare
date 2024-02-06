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
#include <signal.h>

#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/dir.h>
#include <sys/signal.h>
#include <sys/signalfd.h>
#include <sys/epoll.h>

#define PORT (8080)
#define BUFFER_SIZE (1024)
#define LOG_FILE "log.txt"
#define MAX_FILES (20)
#define MAX_CLIENTS (10)
#define MAX_EVENTS (2)

extern size_t total_clients;
extern volatile sig_atomic_t shutdown_flag;
extern int need_update;

void update_log(char *operatie, char *intre_paranteze);
void send_response(char *buffer, int client_socket, int total);
int find_word(char *word_name, char *file_name);

typedef struct
{
    char word_name[30];
    int freq;
} wordFreq;

typedef struct
{
    char file_name[30];
    int name_dim;
    int content_dim;
    int read;
    int write;
    wordFreq top[10];
    pthread_mutex_t f_mutex;
    pthread_cond_t f_cond;
} fileStats;

void index_file(int i, fileStats *fisiere);
void find_files(int *numar_fisiere, fileStats *fisiere);
void *index_thread_function(void *vargp);
void trigger_reindexing();

// pthread_mutex_t log_file_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    fileStats *fisiere;
    int *numarFisiere;
} specThreadData;

void *handle_client(void *vargp);
void *listener_thread_function(void *vargp);
int setup_signal_fd();

extern fileStats f[MAX_FILES];
extern int numar_fisiere;
#endif