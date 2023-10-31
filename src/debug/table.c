/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:21:24 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/31 14:36:54 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "test.h"

void free_table(t_ptable **table)
{
    t_ptable **start;

    if(table)
    {
        start = table;
        while(*table)
        {
            free(*table);
            ++table;
        }
        free(start);
    }
}
void free_lines(char *line, char **args)
{
    char **start;
    
    if(line)
        free(line);
    if(args)
    {
        start = args;
        while(*args)
        {
            free(*args);
            ++args;
        }
        free(start);
    }
}
t_ptable *new_entry(char **arg)
{
    t_ptable *new;

    if(!arg)
        return NULL;
    new = (t_ptable *)malloc(sizeof(*new));
    if(!new)
        return NULL;
    new->state = ft_atoi(arg[0]);
    new->token = ft_atoi(arg[1]);
    new->action = ft_atoi(arg[2]);
    new->n_state = ft_atoi(arg[3]);
    new->reduce = ft_atoi(arg[4]);
    return new;
}
int create_entries(int fd, t_ptable **table)
{
    int i;
    int r;
    char *line;
    char **args;
    
    line = NULL;
    r = ft_get_next_line(fd, &line, 0);
    i = -1;
    while(r >= 0)
    {
        args = ft_split(line, 9);
        table[++i] = new_entry(args);
        free_lines(line, args);
        line = NULL;
        if(!table[i])
            return ERR;
        if(r == 0)
            break;
        r = ft_get_next_line(fd, &line, 0);
    }
    if(r == ERR)
        return ERR;
    return OK;
}
t_ptable **init_table(void)
{
    int fd;
    t_ptable **table;

    table = (t_ptable **)malloc(sizeof(*table) * (100 + 1));
    if(!table)
        return NULL;
    table[0] = NULL;
    table[100] = NULL;
    fd = open("test", O_RDONLY);
    if(fd == ERR)
    {
        free_table(table);
        return NULL;
    }
    if(create_entries(fd, table) == ERR)
    {
        free_table(table);
        close(fd);
        return NULL;
    }
    close(fd);
    return table;
}