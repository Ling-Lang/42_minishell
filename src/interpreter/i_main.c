/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:38:35 by jkulka            #+#    #+#             */
/*   Updated: 2024/03/08 13:32:58 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**add_arg_back(char **arg, char *data)
{
	int		i;
	char	**res;

	if (!arg)
		return (NULL);
	res = (char **)malloc(sizeof(*res) * (arg_len(arg) + 2));
	if (!res)
		return (free_str_null(arg));
	i = -1;
	while (arg[++i])
	{
		res[i] = ft_strdup(arg[i]);
		if (!res[i])
		{
			free_str_array(arg);
			return (free_str_null(res));
		}
	}
	free_str_array(arg);
	res[i] = ft_strdup(data);
	if (!res[i])
		return (free_str_null(res));
	res[i + 1] = NULL;
	return (res);
}

char	**iterate_tree(t_node *node, char **args)
{
	if (!args || !node || (node && node->type == A_PIPE))
		return (args);
	args = iterate_tree(node->l, args);
	args = iterate_tree(node->r, args);
	if (node->type == A_PARAM || node->type == A_CMD)
	{
		if (node->type == A_CMD && ft_strchr(node->data, ' '))
			args = add_cmd(args, node);
		else
			args = add_arg_back(args, node->data);
	}
	return (args);
}

char	**iterate_tree2(t_node *node, char **args)
{
	if (!args || !node)
		return (args);
	args = iterate_tree2(node->l, args);
	args = iterate_tree2(node->r, args);
	if (node->type == A_PARAM || node->type == A_CMD || node->type == A_PIPE)
	{
		if (node->type == A_CMD && ft_strchr(node->data, ' '))
			args = add_cmd(args, node);
		else
			args = add_arg_back(args, node->data);
	}
	return (args);
}
