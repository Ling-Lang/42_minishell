/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 21:12:17 by ahocuk           ###   ########.fr       */
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

void	handle_sigquit(int signum)
{
	(void)signum;
	signal(SIGQUIT, SIG_IGN);
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

int	ft_main(t_env **env)
{
	char		*str;
	t_ptable	**table;
	t_token		*input;
	t_node		*ast;
	int			r;

	r = 0;
	table = init_table();
	signal(SIGINT, handlectrl);
	signal(SIGQUIT, handle_sigquit);
	while (r >= 0)
	{
		str = readline(BLU ">> " WHT);
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
		free(str);
		ft_sanitize_tokens(&input, *env, r);
		ast = parser(input, table);
		r = exec_tree(ast, env);
		free_tree(&ast);
	}
	free_table(table);
	return (r);
}
int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = ft_init(envp);
	ret = ft_main(&env);
	ft_free_env(&env);
	if (ret == ERR)
		return (EXIT_FAILURE);
	return (-ret - 2);
}
