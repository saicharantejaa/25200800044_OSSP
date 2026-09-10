#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "/tmp/client_to_server"
#define FIFO2 "/tmp/server_to_client"

int main()
{
    int fd1, fd2;
    char message[100];
    char response[100];

    printf("Client started.\n");

    while (1)
    {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        message[strcspn(message, "\n")] = '\0';

        // Send message to server
        fd1 = open(FIFO1, O_WRONLY);

        write(fd1, message, strlen(message) + 1);

        close(fd1);

        if (strcmp(message, "exit") == 0)
            break;

        // Receive response from server
        fd2 = open(FIFO2, O_RDONLY);

        read(fd2, response, sizeof(response));

        close(fd2);

        printf("Client received: %s\n", response);
    }

    printf("Client terminated.\n");

    return 0;
}
