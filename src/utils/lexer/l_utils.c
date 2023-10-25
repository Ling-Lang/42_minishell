/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:07:48 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/25 13:35:44 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_separator(char s)
{
	if (s == ' ' || s == '>' || s == '<' || s == '|')
		return (1);
	return (0);
}

int	leading_separators(char *str, int len)
{
	while (is_separator(*str) && (*str) != ' ')
	{
		str++;
		len++;
	}
	return (len);
}

int	get_token_len(char *str)
{
	int	i;
	int	len;
	t_quote q;
	
	init_quote_struct(&q);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (is_separator(str[i]) == 1)
			break ;
		len++;
	}
	if (is_separator(*str) == 1)
		len = leading_separators(str, len);
	return (len);
}

int	get_token_ammount(char *str)
{
	int		i;
	int		len;
	int		c;
	bool	inside;

	i = 0;
	len = 0;
	c = 0;
	inside = false;
	while (*str)
	{
		while (*str == ' ' && *str)
			str++;
		len = get_token_len(str);
		str = str + len;
		c++;
	}
	return (c);
}

void init_quote_struct(t_quote *q)
{
	q->double_quote = 0;
	q->single_quote = 0;
}