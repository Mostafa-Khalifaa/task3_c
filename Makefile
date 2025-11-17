# Compiler and options
CC = gcc
CFLAGS = -Wall -g

# All .c files in project folder (removed menu.c)
SRCS = main.c color.c cursor.c draw.c screen.c input.c magic_square.c
OBJS = $(SRCS:.c=.o)
TARGET = magic_square

# Main rule
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Rule for each .c file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean temporary files
clean:
	rm -f *.o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)