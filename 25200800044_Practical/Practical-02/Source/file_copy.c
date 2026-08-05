#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd1, fd2;
    char ch;
    char src[100], dest[100];

    printf("Enter source file name: ");
    scanf("%99s", src);
    printf("Enter destination file name: ");
    scanf("%99s", dest);

    fd1 = open(src, O_RDONLY);
    if (fd1 < 0) {
        perror("open source");
        return 1;
    }

    fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("open destination");
        close(fd1);
        return 1;
    }

    while (read(fd1, &ch, 1) > 0) {
        if (write(fd2, &ch, 1) < 0) {
            perror("write");
            close(fd1);
            close(fd2);
            return 1;
        }
    }

    printf("File copied successfully.\n");

    close(fd1);
    close(fd2);
    return 0;
}
