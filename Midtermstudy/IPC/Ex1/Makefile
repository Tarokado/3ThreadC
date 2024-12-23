CC = gcc
CFLAGS = -Wall
TARGETS = Sever Client

all: $(TARGETS)

Sever: Sever.c
	$(CC) $(CFLAGS) -o Sever Sever.c

Client: Client.c
	$(CC) $(CFLAGS) -o Client Client.c

clean:
	rm -f $(TARGETS)
