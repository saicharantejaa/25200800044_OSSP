CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = $(wildcard src/*.c)
OUT = nanokernel

all:
	@if [ -z "$(SRC)" ]; then echo "Add source files in src/"; else $(CC) $(CFLAGS) $(SRC) -o $(OUT); fi

run: all
	@if [ -f "$(OUT)" ]; then ./$(OUT); fi

clean:
	rm -f $(OUT)
