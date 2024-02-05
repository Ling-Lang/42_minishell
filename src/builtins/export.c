/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:08:50 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:06:14 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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

bool	ft_find_var(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, name))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_modify(char *arg, t_env **env)
{
	char	*name;
	char	*value;
	t_env	*tmp;

	tmp = *env;
	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg)
			- ft_strlen(name) - 1);
	if (ft_find_var(name, *env) == true)
	{
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->name, name))
				tmp->value = ft_strdup(value);
			tmp = tmp->next;
		}
	}
	else
		add_env(env, set_env(arg));
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
			ft_modify(arg[i], env);
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
