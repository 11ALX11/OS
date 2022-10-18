#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

pid_t pid;
int relpid;

void child1();
void child2();
void child3();
void child4();
void child5();
void child6();

//0 1 1 2 4 4 4
//6, ls

int main()
{
    relpid = 0;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());

    pid = fork();
    switch (pid) {
        case -1:
            printf("Error doing fork() in procces %d", relpid);
            break;
        case 0:
            child1();
            break;
        default:
            pid = fork();
            switch (pid) {
                case -1:
                    printf("Error doing fork() in procces %d", relpid);
                    break;
                case 0:
                    child2();
                    break;
            }
    }

    sleep(10-relpid);
    printf("Procces %d exit PID = %d; PPID = %d\n", relpid, getpid(), getppid());
    return 0;
}

void child1() {
    relpid = 1;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());

    pid = fork();
    switch (pid) {
        case -1:
            printf("Error doing fork() in procces %d", relpid);
            break;
        case 0:
            child3();
            break;
    }
}

void child2() {
    relpid = 2;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());
}

void child3() {
    relpid = 3;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());

    pid = fork();
    switch (pid) {
        case -1:
            printf("Error doing fork() in procces %d", relpid);
            break;
        case 0:
            child4();
            break;
        default:
            pid = fork();
            switch (pid) {
                case -1:
                    printf("Error doing fork() in procces %d", relpid);
                    break;
                case 0:
                    child5();
                    break;
                default:
                    pid = fork();
                    switch (pid) {
                        case -1:
                            printf("Error doing fork() in procces %d", relpid);
                            break;
                        case 0:
                            child6();
                            break;
                    }
            }
    }
}

void child4() {
    relpid = 4;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());
}

void child5() {
    relpid = 5;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());

    printf("Procces %d exit PID = %d; PPID = %d\n", relpid, getpid(), getppid());
    execl("/bin/ls", "ls", "-l", NULL);
}

void child6() {
    relpid = 6;
    printf("Procces %d PID = %d; PPID = %d\n", relpid, getpid(), getppid());
}
