CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = Source/main.c
OUT = Output/practical-01.out

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
