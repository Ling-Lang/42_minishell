/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 17:02:49 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Include the header file containing function declarations for builtin commands.
This allows the builtin commands to be called from this file.
*/
#include "../include/builtins.h"
#include "../include/minishell.h"

void	handlectrl(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ft_printf(BLU "\n>> " WHT);
}
/* What does this do? */

void	print_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%d\t%s\n", i, envp[i]);
		i++;
	}
}
const char	*ttype_names[] = {"END", "WORD", "R_TO_FILE", "R_FROM_FILE",
		"GREATER", "LESS", "PIPE"};
void	ft_print_tokens(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		ft_printf("Type: %d, Value: %s\n", cur->type, (char *)cur->value);
		cur = cur->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_ptable	**table;
	t_env		*env;
	t_token		*input;
	t_node		*ast;
	char		**args;

	(void)argc;
	(void)argv;
	table = init_table();
	env = ft_init(envp);
	signal(SIGINT, handlectrl);
	while ((str = readline(BLU ">> " WHT)))
	{
		if (str == NULL || str[0] == EOF)
		{
			ft_printf("exit");
			break ;
		}
		str[strcspn(str, "\n")] = '\0';
		if (str[0] == '\0')
			continue ;
		if (str[0] != '\0')
			add_history(str);
		input = init_tokens(str);
		ft_check_for_var(&input, env);
		ast = parser(input, table);
		// ft_printf("%s, %d\n", ast->data, ast->reduce);
		exec_tree(ast, &env);
		free_tree(&ast);
		// clear_token(input);
		// write(1, "1", 1);
	}
}
