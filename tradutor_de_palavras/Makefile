NAME = dumbphone
CC = gcc
CFLAGS = -Iinclude/
SRC = src/arquivo.c src/imprime_palavras.c src/main.c src/palavra.c src/tree.c src/usuario.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.c: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean:
	rm -f $(OBJ) $(NAME)

