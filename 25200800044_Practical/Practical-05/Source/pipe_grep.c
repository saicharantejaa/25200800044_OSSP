#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Create first child for ls -l
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0)
    {
        // Child 1: execute ls -l

        close(pipefd[0]);  // Close read end

        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execlp("ls", "ls", "-l", NULL);

        // Only reached if exec fails
        perror("execlp ls");
        exit(1);
    }

    // Create second child for grep
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0)
    {
        // Child 2: execute grep ".c"

        close(pipefd[1]);  // Close write end

        // Redirect stdin from pipe
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);

        execlp("grep", "grep", ".c", NULL);

        // Only reached if exec fails
        perror("execlp grep");
        exit(1);
    }

    // Parent closes both pipe ends
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Command execution completed.\n");

    return 0;
}
