#include "so_stdio.h"

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    SO_FILE *stream = (SO_FILE *)malloc(sizeof(SO_FILE));

    for (int i = 0; i < MAX_SIZE; i++)
    {
        stream->_buffer[i] = 0;
    }
    stream->_child_pid = -1;
    stream->_error = 0;
    stream->_buffer_pos = 0;
    stream->_file_pos = 0;
    stream->_eof = 0;
    stream->_lastOperation = 2;
    stream->_open_type = 0;

    if (stream == NULL)
    {
        printf("Eroare malloc");
        stream->_error = 1;

        free(stream);
        return NULL;
    }

    if (strcmp(mode, "r") == 0)
    { /*r ​- deschide fișierul pentru citire.*/
        stream->_fd = open(pathname, O_RDONLY);
        stream->_open_type = 1;
    }

    else if (strcmp(mode, "r+") == 0)
    { /*r+ ​- deschide fișierul pentru citire și scriere.*/
        stream->_fd = open(pathname, O_RDWR);
        stream->_open_type = 2;
    }

    else if (strcmp(mode, "w") == 0)
    { /*​w ​- deschide fișierul pentru scriere.*/
        /*dacă fișierul nu există, este creat.
        dacă fișierul există, este trunchiat la dimensiune 0.*/
        stream->_fd = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        stream->_open_type = 3;
    }

    else if (strcmp(mode, "w+") == 0)
    { /*w+ ​- deschide fișierul pentru citire și scriere.*/
        /*dacă fișierul nu există, este creat.
        dacă fișierul există, este trunchiat la dimensiune 0*/
        stream->_fd = open(pathname, O_RDWR | O_TRUNC | O_CREAT, 0644);
        stream->_open_type = 4;
    }

    else if (strcmp(mode, "a") == 0)
    { /*a ​- deschide fișierul în modul ​append.*/
        /*dacă fișierul ​nu există, este creat.*/
        stream->_fd = open(pathname, O_APPEND | O_WRONLY | O_CREAT, 0644);
        stream->_open_type = 5;
    }

    else if (strcmp(mode, "a+") == 0)
    { /*a+​ - deschide fișierul ​în modul ​append+read​.*/
        /*dacă fișierul ​nu există, ​este creat.*/
        stream->_fd = open(pathname, O_APPEND | O_RDWR | O_CREAT, 0644);
        stream->_open_type = 6;
    }

    if (stream->_open_type == 0)
    {
        printf("Eroare file type");
        stream->_error = 1;

        free(stream);
        return NULL;
    }

    if (stream->_fd < 0)
    {
        printf("Eroare open");
        stream->_error = 1;

        free(stream);
        return NULL;
    }

    return stream;
}

int so_fclose(SO_FILE *stream)
{
    if (stream->_lastOperation == 1)
    {
        int flush = so_fflush(stream);
        if (flush < 0)
        {
            printf("Eroare fflush fclose!");
            stream->_error = 1;

            free(stream);
            stream = NULL;

            return SO_EOF;
        }
    }

    int ret = close(stream->_fd);
    if (ret < 0)
    {
        free(stream);
        stream = NULL;
    }

    if (stream == NULL)
    {
        return SO_EOF;
    }
    else
    {
        free(stream);
        stream = NULL;
    }

    return 0; // Succes
}

int so_fileno(SO_FILE *stream)
{
    return stream->_fd;
}

int so_fflush(SO_FILE *stream)
{ /*Are sens doar pentru fișierele pentru care ultima operație a fost una de scriere.*/
    int bytes_write = write(stream->_fd, stream->_buffer, stream->_buffer_pos);
    if (bytes_write < 0)
    {
        printf("Eroare fflush");
        stream->_error = 1;

        return SO_EOF;
    }

    stream->_buffer_pos = 0;
    return 0; // Succes
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
    /*Dacă ultima operație făcută pe fișier a fost una de scriere,
    conținutul bufferului trebuie scris în fișier.*/

    if (stream->_lastOperation == 1)
    {
        int flush = so_fflush(stream);
        if (flush < 0)
        {
            printf("Eroare flush fseek!");

            return SO_EOF;
        }
    }

    int ret = lseek(stream->_fd, offset, whence);
    if (ret == -1)
    {
        printf("Eroare fseek");
        stream->_error = 1;

        return SO_EOF;
    }

    stream->_file_pos = ret;
    return 0; // Succes
}

long so_ftell(SO_FILE *stream)
{
    return stream->_file_pos;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
// EX: fread(buffer, strlen(c)+1, 1, stream)
{
    /*Pentru fișierele deschise în modul „​a+“,​ scrierile se fac la fel ca mai sus.
    În schimb, citirea se face inițial de la începutul fișierului.*/
    if (stream->_open_type == 6)
    {
        int seekk = so_fseek(stream, 0, SEEK_SET);
        if (seekk < 0)
        {
            printf("Eroare fseek fread");

            return SO_EOF;
        }
    }

    size_t elements_read = 0;
    size_t total_bytes = size * nmemb;
    char *aux = (char *)malloc(total_bytes);

    for (int i = 0; i < nmemb; i++)
    {
        int character = so_fgetc(stream);
        stream->_file_pos++;
        
        if (stream->_error == 1)
        {
            free(aux);
            return 0;
        }
        if (stream->_eof == 1)
        {
            break;
        }

        aux[i] = (char)character;
        elements_read++;
    }

    stream->_lastOperation = 0;
    memcpy(ptr, aux, elements_read);
    free(aux);

    return elements_read;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
// EX: fwrite(c, strlen(c) + 1, 1, stream);
{
    size_t elements_write = 0;
    size_t total_bytes = size * nmemb;
    char *aux = (char *)ptr;

    /*Operațiile de scriere pe un fișier deschis în modul „​a“​ se fac ca și cum
     fiecare operație ar fi precedată de un seek la sfârșitul fișierului.*/

    /*Pentru fișierele deschise în modul „​a+“,​ scrierile se fac la fel ca mai sus.
    În schimb, citirea se face inițial de la începutul fișierului.*/

    if (stream->_open_type == 5 || stream->_open_type == 6)
    {
        int ret = so_fseek(stream, 0, SEEK_END);
        if (ret < 0)
            return SO_EOF;
    }

    for (int i = 0; i < nmemb; i++)
    {
        int character = so_fputc((int)aux[i], stream);
        stream->_file_pos++;

        if (stream->_error == 1)
            return SO_EOF;

        elements_write++;
    }

    if (elements_write != nmemb || elements_write == 0)
    {
        stream->_error = 1;

        return SO_EOF;
    }

    stream->_lastOperation = 1;

    return elements_write;
}

int so_fgetc(SO_FILE *stream)
{
    if (stream->_buffer_pos == 0 || stream->_buffer_pos >= MAX_SIZE)
    // citim din fisier daca buffer ul e gol sau daca este plin
    {
        int bytes_read = read(stream->_fd, stream->_buffer, MAX_SIZE);
        if (bytes_read < 0)
        {
            printf("Eroare fgetc");
            stream->_error = 1;

            return SO_EOF;
        }

        if (bytes_read == 0)
        {
            printf("End of file");
            stream->_eof = 1;

            return SO_EOF;
        }

        stream->_buffer_pos = 0;
    }

    /*If the failure has been caused by end-of-file condition,
    additionally sets the eof indicator (see feof()) on stream.*/
    if (stream->_buffer[stream->_buffer_pos] == '\0')
    {
        stream->_eof = 1;
        return SO_EOF;
    }

    stream->_lastOperation = 0;
    stream->_buffer_pos++;

    return (unsigned char)stream->_buffer[stream->_buffer_pos - 1];
}

int so_fputc(int c, SO_FILE *stream)
{
    if (stream->_buffer_pos >= MAX_SIZE)
    { // daca buffer ul e plin dam fflush
        int ret = so_fflush(stream);
        if (ret == -1)
        {
            printf("Eroare flush!");
            stream->_error = 1;

            return SO_EOF;
        }
    }

    stream->_buffer[stream->_buffer_pos] = (char)c;
    stream->_buffer_pos++;
    stream->_lastOperation = 1;
    return c;
}

int so_feof(SO_FILE *stream)
{
    if (stream->_buffer[stream->_buffer_pos] == '\0')
        return 1;

    return stream->_eof;
}

int so_ferror(SO_FILE *stream)
{
    return stream->_error;
}

SO_FILE *so_popen(const char *command, const char *type)
{
    SO_FILE *stream = (SO_FILE *)malloc(sizeof(SO_FILE));

    for (int i = 0; i < MAX_SIZE; i++)
    {
        stream->_buffer[i] = 0;
    }

    stream->_error = 0;
    stream->_buffer_pos = 0;
    stream->_file_pos = 0;
    stream->_eof = 0;
    stream->_lastOperation = 2;
    stream->_open_type = 0;

    if (stream == NULL)
    {
        printf("Eroare malloc popen");
        stream->_error = 1;

        free(stream);
        return NULL;
    }

    int pipe_fd[2];
    int ret = pipe(pipe_fd);
    if (ret < 0)
    {
        printf("Eroare pipe!");

        free(stream);
        return NULL;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Eroare fork!");
        close(pipe_fd[READ_END]);
        close(pipe_fd[WRITE_END]);

        free(stream);
        return NULL;
    }

    stream->_child_pid = pid;

    if (pid == 0)
    {
        if (strcmp(type, "r") == 0)
        {
            close(pipe_fd[READ_END]);
            dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
        }
        else if (strcmp(type, "w") == 0)
        {
            close(pipe_fd[WRITE_END]);
            dup2(pipe_fd[READ_END], STDIN_FILENO);
        }

        execlp("/bin/sh", "/bin/sh", "-c", command, NULL);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        if (strcmp(type, "r") == 0)
        {
            close(pipe_fd[WRITE_END]);
            stream->_fd = pipe_fd[READ_END];
        }
        else if (strcmp(type, "w") == 0)
        {
            close(pipe_fd[READ_END]);
            stream->_fd = pipe_fd[WRITE_END];
        }
    }

    return stream;
}

int so_pclose(SO_FILE *stream)
{
    int status;
    pid_t pid = stream->_child_pid;

    int ret = so_fclose(stream);
    if (ret < 0)
    {
        printf("Eroare fclose pclose!");

        free(stream);
        stream = NULL;
        return SO_EOF;
    }

    int wait = waitpid(pid, &status, 0);
    if (wait < 0)
    {
        printf("Eroare wait!");

        free(stream);
        stream = NULL;
        return SO_EOF;
    }

    return status;
}
