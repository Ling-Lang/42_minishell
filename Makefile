NAME = minishell
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra 
DEBUG = -Wall -Wextra -g
LIB = -I ./Libft/src/ ./Libft/libft.a -lreadline

GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

SRC = 	src/main.c \
		src/utils/str_utils.c \
		src/utils/cmd.c \
		src/utils/loop.c \
		src/utils/builtins/echo.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) | lft
	@echo "$(GREEN)Compiling $@$(RESET)"
	@$(CC) $(LIB) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Finished compiling: $@$(RESET)"

%.o: %.c
	@$(CC) -c $< -o $@
lft:
	@cd Libft && make

debug: $(OBJ) | lft
	$(CC) $(LIB) $(DEBUG) $(OBJ) -o $(NAME)

clean:
	@echo "$(YELLOW)Cleaning object files$(RESET)"
	@$(RM) $(OBJ)
	@(cd Libft && make clean)

fclean: clean
	@echo "$(YELLOW)Cleaning executable $(NAME)$(RESET)"
	@$(RM) $(NAME)
	@(cd Libft && make fclean)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re lft