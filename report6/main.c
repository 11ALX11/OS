#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

int fd;

void send_to_child(pid_t pid, char *string1, char *string2);
void send_to_parent();
void get_from_child();
void get_from_parent();

void *child_handler(int nsig);

int child_waiting = 1;
void child();

//pid - pid to another proccess
void parent(pid_t pid);

int main() {
    if ((fd = open("commonfile.tmp", O_CREAT | O_RDWR, 0666)) < 0) {
        printf("Error opening file!\n");
        exit(-1);
    }

    pid_t child_pid = fork();
    switch (child_pid) {
        case -1:
            printf("Error doing fork()!\n");
            exit(-1);
        case 0:
            printf("C\n");
            child();
            break;
        default:
            printf("P\n");
            parent(child_pid);
    }

    if (child_pid == 0) {
        printf("Child exit 0\n");
    }
    if (child_pid > 0) {
        printf("Parent exit 0\n");
    }

    close(fd);

    sleep(2);
    return 0;
}

void *child_handler(int nsig) {
    //get_from_parent();
    //send_to_parent();
    printf("handler");

    child_waiting = 0; //stop child
}

void child() {
    //setting handler
    signal(SIGUSR1, child_handler);

    while (child_waiting) {
        printf("Waiting for signal from parent...\n");
        sleep(1);
    }
}

void parent(pid_t pid) {
    char string1[] = "Hello \0";
    char string2[] = "world!\n\0";

    send_to_child(pid, string1, string2);
    //get_from_child();
}

void send_to_child(pid_t pid, char *string1, char *string2) {
    printf("Parent sending to child\n");

    int i = 0;
    while (string1[i] != '\n' && string1[i] != '\0') i++;
    write(fd, string1, ++i);

    i = 0;
    while (string2[i] != '\n' && string2[i] != '\0') i++;
    write(fd, string2, ++i);

    kill(pid, SIGUSR1);
}
