#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child process started.\n");
        printf("Child PID = %d\n", getpid());

        sleep(2);

        printf("Child process exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent process started.\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        // Wait for the child
        waitpid(pid, &status, 0);

        printf("Parent: Child process completed.\n");
        printf("Zombie process eliminated.\n");
    }

    return 0;
}
