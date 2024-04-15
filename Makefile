CC=gcc
CFLAGS=-Wall -Wextra -Werror #-fsanitize=address -g3
BIN=my_mouse
SRC=src/main.c src/my_mouse.c src/matrix.c src/queue.c
INC=inc

all:
	$(CC) $(CFLAGS) -I$(INC) $(SRC) -o $(BIN)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(BIN)
re: fclean all
