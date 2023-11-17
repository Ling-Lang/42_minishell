NAME = minishell
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -ggdb3  -fsanitize=address
INCLUDE = -I ./Libft/src/ -L ./Libft/  -I ./include
LIB = -lft -lreadline

GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

SRC = 	src/main.c \
		src/utils/lexer/l_strutils.c \
		src/utils/lexer/l_main.c \
		src/utils/lexer/l_quotes.c \
		src/utils/lexer/l_tokens.c \
		src/utils/lexer/l_utils.c \
		src/utils/lexer/expander/le_main.c \
		src/utils/lexer/expander/le_quotes.c \
		src/utils/parser/p_main.c \
		src/utils/parser/p_action.c \
		src/utils/parser/p_clean.c \
		src/utils/parser/p_other.c \
		src/utils/parser/p_stack.c \
		src/utils/parser/p_tree.c \
		src/utils/parser/p_table.c \
		src/utils/parser/gnl.c \
		src/utils/interpreter/i_main.c \
		src/utils/interpreter/i_utils.c \
		src/utils/interpreter/i_cmd.c \
		src/utils/interpreter/i_fd.c \
		src/utils/interpreter/i_redirects.c \
		src/utils/builtins/echo.c \
		src/utils/builtins/cd.c \
		src/utils/builtins/pwd.c \
		src/utils/builtins/export.c \
		src/utils/builtins/unset.c \
		src/utils/builtins/env.c \
		src/utils/builtins/b_main.c \
		src/utils/builtins/exit.c \
		src/utils/init.c \
		src/utils/env/e_main.c \
		src/utils/env/e_paths.c \
		src/utils/error.c \
		src/utils/signals.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) | lft
	@echo "$(GREEN)Compiling $@$(RESET)"
	@$(CC) $(INCLUDE) $(OBJ) $(LIB) -o $(NAME) $(CFLAGS) 
	@echo "$(GREEN)Finished compiling: $@$(RESET)"

%.o: %.c
	@$(CC) -c $< -o $@ $(CFLAGS)
lft:
	@cd Libft && make

debug: clean $(OBJ) | lft
	$(CC) $(DEBUG) $(INCLUDE) $(OBJ) -o $(NAME) $(LIB) 

clean:
	@echo "$(YELLOW)Cleaning object files$(RESET)"
	@$(RM) $(OBJ)
	@(cd Libft && make clean)

fclean: clean
	@echo "$(YELLOW)Cleaning executable $(NAME)$(RESET)"
	@$(RM) $(NAME)
	@$(RM) ./valgrind.log 
	@(cd Libft && make fclean)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re lft