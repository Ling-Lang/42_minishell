/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_table.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:23:31 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/12 14:51:57 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	free_table(t_ptable **table)
{
	t_ptable	**start;

	if (table)
	{
		start = table;
		while (*table)
		{
			free(*table);
			++table;
		}
		free(start);
	}
}

void	free_lines(char *line, char **args)
{
	char	**start;

	if (line)
		free(line);
	if (args)
	{
		start = args;
		while (*args)
		{
			free(*args);
			++args;
		}
		free(start);
	}
}

t_ptable	*new_entry(char **arg)
{
	t_ptable	*new;

	if (!arg)
		return (NULL);
	new = (t_ptable *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->state = ft_atoi(arg[0]);
	new->token = ft_atoi(arg[1]);
	new->action = ft_atoi(arg[2]);
	new->n_state = ft_atoi(arg[3]);
	new->reduce = ft_atoi(arg[4]);
	return (new);
}

int	read_table(int fd, t_ptable **table)
{
    int		i;
    char	*line;
    char	**args;

    line = get_next_line(fd);
    i = -1;
    while (line != NULL)
    {
        args = ft_split(line, 9);
        table[++i] = new_entry(args);
        free_lines(line, args);
        if (!table[i])
            return (ERR);
        line = get_next_line(fd);
    }
    return (OK);
}

t_ptable	**init_table(void)
{
    int			fd;
    t_ptable	**table;

    table = (t_ptable **)calloc(101, sizeof(*table));
    if (!table)
	{
    	return (NULL);
	}
	fd = open(TBL_PATH, O_RDONLY);
    if (fd == ERR)
    {
        free_table(table);
        return (NULL);
    }
    if (read_table(fd, table) == ERR)
    {
        free_table(table);
        close(fd);
        return (NULL);
    }
    close(fd);
    return (table);
}
