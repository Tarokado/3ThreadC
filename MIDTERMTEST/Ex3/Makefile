# Variables
CC = gcc
CFLAGS = -Wall -g
TARGETS = Client Sever
# Default rule: build all targets
all: $(TARGETS)
# Rule to build Sever executable
Sever: Sever.c
	$(CC) $(CFLAGS) -o Sever Sever.c
# Rule to build Client executable
Client: Client.c
	$(CC) $(CFLAGS) -o Client Client.c
# Clean rule to remove generated files
clean:
	rm -f $(TARGETS) *.o
