#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex;

int main() {

    pthread_mutex_init(&mutex, NULL);

    pid_t pid = fork();
    switch (pid) {
        case -1:
            printf("Error doing fork()");
            break;
        case 0:
            child();
            break;
        default:
            parent();
            break;
    }

    return 0;
}

void parent()
{
    while (1) {
        char chr;
        if (!read(0, &chr, 1)) {
            printf("continue (!read(...))\n");
            continue;
        }

        pthread_mutex_lock(&mutex);
        //critical section
        int fd;
        if ((fd = open("file.tmp", O_CREAT | O_RDWR, 0666)) < 0) {
            perror("Error opening file!");
            exit(-1);
        }

        write(fd, &chr, 1);

        close(fd);
        //critical section end
        pthread_mutex_unlock(&mutex);
    }
}

void child()
{
    char vowels[12] = "AEIOUYaeiouy";

    while (1) {
        char chr;

        pthread_mutex_lock(&mutex);
        //critical section
        int fd;
        if ((fd = open("file.tmp", O_CREAT | O_RDWR, 0666)) < 0) {
            perror("Error opening file!");
            exit(-1);
        }

        read(fd, &chr, 1);

        close(fd);
        //critical section end
        pthread_mutex_unlock(&mutex);

        if (strchr(vowels, chr) != NULL) {
            write(1, &chr, 1);
            chr = '\n';
            write(1, &chr, 1);
        }
    }
}
