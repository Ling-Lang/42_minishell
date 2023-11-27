/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:08:50 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 03:00:24 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env	*set_env(char *envp)
{
	t_env	*tmp;
	t_env	*env;

	env = NULL;
	tmp = new_env(envp);
	if (!tmp)
		return (NULL);
	add_env(&env, tmp);
	return (env);
}

int	ft_export(t_env **env, char **arg)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!arg[1])
	{
		tmp = *env;
		while (tmp != NULL)
		{
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
		return (OK);
	}
	else
	{
		while (arg[i] != NULL)
		{
			add_env(env, set_env(arg[i]));
			i++;
			if (arg[i] == NULL)
				return (OK);
		}
	}
	return (OK);
}

void	ft_export_special(char ****commands, int index, t_env **env)
{
	char	**export_args;

	export_args = (*commands)[index];
	ft_export(env, export_args);
}
