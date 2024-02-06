#include "header.h"

void send_operation(char *buffer, int client_socket)
{
    char buffer_sent[BUFFER_SIZE] = "";
    int op_code = -1;

    char *p = strtok(buffer, " \n");

    if (strcmp(p, "LIST") == 0)
    {
        op_code = 0;
        snprintf(buffer_sent, BUFFER_SIZE, "%d", op_code);

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(LIST)\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(p, "DOWNLOAD") == 0)
    {
        op_code = 1;
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", op_code);

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " \n");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(DOWNLOAD)\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(p, "UPLOAD") == 0)
    {
        op_code = 2;
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", op_code);

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " \n");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        int file_d = open(p, O_RDONLY);
        if (file_d == -1)
        {
            perror("Open failed!(UPLOAD)\n");
            exit(EXIT_FAILURE);
        }

        struct stat file_stat;
        if (fstat(file_d, &file_stat))
        {
            perror("Bad call!(UPLOAD)");
            exit(EXIT_FAILURE);
        }
        off_t file_size = file_stat.st_size;

        char buff_file_size[10];
        snprintf(buff_file_size, 10, "%jd", (__intmax_t)file_size);

        strcat(buffer_sent, buff_file_size);
        strcat(buffer_sent, "|");

        char *buff_file_content = (char *)malloc(sizeof(char) * file_size);
        int bytesRead = read(file_d, buff_file_content, file_size);
        if (bytesRead < 0)
        {
            perror("Read fail!(UPLOAD)\n");
            exit(EXIT_FAILURE);
        }

        strcat(buffer_sent, buff_file_content);
        strcat(buffer_sent, "|");

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(UPLOAD)\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(p, "DELETE") == 0)
    {
        op_code = 4;
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", op_code);

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " \n");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(DELETE)\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(p, "MOVE") == 0)
    {
        op_code = 8;
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", op_code);

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " \n");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(MOVE)\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(p, "UPDATE") == 0)
    {
        op_code = 10;
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", op_code);

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " \n");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(UPDATE)\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (strcmp(p, "SEARCH") == 0)
    {
        op_code = 20;
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", op_code);

        p = strtok(NULL, " ");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        p = strtok(NULL, " \n");
        strcat(buffer_sent, p);
        strcat(buffer_sent, "|");

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(SEARCH)\n");
            exit(EXIT_FAILURE);
        }
    }

    else
    {
        snprintf(buffer_sent, BUFFER_SIZE, "%d|", 76);

        int bytesSent = send(client_socket, buffer_sent, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(UNKNOWN)\n");
            exit(EXIT_FAILURE);
        }
    }
}

void receive_response(char *buffer)
{
    char *p = strtok(buffer, "|");

    if (strcmp(p, "0") == 0)
    {
        printf("Operatie LIST, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "0") == 0)
            printf("SUCCESS, s-a primit lista de fisiere cu dim. ");

        p = strtok(NULL, "|");
        printf("%s:\n", p);

        p = strtok(NULL, "|");
        char *pp = strtok(p, "\\0");
        while (pp != NULL)
        {
            printf("%s\n", pp);
            pp = strtok(NULL, "\\0");
        }
    }

    if (strcmp(p, "1") == 0)
    {
        printf("Operatie DOWNLOAD, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "1") == 0)
            printf("FILE_NOT_FOUND!");

        else
        {
            printf("SUCCESS, s-a primit continutul: ");
            p = strtok(NULL, "|");
            p = strtok(NULL, "|");
            printf("%s\n", p);

            int file_d = open("just_downloaded.txt", O_WRONLY | O_CREAT, 0666);
            int bytesWrite = write(file_d, p, strlen(p));
            if (bytesWrite < 0)
            {
                perror("Write fail!(DOWNLOAD)\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (strcmp(p, "2") == 0)
    {
        printf("Operatie UPLOAD, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "2") == 0)
            printf("PERMISSION DENIED! File already existing!");

        else
        {
            printf("SUCCESS, file uploaded! ");
        }
    }

    if (strcmp(p, "4") == 0)
    {
        printf("Operatie DELETE, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "1") == 0)
            printf("FILE NOT FOUND!");

        else
        {
            printf("SUCCESS, file deleted! ");
        }
    }

    if (strcmp(p, "8") == 0)
    {
        printf("Operatie MOVE, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "1") == 0)
            printf("FILE NOT FOUND!");

        else if (strcmp(p, "0") == 0)
        {
            printf("SUCCESS, file moved! ");
        }

        else if (strcmp(p, "2") == 0)
        {
            printf("PERMISSION DENIED!");
        }
    }

    if (strcmp(p, "10") == 0)
    {
        printf("Operatie UPDATE, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "1") == 0)
            printf("FILE NOT FOUND!");

        else if (strcmp(p, "0") == 0)
        {
            printf("SUCCESS, file updated! ");
        }
    }

    if (strcmp(p, "20") == 0)
    {
        printf("Operatie SEARCH, ");

        p = strtok(NULL, "|");
        if (strcmp(p, "0") == 0)
            printf("SUCCESS, s-a primit lista de fisiere:\n");

        p = strtok(NULL, "|");
        if (strlen(p) == 3)
        {
            printf("Lista goala!\n");
        }
        else
        {
            char *pp = strtok(p, "\\0");
            while (pp != NULL)
            {
                printf("%s\n", pp);
                pp = strtok(NULL, "\\0");
            }
        }
    }

    if (strcmp(p, "100") == 0)
    {
        printf("UNKNOWN OPERATION!\n");
    }

    if (strcmp(p, "111") == 0)
    {
        printf("MAX NUMBER OF CLIENTS REACHED!\n");
    }
}
