#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
    char command[256];
    pid_t pid;
    int status;

    printf("Enter a Linux command: ");
    fflush(stdout);

    if (fgets(command, sizeof(command), stdin) == NULL) {
        fprintf(stderr, "Failed to read command.\n");
        return 1;
    }

    command[strcspn(command, "\n")] = '\0';
    if (command[0] == '\0') {
        fprintf(stderr, "No command entered.\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child PID: %d\n", getpid());
        fflush(stdout);
        execlp("sh", "sh", "-c", command, (char *)NULL);
        perror("exec failed");
        exit(1);
    }

    printf("Parent PID: %d\n", getpid());
    printf("Child PID: %d\n", pid);

    if (wait(&status) == -1) {
        perror("wait failed");
        return 1;
    }

    if (WIFEXITED(status)) {
        printf("Child finished execution with exit status %d.\n", WEXITSTATUS(status));
    } else {
        printf("Child did not terminate normally.\n");
    }

    return 0;
}
