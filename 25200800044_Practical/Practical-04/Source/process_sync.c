#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i;
    pid_t pid;
    int status;

    printf("Parent process started. PID = %d\n", getpid());

    // Create 3 child processes
    for (i = 1; i <= 3; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            printf("Child %d started. PID = %d\n", i, getpid());

            sleep(i);

            printf("Child %d finished. PID = %d\n", i, getpid());
            exit(i);
        }
    }

    // wait() waits for any one child
    printf("\nParent is using wait()...\n");

    pid = wait(&status);

    if (pid > 0)
    {
        printf("wait(): Child PID %d completed\n", pid);
    }

    // waitpid() waits for specific remaining children
    printf("\nParent is using waitpid()...\n");

    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        printf("waitpid(): Child PID %d completed\n", pid);
    }

    printf("\nAll child processes completed.\n");

    return 0;
}
