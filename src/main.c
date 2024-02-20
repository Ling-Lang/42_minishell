/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:36 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/20 14:17:48 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_main(t_env **env, t_ptable **table, t_return *ret)
{
	char		*str;
	t_token		*input;
	t_node		*tree;

	ret->r_code = 0;
	while (ret->should_exit == false)
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
		ft_sanitize_tokens(&input, *env, ret->r_code);
		tree = parser(input, table);
		exec_tree(tree, env, ret);
		free_tree(&tree);
	}
	free_table(table);
}

int	main(int argc, char **argv, char **envp)
{
	t_return	ret;
	t_env		*env;
	t_ptable	**table;

	(void)argc;
	(void)argv;
	ret.r_code = 0;
	ret.should_exit = false;
	signal(SIGINT, handlectrl);
	signal(SIGQUIT, SIG_IGN);
	table = init_table();
	if (table == NULL)
		return (EXIT_FAILURE);
	env = ft_init(envp);
	ft_main(&env, table, &ret);
	ft_free_env(&env);
	if (ret.r_code == ERR)
		return (EXIT_FAILURE);
	return (ret.r_code);
}

	// system("leaks minishell");