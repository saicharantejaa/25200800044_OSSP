#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Signal handler */
void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\nReceived SIGINT (Ctrl+C)\n");
    }
    else if (sig == SIGTERM)
    {
        printf("\nReceived SIGTERM\n");
    }
    else if (sig == SIGUSR1)
    {
        printf("\nReceived SIGUSR1\n");
    }

    printf("Signal handled successfully.\n");
}

int main()
{
    printf("Signal Handling Program\n");
    printf("PID = %d\n", getpid());
    printf("Waiting for signals...\n\n");

    /* Register signal handlers */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    while (1)
    {
        printf("Program is running...\n");
        sleep(2);
    }

    return 0;
}
