NAME = minishell
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra 
DEBUG = -Wall -Wextra -ggdb3
LIB = -I ./Libft/src/ ./Libft/libft.a -lreadline

GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

SRC = 	src/main.c \
		src/utils/lexer/split.c \
		src/utils/parser/cmd.c \
		src/utils/parser/loop.c \
		src/utils/builtins/echo.c \
		src/utils/builtins/cd.c \
		src/utils/builtins/pwd.c \
		src/utils/builtins/export.c \
		src/utils/init.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) | lft
	@echo "$(GREEN)Compiling $@$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)
	@echo "$(GREEN)Finished compiling: $@$(RESET)"

%.o: %.c
	@$(CC) -c $< -o $@ $(DEBUG)
lft:
	@cd Libft && make

debug: clean $(OBJ) | lft
	$(CC) $(OBJ) -o $(NAME) $(LIB) $(DEBUG)

clean:
	@echo "$(YELLOW)Cleaning object files$(RESET)"
	@$(RM) $(OBJ)
	@(cd Libft && make clean)

fclean: clean
	@echo "$(YELLOW)Cleaning executable $(NAME)$(RESET)"
	@$(RM) $(NAME)
	@$(RM) ./valgrind.log 
	@$(RM) -r ./minishell.dSYM
	@(cd Libft && make fclean)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re lft