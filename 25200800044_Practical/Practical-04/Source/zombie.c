#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

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

        printf("Child is exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent process started.\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent sleeping for 30 seconds...\n");

        sleep(30);

        printf("Parent exiting...\n");
    }

    return 0;
}
