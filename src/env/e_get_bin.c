/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_get_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:35:09 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:36:02 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**split_path(char *path)
{
	if (!path)
		return (ft_split(".", ':'));
	else
		return (ft_split(path, ':'));
}

int	get_bin(char **arg, t_env *env)
{
	char	*path;
	char	**dir;

	if (ft_strchr(*arg, '/'))
		return (0);
	path = get_env("PATH", env);
	dir = split_path(path);
	if (!dir)
		return (ERR);
	*arg = get_path(dir, *arg);
	return (0);
}
