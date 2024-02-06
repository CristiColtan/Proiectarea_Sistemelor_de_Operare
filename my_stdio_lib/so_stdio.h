#ifndef SO_STDIO_H
#define SO_STDIO_H

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <sys/signal.h>

#include <stdlib.h>

#define MAX_SIZE (4096)
/*Dimensiunea implicită a bufferului unui fișier este de 4096 bytes.*/

#define SEEK_SET (0) /* Seek from beginning of file.  */
#define SEEK_CUR (1) /* Seek from current position.  */
#define SEEK_END (2) /* Seek from end of file.  */

#define SO_EOF (-1)

#define READ_END (0)
#define WRITE_END (1)

struct _so_file;

typedef struct _so_file
{
    int _fd;                // file descriptor
    int _open_type;         // 1-r, 2-r+, 3-w, 4-w+, 5-a, 6-a+, 0-altceva
    int _error;             // 0-nu avem eroare, 1-avem eroare
    char _buffer[MAX_SIZE]; // buffering
    int _buffer_pos;        // pozitia in buffer
    int _file_pos;          // pozitia in fisier
    int _eof;               // 0-nu end of file, 1-end of file
    int _lastOperation;     // 0-read, 1-write, 2-altceva
    pid_t _child_pid;       // pid copil

} SO_FILE;

SO_FILE *so_fopen(const char *pathname, const char *mode);

int so_fclose(SO_FILE *stream); 

int so_fileno(SO_FILE *stream); 

int so_fflush(SO_FILE *stream); 

int so_fseek(SO_FILE *stream, long offset, int whence); 
long so_ftell(SO_FILE *stream);                        

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream);       
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

int so_fgetc(SO_FILE *stream);        
int so_fputc(int c, SO_FILE *stream); 

int so_feof(SO_FILE *stream);   
int so_ferror(SO_FILE *stream); 

SO_FILE *so_popen(const char *command, const char *type);
int so_pclose(SO_FILE *stream);

#endif /* SO_STDIO_H */
