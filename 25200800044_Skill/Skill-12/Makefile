CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = $(wildcard Source/*.c)
OUT = Output/skill-12.out

all:
	@if [ -z "$(SRC)" ]; then echo "Add source files in Source/"; else $(CC) $(CFLAGS) $(SRC) -o $(OUT); fi

run: all
	@if [ -f "$(OUT)" ]; then ./$(OUT); fi

clean:
	rm -f $(OUT)
