/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:55:32 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/06 08:22:30 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_env(t_env **env, t_env *new)
{
	t_env	*cur;

	if (!(*env))
	{
		(*env) = new;
		return ;
	}
	cur = (*env);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
}

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
    return ft_substr(env, 0, ft_strchr(env, '=') - env);
}

char	*extract_value(char *env, char *name)
{
    return ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env) - ft_strlen(name) - 1);
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

// char	**t_env_to_envp(t_env *env)
// {
// 	int		i;
// 	t_env	*tmp;
// 	char	**envp;
// 	char	*tmp2;

// 	i = 0;
// 	tmp = env;
// 	while (tmp && ++i)
// 		tmp = tmp->next;
// 	envp = (char **)malloc(sizeof(*envp) * (i + 1));
// 	if (!envp)
// 		return (NULL);
// 	envp[i] = NULL;
// 	tmp = env;
// 	i = -1;
// 	while (tmp)
// 	{
// 		tmp2 = ft_strjoin("=", tmp->value);
// 		if (!tmp2)
// 			return (NULL);
// 		envp[++i] = ft_strjoin(tmp->name, tmp2);
// 		free(tmp2);
// 		tmp = tmp->next;
// 	}
// 	return (envp);
// }

int count_env(t_env *env)
{
    int		i;
    t_env	*tmp;

    i = 0;
    tmp = env;
    while (tmp && ++i)
        tmp = tmp->next;
    return i;
}

char **allocate_envp(int size)
{
    char **envp;

    envp = (char **)malloc(sizeof(*envp) * (size + 1));
    if (!envp)
        return (NULL);
    envp[size] = NULL;
    return envp;
}

char *join_name_value(t_env *tmp)
{
    char *tmp2;
    char *result;

    tmp2 = ft_strjoin("=", tmp->value);
    if (!tmp2)
        return (NULL);
    result = ft_strjoin(tmp->name, tmp2);
    free(tmp2);
    return result;
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

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((void *)(*env)->name);
		free((*env)->value);
		free((*env));
		*env = tmp;
	}
}
