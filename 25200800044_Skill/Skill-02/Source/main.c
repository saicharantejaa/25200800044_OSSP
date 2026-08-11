#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BUFFER_SIZE 1024

struct termios old_settings;

void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSADRAIN, &old_settings);
    printf("\r\nTerminal settings restored. Goodbye!\n");
}

int main() {
    struct termios new_settings;
    char input_buffer[BUFFER_SIZE];
    int buffer_index = 0;
    const char *prompt = "myshell> ";

    if (tcgetattr(STDIN_FILENO, &old_settings) != 0) {
        perror("tcgetattr failed");
        return EXIT_FAILURE;
    }
    
    atexit(restore_terminal);

    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO); 
    new_settings.c_cc[VMIN] = 1;  
    new_settings.c_cc[VTIME] = 0; 

    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &new_settings) != 0) {
        perror("tcsetattr failed");
        return EXIT_FAILURE;
    }

    printf("Interactive Loop Started. Type commands. Type 'exit' to quit.\r\n\n");

    printf("%s", prompt);
    fflush(stdout);

    while (1) {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) <= 0) {
            break; 
        }

        if (ch == '\r' || ch == '\n') {
            printf("\r\n");
            fflush(stdout);

            input_buffer[buffer_index] = '\0';

            if (strcasecmp(input_buffer, "exit") == 0) {
                break;
            }

            if (buffer_index > 0) {
                printf("Executed: %s\r\n", input_buffer);
            } else {
                printf("Empty command received.\r\n");
            }

            buffer_index = 0;
            printf("%s", prompt);
            fflush(stdout);
        }
        else if (ch == 127 || ch == '\b') {
            if (buffer_index > 0) {
                buffer_index--; 
                printf("\b \b");
                fflush(stdout);
            }
        }
        else if (ch < 32) {
            continue; 
        }
        else {
            if (buffer_index < BUFFER_SIZE - 1) {
                input_buffer[buffer_index++] = ch;
                putchar(ch);
                fflush(stdout);
            }
        }
    }

    return EXIT_SUCCESS;
}
