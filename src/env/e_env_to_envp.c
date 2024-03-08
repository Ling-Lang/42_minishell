/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_env_to_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:39:16 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:39:50 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	return (i);
}

char	**allocate_envp(int size)
{
	char	**envp;

	envp = (char **)malloc(sizeof(*envp) * (size + 1));
	if (!envp)
		return (NULL);
	envp[size] = NULL;
	return (envp);
}

char	*join_name_value(t_env *tmp)
{
	char	*tmp2;
	char	*result;

	tmp2 = ft_strjoin("=", tmp->value);
	if (!tmp2)
		return (NULL);
	result = ft_strjoin(tmp->name, tmp2);
	free(tmp2);
	return (result);
}

char	**t_env_to_envp(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**envp;

	i = count_env(env);
	envp = allocate_envp(i);
	if (!envp)
		return (NULL);
	tmp = env;
	i = -1;
	while (tmp)
	{
		envp[++i] = join_name_value(tmp);
		if (!envp[i])
			return (NULL);
		tmp = tmp->next;
	}
	return (envp);
}
