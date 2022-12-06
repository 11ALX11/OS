#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t mutex;

int main() {

    pthread_mutex_init(&mutex, NULL);

    while (1) {
        char chr;
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
    }

}
