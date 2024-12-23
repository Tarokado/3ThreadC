# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Targets
all: Sever Client

# Build the server program (link with math library)
Sever: Sever.c
	$(CC) $(CFLAGS) -o Sever Sever.c -lm

# Build the client program
Client: Client.c
	$(CC) $(CFLAGS) -o Client Client.c

# Clean up the compiled files
clean:
	rm -f Sever Client
