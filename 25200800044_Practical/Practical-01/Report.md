# Practical-01 Report

## Aim

To develop a C program that demonstrates how a Linux operating system executes a command entered by a user using `fork()`, `exec()`, and `wait()`.

## Theory

Linux creates a new process using the `fork()` system call. The child process receives a separate process ID and can replace its program image using an `exec()` family system call. The parent process can synchronize with the child process using `wait()`, which blocks until the child finishes execution.

In this practical, the parent accepts a command from the user, creates a child process, and waits for the child. The child process executes the command through the shell using `execlp()`.

## Algorithm

1. Read a Linux command from standard input.
2. Validate that the command is not empty.
3. Create a child process using `fork()`.
4. In the child process, display the child PID and execute the command using `execlp()`.
5. In the parent process, display the parent PID and child PID.
6. Wait for the child process to complete using `wait()`.
7. Display the child's exit status.

## Output

Sample input is stored in `Input/sample_input.txt`.

Sample output format is stored in `Output/sample_output.txt`. Process IDs, host name, and kernel details vary by system.

## Conclusion

The program demonstrates process creation, command execution, and parent-child synchronization in Linux using core operating system system calls.
