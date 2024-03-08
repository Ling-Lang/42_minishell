/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_new_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:37:59 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:38:52 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*allocate_env(void)
{
	t_env	*res;

	res = (t_env *)malloc(sizeof(*res));
	if (!res)
		return (NULL);
	return (res);
}

char	*extract_name(char *env)
{
	return (ft_substr(env, 0, ft_strchr(env, '=') - env));
}

char	*extract_value(char *env, char *name)
{
	return (ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env)
			- ft_strlen(name) - 1));
}

void	free_resources(t_env *res, char *name, char *value)
{
	free(name);
	free(value);
	free(res);
}

t_env	*new_env(char *env)
{
	t_env	*res;
	char	*name;
	char	*value;

	res = allocate_env();
	if (!res)
		return (NULL);
	name = extract_name(env);
	value = extract_value(env, name);
	if (!name || !value)
	{
		free_resources(res, name, value);
		return (NULL);
	}
	res->name = name;
	res->value = value;
	res->next = NULL;
	return (res);
}
