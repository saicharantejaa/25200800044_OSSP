#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];
    char source_file[100], destination_file[100];

    printf("Enter source file name: ");
    scanf("%99s", source_file);
    printf("Enter destination file name: ");
    scanf("%99s", destination_file);

    source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return 1;
    }

    dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from source file");
    } else {
        printf("File copied successfully.\n");
    }

    close(source_fd);
    close(dest_fd);
    return 0;
}
