# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -pthread

# Target executable
TARGET = thread_program

# Source files
SRCS = BothThread.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the target executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
