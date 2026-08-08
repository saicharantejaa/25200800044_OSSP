#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("[Parent] Starting program. PID: %d, PPID: %d\n", getpid(), getppid());
    fflush(stdout); // Flush stdout to prevent duplicate output after fork
    
    // Create child process
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("[Child] Process created! PID: %d, PPID: %d\n", getpid(), getppid());
        printf("[Child] Sleeping for 6 seconds to show 'Waiting/Sleeping' state...\n");
        sleep(6);
        printf("[Child] Woke up. Exiting now.\n");
        exit(0);
    } else {
        // Parent process
        printf("[Parent] Created child process with PID: %d\n", pid);
        printf("[Parent] Sleeping for 2 seconds to allow child to sleep...\n");
        sleep(2);
        
        printf("[Parent] Woke up. Calling wait() to synchronize with child...\n");
        wait(NULL);
        printf("[Parent] Child has finished execution. Parent exiting.\n");
    }

    return 0;
}
