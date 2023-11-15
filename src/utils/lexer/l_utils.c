/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:07:48 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/15 15:58:27 by jkulka           ###   ########.fr       */
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
	int		i;
	int		len;
	t_quote	q;

	init_quote_struct(&q);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			q.d_quote++;
		if (str[i] == '\'')
			q.s_quote++;
		if (is_separator(str[i]) && q.d_quote % 2 == 0 && q.s_quote % 2 == 0)
			break ;
		if (is_separator(str[i]) && q.d_quote % 2 == 1 && q.s_quote % 2 == 2)
			break ;
		if (is_separator(str[i]) && q.d_quote % 2 == 2 && q.s_quote % 2 == 1)
			break ;
		len++;
	}
	if (is_separator(*str) == 1)
		len = leading_separators(str, len);
	if (q.d_quote % 2 != 0 || q.s_quote % 2 != 0) {
		ft_printf("Unclosed quotes!\n");
		exit(-1); // Return error (-1) if quotes are unclosed at the end
	}
	return (len);
}

int	get_token_ammount(char *str)
{
	int		len;
	int		c;

	len = 0;
	c = 0;
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

void	init_quote_struct(t_quote *q)
{
	q->d_quote = 0;
	q->s_quote = 0;
}
