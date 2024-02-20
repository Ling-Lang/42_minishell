/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:52:45 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/20 12:55:28 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_str_len_quotes(char *str)
{
	int		i;
	int		len;
	int		inside;
	char	q;

	i = -1;
	len = 0;
	inside = 0;
	q = 0;
	while (str[++i])
	{
		if (inside == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			q = str[i];
			inside = 1;
		}
		else if (inside == 1 && q == str[i])
		{
			inside = 0;
			q = 0;
		}
		else
			len++;
	}
	return (len);
}

char	*ft_rem_quotes_double(char *str)
{
	int		i;
	int		inside;
	int		j;
	char	*ret;

	i = -1;
	inside = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_str_len_quotes(str) + 1));
	while (str[++i])
	{
		if (inside == 0 && (str[i] == '\"'))
			inside = 1;
		else if (inside == 1 && (str[i] == '\"'))
			inside = 0;
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_rem_quotes_single(char *str)
{
	int		i;
	int		inside;
	int		j;
	char	*ret;

	i = -1;
	inside = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_str_len_quotes(str) + 1));
	while (str[++i])
	{
		if (inside == 0 && (str[i] == '\''))
			inside = 1;
		else if (inside == 1 && (str[i] == '\''))
			inside = 0;
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}
