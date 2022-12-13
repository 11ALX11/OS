#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

const char empty_name[] = "report7_sem_empty";
const char full_name[] = "report7_sem_full";

pthread_mutex_t mutex;

int main() {

    sem_t* empty = sem_open(empty_name, O_CREAT, 0644, 1);
    sem_t* full = sem_open(full_name, O_CREAT, 0644, 0);
    pthread_mutex_init(&mutex, NULL);

    // model of a Producer proccessor

    while (1) {
        char chr;

        sem_wait(empty); //P(empty)

        if (!read(0, &chr, 1)) {
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

        sem_post(full); //V(full)
    }

    return 0;
}
