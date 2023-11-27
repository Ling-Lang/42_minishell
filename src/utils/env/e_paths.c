/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_paths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahocuk <ahocuk@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:02:32 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 03:02:43 by ahocuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*build_path(char *path, char *arg)
{
	char	*arg_path;
	char	*dir;

	dir = ft_strjoin(path, "/");
	arg_path = ft_strjoin(dir, arg);
	if (!arg_path)
	{
		free(dir);
		return (NULL);
	}
	free(dir);
	if (access(arg_path, F_OK | X_OK) == 0)
		return (arg_path);
	free(arg_path);
	return (NULL);
}

char	*get_path(char **dir, char *arg)
{
	char	*path;
	char	**start;

	start = dir;
	while (*dir)
	{
		path = build_path(*dir, arg);
		if (path)
		{
			while (*dir)
			{
				free(*dir);
				++dir;
			}
			free(start);
			free(arg);
			return (path);
		}
		free(path);
		free(*dir);
		++dir;
	}
	free(start);
	return (arg);
}

char	*get_env(char *find, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(find, tmp->name, ft_strlen(find)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_bin(char **arg, t_env *env)
{
	char	*path;
	char	**dir;

	if (ft_strchr(*arg, '/'))
		return (0);
	path = get_env("PATH", env);
	if (!path)
		dir = ft_split(".", ':');
	else
		dir = ft_split(path, ':');
	if (!dir)
		return (ERR);
	*arg = get_path(dir, *arg);
	return (0);
}
