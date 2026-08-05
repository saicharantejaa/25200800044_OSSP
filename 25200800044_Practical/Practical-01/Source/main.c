#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char command[100];
    pid_t pid;

    printf("Enter a Linux command: ");
    scanf("%99s", command);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child PID: %d\n", getpid());
        execlp(command, command, (char *)NULL);
        perror("exec failed");
        exit(1);
    } else {
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        wait(NULL);
        printf("Child finished execution.\n");
    }

    return 0;
}
