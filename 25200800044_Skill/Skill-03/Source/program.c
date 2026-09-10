#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_HISTORY 10
#define BUFFER_SIZE 100

char *history[MAX_HISTORY];
int history_count = 0;
int history_index = 0;

/* Disable terminal's normal input processing */
void enable_raw_mode(struct termios *old)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, old);
    raw = *old;

    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/* Restore normal terminal mode */
void disable_raw_mode(struct termios *old)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, old);
}

/* Store command in history */
void add_history(const char *command)
{
    if (strlen(command) == 0)
        return;

    if (history_count < MAX_HISTORY)
    {
        history[history_count] = strdup(command);
        history_count++;
    }
    else
    {
        free(history[0]);

        for (int i = 1; i < MAX_HISTORY; i++)
            history[i - 1] = history[i];

        history[MAX_HISTORY - 1] = strdup(command);
    }

    history_index = history_count;
}

/* Clear current line */
void clear_line(int length)
{
    for (int i = 0; i < length; i++)
        printf("\b \b");

    fflush(stdout);
}

/* Read command */
void read_command(char *buffer)
{
    int position = 0;
    int ch;

    struct termios old_terminal;

    enable_raw_mode(&old_terminal);

    printf("$ ");
    fflush(stdout);

    while (1)
    {
        ch = getchar();

        /* ENTER */
        if (ch == '\n' || ch == '\r')
        {
            buffer[position] = '\0';
            printf("\n");
            break;
        }

        /* BACKSPACE */
        else if (ch == 127 || ch == 8)
        {
            if (position > 0)
            {
                position--;
                buffer[position] = '\0';

                printf("\b \b");
                fflush(stdout);
            }
        }

        /* ESCAPE SEQUENCE */
        else if (ch == 27)
        {
            int second = getchar();

            if (second == '[')
            {
                int arrow = getchar();

                /* UP ARROW */
                if (arrow == 'A')
                {
                    if (history_index > 0)
                    {
                        clear_line(position);

                        history_index--;

                        strcpy(buffer, history[history_index]);
                        position = strlen(buffer);

                        printf("%s", buffer);
                        fflush(stdout);
                    }
                }

                /* DOWN ARROW */
                else if (arrow == 'B')
                {
                    if (history_index < history_count - 1)
                    {
                        clear_line(position);

                        history_index++;

                        strcpy(buffer, history[history_index]);
                        position = strlen(buffer);

                        printf("%s", buffer);
                        fflush(stdout);
                    }
                    else if (history_index == history_count - 1)
                    {
                        clear_line(position);

                        history_index = history_count;
                        position = 0;
                        buffer[0] = '\0';

                        fflush(stdout);
                    }
                }
            }
        }

        /* NORMAL CHARACTER */
        else if (position < BUFFER_SIZE - 1)
        {
            buffer[position++] = ch;
            putchar(ch);
            fflush(stdout);
        }
    }

    disable_raw_mode(&old_terminal);
}

int main()
{
    char buffer[BUFFER_SIZE];

    printf("Simple Command History Program\n");
    printf("Type commands and press Enter.\n");
    printf("Use UP/DOWN arrows to recall commands.\n");
    printf("Type exit to quit.\n\n");

    while (1)
    {
        read_command(buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        if (strlen(buffer) > 0)
            add_history(buffer);

        printf("You entered: %s\n", buffer);
    }

    /* Free history memory */
    for (int i = 0; i < history_count; i++)
        free(history[i]);

    return 0;
}
