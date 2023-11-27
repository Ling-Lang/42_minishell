/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 21:25:26 by jkulka           ###   ########.fr       */
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

int	ft_main(t_env **env, t_ptable **table)
{
	char		*str;
	t_token		*input;
	t_node		*ast;
	int			r;

	r = 0;
	while (r >= 0)
	{
		str = readline(BLU ">> " WHT);
		if (str == NULL || str[0] == EOF)
			break ;
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
	int			ret;
	t_env		*env;
	t_ptable	**table;

	(void)argc;
	(void)argv;
	signal(SIGINT, handlectrl);
	signal(SIGQUIT, handle_sigquit);
	table = init_table();
	env = ft_init(envp);
	ret = ft_main(&env, table);
	ft_free_env(&env);
	if (ret == ERR)
		return (EXIT_FAILURE);
	return (-ret - 2);
}
