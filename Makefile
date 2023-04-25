CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

all: simon_says

simon_says: simon_says.c
	$(CC) $(CFLAGS) -o simon_says simon_says.c

clean:
	rm -f simon_says

