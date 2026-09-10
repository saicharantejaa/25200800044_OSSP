#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/client_to_server"
#define FIFO2 "/tmp/server_to_client"

int main()
{
    int fd1, fd2;
    char message[100];
    char response[100];

    // Create named pipes
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Server started...\n");

    while (1)
    {
        // Open client-to-server FIFO for reading
        fd1 = open(FIFO1, O_RDONLY);

        int n = read(fd1, message, sizeof(message) - 1);
          close(fd1);

            if (n <= 0)
            continue;

           message[n] = '\0';

            if (strcmp(message, "exit") == 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        printf("Server received: %s\n", message);

        // Prepare response
        snprintf(response, sizeof(response),
                 "Server processed: %s", message);

        // Open server-to-client FIFO for writing
        fd2 = open(FIFO2, O_WRONLY);

        write(fd2, response, strlen(response) + 1);
        close(fd2);
    }

    unlink(FIFO1);
    unlink(FIFO2);

    printf("Server terminated.\n");

    return 0;
}
