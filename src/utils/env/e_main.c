/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:55:32 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/10 02:27:05 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void add_env(t_env **env, t_env *new)
{
    t_env *cur;

    if (!(*env))
    {
        (*env) = new;
        return;
    }
    cur = (*env);
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new;
}
t_env	*new_env(char *env)
{
	t_env	*res;
	char	*name;
	char	*value;
	res = (t_env *)malloc(sizeof(*res));
	if (!res)
		return (NULL);
	name = ft_substr(env, 0, ft_strchr(env, '=') - env);
	value = ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env)
			- ft_strlen(name) - 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		free(res);
		return (NULL);
	}
	res->name = name;
	res->value = value;
	res->next = NULL;
	return (res);
}

char	**t_env_to_envp(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**envp;
	char	*tmp2;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->next;
	envp = (char **)malloc(sizeof(*envp) * (i + 1));
	if (!envp)
		return (NULL);
	envp[i] = NULL;
	tmp = env;
	i = -1;
	while (tmp)
	{
		tmp2 = ft_strjoin("=", tmp->value);
		if (!tmp2)
			return (NULL);
		envp[++i] = ft_strjoin(tmp->name, tmp2);
		free(tmp2);
		tmp = tmp->next;
	}
	return (envp);
}

