/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_paths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:02:32 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:36:28 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	free_dir(char **dir)
{
	while (*dir)
	{
		free(*dir);
		++dir;
	}
}

char	*build_and_free(char **dir, char *arg)
{
	char	*path;

	path = build_path(*dir, arg);
	if (path)
	{
		free_dir(dir);
		free(arg);
	}
	return (path);
}

char	*get_path(char **dir, char *arg)
{
	char	*path;
	char	**start;

	start = dir;
	while (*dir)
	{
		path = build_and_free(dir, arg);
		if (path)
		{
			free(start);
			return (path);
		}
		free(*dir);
		++dir;
	}
	free(start);
	return (arg);
}
