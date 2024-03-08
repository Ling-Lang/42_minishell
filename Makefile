NAME = minishell
RM = rm -f
CC = gcc -g
CFLAGS = -Wall -Werror -Wextra
DEBUG = -ggdb3
LIBFT := ./lib/Libft
HEADERS := -I ./include -I $(LIBFT)/include
LIB := -lreadline $(LIBFT)/libft.a

GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

SRC = 	src/main.c \
		src/lexer/l_strutils.c \
		src/lexer/l_main.c \
		src/lexer/l_tokens.c \
		src/lexer/l_utils.c \
		src/lexer/expander/le_main.c \
		src/lexer/expander/le_var.c \
		src/lexer/expander/le_quotes.c \
		src/parser/p_main.c \
		src/parser/p_action.c \
		src/parser/p_clean.c \
		src/parser/p_other.c \
		src/parser/p_stack.c \
		src/parser/p_tree.c \
		src/parser/p_table.c \
		src/parser/p_utils.c \
		src/parser/p_magic.c \
		src/parser/p_push.c \
		src/parser/p_reduce.c \
		src/interpreter/i_main.c \
		src/interpreter/i_main_helper.c \
		src/interpreter/i_utils.c \
		src/interpreter/i_utils2.c \
		src/interpreter/i_pipes.c \
		src/interpreter/i_exec_tree.c \
		src/interpreter/i_fd.c \
		src/interpreter/i_redirects.c \
		src/interpreter/i_ret_helper.c \
		src/interpreter/heredoc/ih_file.c \
		src/interpreter/heredoc/ih_main.c \
		src/interpreter/heredoc/ih_other.c \
		src/interpreter/heredoc/ih_limit.c \
		src/interpreter/heredoc/ih_utils.c \
		src/interpreter/i_pipes2.c \
		src/interpreter/i_execve.c \
		src/interpreter/i_exec_handler.c \
		src/interpreter/i_simple_cmd.c \
		src/builtins/echo.c \
		src/builtins/cd.c \
		src/builtins/pwd.c \
		src/builtins/export.c \
		src/builtins/unset.c \
		src/builtins/env.c \
		src/builtins/b_main.c \
		src/builtins/exit.c \
		src/env/e_main.c \
		src/env/e_get_bin.c \
		src/env/e_new_env.c \
		src/env/e_env_to_envp.c \
		src/env/e_paths.c \
		src/utils/init.c \
		src/utils/error.c \
		src/utils/signals.c

OBJ = $(patsubst %.c,obj/%.o,$(SRC))

all: lft $(NAME)

lft:
	@if [ ! -d "$(LIBFT)" ]; then \
		echo "$(YELLOW)Cloning Libft$(RESET)"; \
		git clone https://github.com/Ling-Lang/Libft $(LIBFT); \
	fi
		@cd $(LIBFT) && make;

$(NAME): $(OBJ) | lft
	@echo "$(GREEN)Compiling $@$(RESET)"
	@$(CC) $(HEADERS) $(OBJ) $(LIB) -o $(NAME) $(CFLAGS) 
	@echo "$(GREEN)Finished compiling: $@$(RESET)"

obj/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(CFLAGS) -g

debug: clean $(OBJ) | lft
	$(CC) $(CFLAGS) $(HEADERS) $(OBJ) -o $(NAME) $(LIB) 

clean:
	@echo "$(YELLOW)Cleaning object files$(RESET)"
	@rm -rf obj
	@(cd lib/Libft && make clean)

fclean: clean
	@echo "$(YELLOW)Cleaning executable $(NAME)$(RESET)"
	@$(RM) $(NAME)
	@$(RM) ./valgrind.log 
	@(cd lib/Libft && make fclean)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re lft