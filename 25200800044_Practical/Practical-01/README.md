# Practical-01

This practical demonstrates how a Linux operating system executes a command entered by a user.

The program accepts a Linux command, creates a child process using `fork()`, executes the command in the child process using an `exec()` system call, and allows the parent process to wait for completion using `wait()`.

## Files

- `Source/main.c`: C implementation.
- `Input/sample_input.txt`: sample command input.
- `Output/sample_output.txt`: sample execution output format.
- `Report.md`: practical write-up.

## Build and Run

```sh
make
make run
```
