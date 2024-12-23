# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -pthread

# Target executable names
CLIENT = Client
SERVER = Sever

# Source files
CLIENT_SRC = Client.c
SERVER_SRC = Sever.c

# Build rules
all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC)

$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC)

# Clean up the generated files
clean:
	rm -f $(CLIENT) $(SERVER)
