#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_ITEMS 10

int main()
{
    int pipefd[2];
    pid_t pid;
    int data;
    struct timespec start, end;

    // Create pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    // Start measuring time
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid > 0)
    {
        // ================ PRODUCER (PARENT) ================

        close(pipefd[0]);  // Close unused read end

        printf("Producer (Parent) started. PID = %d\n", getpid());

        for (int i = 1; i <= NUM_ITEMS; i++)
        {
            data = i * 10;

            printf("Producer: Sending %d\n", data);

            write(pipefd[1], &data, sizeof(data));

            usleep(100000);  // 0.1 second
        }

        close(pipefd[1]);  // Signal end of data

        wait(NULL);       // Wait for consumer

        clock_gettime(CLOCK_MONOTONIC, &end);

        double elapsed =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("\nCommunication completed.\n");
        printf("Time taken: %.6f seconds\n", elapsed);
        printf("Items transferred: %d\n", NUM_ITEMS);
        printf("Communication rate: %.2f items/second\n",
               NUM_ITEMS / elapsed);
    }
    else
    {
        // ================ CONSUMER (CHILD) ================

        close(pipefd[1]);  // Close unused write end

        printf("Consumer (Child) started. PID = %d\n", getpid());

        while (read(pipefd[0], &data, sizeof(data)) > 0)
        {
            printf("Consumer: Received %d\n", data);
        }

        close(pipefd[0]);

        printf("Consumer finished.\n");

        exit(0);
    }

    return 0;
}
