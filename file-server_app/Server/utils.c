#include "header.h"

pthread_mutex_t log_file_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_index = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_index = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void update_log(char *operatie, char *intre_paranteze)
{
    time_t current_time;
    time(&current_time);
    char *time_string = ctime(&current_time);
    size_t pos = strcspn(time_string, "\n");
    time_string[pos] = '\0';

    pthread_mutex_lock(&log_file_mutex);

    int log_fd = open(LOG_FILE, O_WRONLY | O_APPEND);
    if (log_fd == -1)
    {
        perror("Eroare open!(LOG_FILE)\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(operatie, "0") == 0)
    {
        strcat(time_string, " 0x0 - LIST\n");
    }

    if (strcmp(operatie, "1") == 0)
    {
        strcat(time_string, " 0x1 - DOWNLOAD ");
        strcat(time_string, "[");
        strcat(time_string, intre_paranteze);
        strcat(time_string, "]\n");
    }

    if (strcmp(operatie, "2") == 0)
    {
        strcat(time_string, " 0x2 - UPLOAD ");
        strcat(time_string, "[");
        strcat(time_string, intre_paranteze);
        strcat(time_string, "]\n");
    }

    if (strcmp(operatie, "4") == 0)
    {

        strcat(time_string, " 0x4 - DELETE ");
        strcat(time_string, "[");
        strcat(time_string, intre_paranteze);
        strcat(time_string, "]\n");
    }

    if (strcmp(operatie, "8") == 0)
    {

        strcat(time_string, " 0x8 - MOVE ");
        strcat(time_string, "[");
        strcat(time_string, intre_paranteze);
        strcat(time_string, "]\n");
    }

    if (strcmp(operatie, "10") == 0)
    {

        strcat(time_string, " 0x10 - UPDATE ");
        strcat(time_string, "[");
        strcat(time_string, intre_paranteze);
        strcat(time_string, "]\n");
    }

    if (strcmp(operatie, "20") == 0)
    {

        strcat(time_string, " 0x20 - SEARCH ");
        strcat(time_string, "[");
        strcat(time_string, intre_paranteze);
        strcat(time_string, "]\n");
    }

    int bytesWrite = write(log_fd, time_string, strlen(time_string));
    if (bytesWrite < 0)
    {
        perror("Eroare write!(LOG_FILE)\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_unlock(&log_file_mutex);
}

void send_response(char *buffer, int client_socket, int total)
{
    if (total == 1)
    {
        char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        memset(buffer_response, 0, BUFFER_SIZE);

        snprintf(buffer_response, 5, "111|");
        int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
        if (bytesSent < 0)
        {
            perror("Sent fail!(UPDATE)\n");
            exit(EXIT_FAILURE);
        }

        free(buffer_response);
    }
    else
    {
        char *p = strtok(buffer, " |\n");

        if (strcmp(p, "0") == 0)
        {
            update_log(p, "");
            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            DIR *dir;
            struct dirent *dirent;
            dir = opendir(".");

            if (dir)
            {
                while ((dirent = readdir(dir)) != NULL)
                {
                    if (dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
                    {
                        DIR *subdir;
                        struct dirent *subdirent;
                        subdir = opendir(dirent->d_name);

                        if (subdir)
                        {
                            while ((subdirent = readdir(subdir)) != NULL)
                            {
                                if (subdirent->d_type == DT_REG)
                                {
                                    strcat(buffer_response, dirent->d_name);
                                    strcat(buffer_response, "/");
                                    strcat(buffer_response, subdirent->d_name);
                                    strcat(buffer_response, "\\0");
                                }
                            }
                        }
                        else
                        {
                            perror("Eroare open!(SUBDIR)\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else if (dirent->d_type == DT_REG)
                    {
                        strcat(buffer_response, dirent->d_name);
                        strcat(buffer_response, "\\0");
                    }
                }
                closedir(dir);
            }
            else
            {
                perror("Eroare open!(DIR)\n");
                exit(EXIT_FAILURE);
            }

            /*int log_fd = open("testing.txt", O_WRONLY | O_APPEND);
            if (log_fd == -1)
            {
                perror("Eroare open!(LOG_FILE)\n");
                exit(EXIT_FAILURE);
            }

            int bytesWrite = write(log_fd, buffer_response, strlen(buffer_response));
            if (bytesWrite < 0)
            {
                perror("Eroare write!(LOG_FILE)\n");
                exit(EXIT_FAILURE);
            }*/

            char *buffer_response_final = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response_final, 0, BUFFER_SIZE);

            snprintf(buffer_response_final, 10, "0|0|%ld|", strlen(buffer_response));
            strcat(buffer_response_final, buffer_response);
            strcat(buffer_response_final, "|");

            int bytesSent = send(client_socket, buffer_response_final, BUFFER_SIZE, 0);
            if (bytesSent < 0)
            {
                perror("Sent fail!(LIST)\n");
                exit(EXIT_FAILURE);
            }
            free(buffer_response_final);
            free(buffer_response);
        }

        else if (strcmp(p, "1") == 0)
        {
            p = strtok(NULL, "|");
            int nr_octeti_cale = atoi(p);

            p = strtok(NULL, "|");

            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            update_log("1", p);

            //

            for (int i = 0; i < numar_fisiere; i++)
            {
                if (strcmp(p, f[i].file_name) == 0)
                {
                    pthread_mutex_lock(&f[i].f_mutex);
                    while (f[i].write != 0)
                    {
                        pthread_cond_wait(&f[i].f_cond, &f[i].f_mutex);
                    }

                    f[i].read++;

                    int file_d = open(p, O_RDONLY);
                    if (file_d == -1)
                    {
                        snprintf(buffer_response, 10, "1|1|6|");
                        int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                        if (bytesSent < 0)
                        {
                            perror("Sent fail!(DOWNLOAD)\n");
                            exit(EXIT_FAILURE);
                        }
                        return;
                    }

                    char *buffer_file_content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
                    memset(buffer_file_content, 0, BUFFER_SIZE);
                    int bytesRead = read(file_d, buffer_file_content, BUFFER_SIZE);
                    if (bytesRead < 0)
                    {
                        perror("Read fail!(DOWNLOAD)\n");
                        exit(EXIT_FAILURE);
                    }

                    snprintf(buffer_response, 1000, "1|0|%ld|", (strlen(buffer_file_content)) + 7);
                    strcat(buffer_response, buffer_file_content);
                    strcat(buffer_response, "|");

                    int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                    if (bytesSent < 0)
                    {
                        perror("Sent fail!(DOWNLOAD)\n");
                        exit(EXIT_FAILURE);
                    }
                    free(buffer_response);
                    free(buffer_file_content);

                    //
                    f[i].read--;
                    if (f[i].read == 0)
                    {
                        pthread_cond_signal(&f[i].f_cond);
                    }
                    pthread_mutex_unlock(&f[i].f_mutex);
                    break;
                }
            }
        }

        else if (strcmp(p, "2") == 0)
        {
            p = strtok(NULL, "|");
            uint32_t nr_octeti_cale = atoi(p);

            p = strtok(NULL, "|");

            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            update_log("2", p);

            char file_name[20];
            strcpy(file_name, p);

            p = strtok(NULL, "|");

            uint32_t nr_octeti_continut = atoi(p);
            char *buffer_continut = (char *)malloc(sizeof(char) * nr_octeti_continut);

            p = strtok(NULL, "|");

            strcpy(buffer_continut, p);

            int file_d = open(file_name, O_RDONLY);
            if (file_d == -1)
            {
                int newfile_d = open(file_name, O_WRONLY | O_CREAT, 0666);
                if (newfile_d == -1)
                {
                    perror("Eroare open!(NEW_FILE UPLOAD)\n");
                    exit(EXIT_FAILURE);
                }

                int bytesWrite = write(newfile_d, buffer_continut, nr_octeti_continut);
                if (bytesWrite < 0)
                {
                    perror("Write fail!(UPLOAD)\n");
                    exit(EXIT_FAILURE);
                }

                snprintf(buffer_response, 10, "2|0|6|");
                int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                if (bytesSent < 0)
                {
                    perror("Sent fail!(UPLOAD)\n");
                    exit(EXIT_FAILURE);
                }

                strcpy(f[numar_fisiere].file_name, file_name);
                f[numar_fisiere].name_dim = strlen(file_name);
                f[numar_fisiere].read = 0;
                f[numar_fisiere].write = 0;
                pthread_cond_init(&f[numar_fisiere].f_cond, NULL);
                pthread_mutex_init(&f[numar_fisiere].f_mutex, NULL);
                numar_fisiere++;
            }
            else
            {
                snprintf(buffer_response, 10, "2|2|6|");
                int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                if (bytesSent < 0)
                {
                    perror("Sent fail!(UPLOAD)\n");
                    exit(EXIT_FAILURE);
                }
                free(buffer_response);
                free(buffer_continut);
                return;
            }

            free(buffer_response);
            free(buffer_continut);

            trigger_reindexing();
        }

        else if (strcmp(p, "4") == 0)
        {
            p = strtok(NULL, "|");
            uint32_t nr_octeti_cale = atoi(p);

            p = strtok(NULL, "|");

            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            update_log("4", p);

            char file_name[20];
            strcpy(file_name, p);

            int deleteFile = remove(file_name);
            if (deleteFile == 0)
            {
                snprintf(buffer_response, 10, "4|0|6|");
                int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                if (bytesSent < 0)
                {
                    perror("Sent fail!(DELETE)\n");
                    exit(EXIT_FAILURE);
                }

                for (int i = 0; i < numar_fisiere; i++)
                {
                    if (strcmp(f[i].file_name, file_name) == 0)
                    {
                        strcpy(f[i].file_name, "hidden");
                        break;
                    }
                }
            }
            else
            {
                snprintf(buffer_response, 10, "4|1|6|");
                int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                if (bytesSent < 0)
                {
                    perror("Sent fail!(DELETE)\n");
                    exit(EXIT_FAILURE);
                }
            }

            free(buffer_response);
            trigger_reindexing();
        }

        else if (strcmp(p, "8") == 0)
        {
            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            p = strtok(NULL, "|");
            uint32_t nr_octeti_cale_vechi = atoi(p);

            p = strtok(NULL, "|");
            char file_name_vechi[20];
            strcpy(file_name_vechi, p);

            p = strtok(NULL, "|");
            uint32_t nr_octeti_cale_nou = atoi(p);

            p = strtok(NULL, "|");
            char file_name_nou[20];
            strcpy(file_name_nou, p);

            char intre_parantezee[40];
            strcpy(intre_parantezee, file_name_vechi);
            strcat(intre_parantezee, " -> ");
            strcat(intre_parantezee, file_name_nou);

            update_log("8", intre_parantezee);

            int file_d_vechi = open(file_name_vechi, O_RDONLY);
            if (file_d_vechi == -1)
            {
                snprintf(buffer_response, 10, "8|1|6|");
                int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                if (bytesSent < 0)
                {
                    perror("Sent fail!(MOVE)\n");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                char *buffer_content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
                memset(buffer_content, 0, BUFFER_SIZE);

                int bytesRead = read(file_d_vechi, buffer_content, BUFFER_SIZE);
                if (bytesRead < 0)
                {
                    perror("Sent fail!(MOVE)\n");
                    exit(EXIT_FAILURE);
                }
                int deleteFile = remove(file_name_vechi);
                if (deleteFile != 0)
                {
                    perror("Delete fail!(MOVE)\n");
                    exit(EXIT_FAILURE);
                }

                char dir_nou[10] = "";
                char copy_file_name_nou[40];
                strcpy(copy_file_name_nou, file_name_nou);
                char *pp = strtok(copy_file_name_nou, "/");
                strcpy(dir_nou, pp);

                struct stat statbuf;
                if (stat(dir_nou, &statbuf) != 0)
                {
                    mkdir(dir_nou, 0700);
                }

                int file_d_nou = open(file_name_nou, O_RDONLY);
                if (file_d_nou == -1)
                {
                    int file_d_nou_nou = open(file_name_nou, O_WRONLY | O_CREAT, 0666);
                    if (file_d_nou_nou == -1)
                    {
                        perror("Create file fail!(MOVE)\n");
                        exit(EXIT_FAILURE);
                    }

                    int bytesWrite = write(file_d_nou_nou, buffer_content, strlen(buffer_content));
                    if (bytesWrite < 0)
                    {
                        perror("Write fail!(MOVE)\n");
                        exit(EXIT_FAILURE);
                    }

                    snprintf(buffer_response, 10, "8|0|6|");
                    int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                    if (bytesSent < 0)
                    {
                        perror("Sent fail!(MOVE)\n");
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    snprintf(buffer_response, 10, "8|2|6|");
                    int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                    if (bytesSent < 0)
                    {
                        perror("Sent fail!(MOVE)\n");
                        exit(EXIT_FAILURE);
                    }
                }

                free(buffer_content);
            }
            free(buffer_response);
            trigger_reindexing();
        }

        else if (strcmp(p, "10") == 0)
        {
            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            p = strtok(NULL, "|");
            uint32_t nr_octeti_cale = atoi(p);

            p = strtok(NULL, "|");
            char file_name[20];
            strcpy(file_name, p);

            update_log("10", p);

            p = strtok(NULL, "|");
            int offset = atoi(p);

            p = strtok(NULL, "|");
            int dimens = atoi(p);

            p = strtok(NULL, "|");
            char *buffer_content = (char *)malloc(sizeof(char) * dimens);
            memset(buffer_content, 0, dimens);
            memcpy(buffer_content, p, dimens);

            int file_d = open(file_name, O_RDWR);
            if (file_d == -1)
            {
                snprintf(buffer_response, 10, "10|1|6|");
                int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                if (bytesSent < 0)
                {
                    perror("Sent fail!(UPDATE)\n");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                for (int i = 0; i < numar_fisiere; i++)
                {
                    if (strcmp(file_name, f[i].file_name) == 0)
                    {
                        pthread_mutex_lock(&f[i].f_mutex);
                        while (f[i].write != 0 || f[i].read != 0)
                        {
                            pthread_cond_wait(&f[i].f_cond, &f[i].f_mutex);
                        }
                        f[i].write++;

                        lseek(file_d, offset, SEEK_SET);

                        int bytesWrite = write(file_d, buffer_content, dimens);
                        if (bytesWrite < 0)
                        {
                            perror("Sent fail!(UPDATE)\n");
                            exit(EXIT_FAILURE);
                        }

                        f[i].write--;
                        pthread_cond_broadcast(&f[i].f_cond);
                        // Anuntam toate thread urile
                        pthread_mutex_unlock(&f[i].f_mutex);

                        snprintf(buffer_response, 10, "10|0|6|");
                        int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
                        if (bytesSent < 0)
                        {
                            perror("Sent fail!(UPDATE)\n");
                            exit(EXIT_FAILURE);
                        }

                        free(buffer_content);
                    }
                }
            }

            free(buffer_response);
            trigger_reindexing();
        }

        else if (strcmp(p, "20") == 0)
        {
            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            p = strtok(NULL, "|");
            uint32_t nr_octeti_cuvant = atoi(p);

            p = strtok(NULL, "|");
            char word_name[20];
            strcpy(word_name, p);

            update_log("20", p);

            DIR *dir;
            struct dirent *dirent;
            dir = opendir(".");

            if (dir)
            {
                while ((dirent = readdir(dir)) != NULL)
                {
                    if (dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
                    {
                        DIR *subdir;
                        struct dirent *subdirent;
                        subdir = opendir(dirent->d_name);

                        if (subdir)
                        {
                            while ((subdirent = readdir(subdir)) != NULL)
                            {
                                if (subdirent->d_type == DT_REG)
                                {
                                    char final_file_name[30] = "";
                                    strcpy(final_file_name, dirent->d_name);
                                    strcat(final_file_name, "/");
                                    strcat(final_file_name, subdirent->d_name);

                                    if (find_word(word_name, final_file_name) == 1)
                                    {
                                        strcat(buffer_response, final_file_name);
                                        strcat(buffer_response, "\\0");
                                    }
                                }
                            }
                        }
                        else
                        {
                            perror("Eroare open!(SUBDIR)\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else if (dirent->d_type == DT_REG)
                    {
                        if (find_word(word_name, dirent->d_name) == 1)
                        {
                            strcat(buffer_response, dirent->d_name);
                            strcat(buffer_response, "\\0");
                        }
                    }
                }
                closedir(dir);
            }
            else
            {
                perror("Eroare open!(DIR)\n");
                exit(EXIT_FAILURE);
            }

            char *buffer_response_final = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response_final, 0, BUFFER_SIZE);

            snprintf(buffer_response_final, 10, "20|0|");
            if (strlen(buffer_response) == 0)
                strcat(buffer_response_final, "gol");
            else
                strcat(buffer_response_final, buffer_response);
            strcat(buffer_response_final, "|");

            int bytesSent = send(client_socket, buffer_response_final, BUFFER_SIZE, 0);
            if (bytesSent < 0)
            {
                perror("Sent fail!(SEARCH)\n");
                exit(EXIT_FAILURE);
            }

            free(buffer_response_final);
            free(buffer_response);
        }

        else
        {
            char *buffer_response = (char *)malloc(sizeof(char) * BUFFER_SIZE);
            memset(buffer_response, 0, BUFFER_SIZE);

            snprintf(buffer_response, 5, "100|");
            int bytesSent = send(client_socket, buffer_response, BUFFER_SIZE, 0);
            if (bytesSent < 0)
            {
                perror("Sent fail!(UPDATE)\n");
                exit(EXIT_FAILURE);
            }

            free(buffer_response);
        }
    }
}

// DETALII DE IMPLEMENTARE

int find_word(char *word_name, char *file_name)
{
    int ok = 0;

    int file_d = open(file_name, O_RDONLY);
    char *buffer_content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    memset(buffer_content, 0, BUFFER_SIZE);

    int bytesRead = read(file_d, buffer_content, BUFFER_SIZE);
    char *p = strtok(buffer_content, " ");
    while (p)
    {
        if (strcmp(p, word_name) == 0)
        {
            ok = 1;
            break;
        }
        p = strtok(NULL, " ");
    }

    free(buffer_content);
    return ok;
}

void find_files(int *numar_fisiere, fileStats *fisiere)
{
    int i = 0;
    DIR *dir;
    struct dirent *dirent;
    dir = opendir(".");

    if (dir)
    {
        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
            {
                DIR *subdir;
                struct dirent *subdirent;
                subdir = opendir(dirent->d_name);

                if (subdir)
                {
                    while ((subdirent = readdir(subdir)) != NULL)
                    {
                        if (subdirent->d_type == DT_REG)
                        {
                            char final_file_name[30] = "";
                            strcpy(final_file_name, dirent->d_name);
                            strcat(final_file_name, "/");
                            strcat(final_file_name, subdirent->d_name);

                            strcpy(fisiere[i].file_name, final_file_name);
                            fisiere[i].name_dim = strlen(final_file_name);
                            fisiere[i].read = 0;
                            fisiere[i].write = 0;
                            pthread_cond_init(&fisiere[i].f_cond, NULL);
                            pthread_mutex_init(&fisiere[i].f_mutex, NULL);
                            i++;
                        }
                    }
                }
                else
                {
                    perror("Eroare open!(SUBDIR)\n");
                    exit(EXIT_FAILURE);
                }
            }
            else if (dirent->d_type == DT_REG)
            {

                strcpy(fisiere[i].file_name, dirent->d_name);
                fisiere[i].name_dim = strlen(dirent->d_name);
                fisiere[i].read = 0;
                fisiere[i].write = 0;
                pthread_cond_init(&fisiere[i].f_cond, NULL);
                pthread_mutex_init(&fisiere[i].f_mutex, NULL);
                i++;
            }
        }
        closedir(dir);
    }
    else
    {
        perror("Eroare open!(DIR)\n");
        exit(EXIT_FAILURE);
    }
    *numar_fisiere = i;
}

void index_file(int nr, fileStats *fisiere)
{
    FILE *file = fopen(fisiere[nr].file_name, "r");

    if (file == NULL)
    {
        return;
    }

    char word[30];
    wordFreq words[1000] = {0};
    int words_number = 0;

    while (fscanf(file, "%29s", word) == 1)
    {
        int found = 0;
        for (int i = 0; i < words_number; i++)
        {
            if (strcmp(words[i].word_name, word) == 0)
            {
                words[i].freq++;
                found = 1;
                break;
            }
        }
        if (found == 0 && words_number < 1000)
        {
            strcpy(words[words_number].word_name, word);
            words[words_number].freq = 1;
            words_number++;
        }
    }

    for (int i = 0; i < words_number - 1; i++)
    {
        for (int j = 0; j < words_number - i - 1; j++)
        {
            if (words[j].freq < words[j + 1].freq)
            {
                wordFreq temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 10 && i < words_number; i++)
    {
        strcpy(fisiere[nr].top[i].word_name, words[i].word_name);
        fisiere[nr].top[i].freq = words[i].freq;
    }

    fclose(file);
}

void *index_thread_function(void *vargp)
{
    specThreadData *data = (specThreadData *)vargp;

    find_files(data->numarFisiere, data->fisiere);
    for (int i = 0; i < *(data->numarFisiere); i++)
    {
        index_file(i, data->fisiere);
    }
    printf("*Specialised thread indexed files first time!*\n");

    while (!shutdown_flag)
    {
        pthread_mutex_lock(&mutex_index);

        while (!need_update)
        {
            pthread_cond_wait(&cond_index, &mutex_index);
        }

        need_update = 0;
        pthread_mutex_unlock(&mutex_index);

        //
        for (int i = 0; i < *(data->numarFisiere); i++)
        {
            if (strcmp(data->fisiere->file_name, "hidden") != 0)
                index_file(i, data->fisiere);
        }

        printf("*Specialised thread reindexed files!*\n");
        //
    }

    return NULL;
}

void *handle_client(void *vargp)
{
    int client_socket = *((int *)vargp);

    char buffer[BUFFER_SIZE] = "";

    int bytesRead = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    printf("Am primit de la client: %s\n", buffer);

    if (total_clients < MAX_CLIENTS)
        send_response(buffer, client_socket, 0);
    else
        send_response(buffer, client_socket, 1);

    close(client_socket);

    return NULL;
}

int setup_signal_fd()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
    {
        perror("Sigprocmask fail!\n");
        exit(EXIT_FAILURE);
    }

    int signal_fd = signalfd(-1, &mask, 0);
    if (signal_fd == -1)
    {
        perror("Signalfd fail!\n");
        exit(EXIT_FAILURE);
    }

    return signal_fd;
}

void trigger_reindexing()
{
    pthread_mutex_lock(&mutex_index);
    need_update = 1;
    pthread_cond_signal(&cond_index);
    pthread_mutex_unlock(&mutex_index);
}
