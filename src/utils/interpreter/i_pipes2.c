/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_pipes2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:55:38 by ahocuk            #+#    #+#             */
/*   Updated: 2023/11/27 21:47:13 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**copy_string_array(char **original)
{
	int		size;
	char	**copy;
	int		i;

	size = 0;
	while (original[size] != NULL)
		size++;
	copy = (char **)malloc((size + 1) * sizeof(char *));
	i = 0;
	while (i <= size)
	{
		if (original[i] != NULL)
		{
			copy[i] = strdup(original[i]);
			if (copy[i] == NULL)
			{
				free_string_array(copy);
				return (NULL);
			}
		}
		else
			copy[i] = NULL;
		i++;
	}
	return (copy);
}

void	pipe_free(char ***commands, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		free(commands[i]);
		++i;
	}
	free(commands);
}

char	***add_pipe(char **args, int *num_commands)
{
	char	***commands;
	int		command_index;
	char	**tmp;

	commands = (char ***)malloc(64 * sizeof(char **));
	command_index = 0;
	while (args[0] != NULL)
	{
		tmp = copy_string_array(args);
		remove_pipe_symbol(tmp);
		commands[command_index++] = tmp;
		while (check_builtin(args[0]) != 5 && args[0] != NULL)
			shift_elements(args, 0);
		shift_elements(args, 0);
	}
	*num_commands = command_index;
	return (commands);
}
