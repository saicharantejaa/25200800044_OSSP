# Practical-03

## Aim
Develop a C program that uses the system calls open(), read(), write(), and close() to copy the contents of one file to another. Explain how control transitions between user space and kernel space during execution.

## Objectives
- Understand file handling system calls in Linux (`open`, `read`, `write`, `close`).
- Learn about file descriptors.
- Understand the transition between user space and kernel space during I/O operations.

## Programs
- `Source/copy_file.c`: C program to copy a file using system calls.

## Requirements
- GCC compiler
- Linux environment (WSL/Ubuntu)

## Compilation
```bash
make
```

## Execution
```bash
make run
```

## Result
The program successfully copies the contents of the source file to the destination file using low-level system calls, demonstrating direct interaction with the OS kernel.
