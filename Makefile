NAME = minishell
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra 
DEBUG = -Wall -Wextra -g
LIB = -I ./Libft/src/ ./Libft/libft.a

SRC = src/main.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) | lft
	$(CC) $(LIB) $(CFLAGS) $(OBJ) -o $(NAME)

lft:
	(cd Libft && make)

debug: $(OBJ) | lft
	$(CC) $(LIB) $(DEBUG) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	(cd Libft && make clean)

fclean: clean
	$(RM) $(NAME)
	(cd Libft && make fclean)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re lft