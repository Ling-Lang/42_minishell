/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_strutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:28:05 by jkulka            #+#    #+#             */
/*   Updated: 2024/02/05 12:44:27 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strncpy(char *src, char *dst, int n)
{
	int	i;

	if (n == 0 || !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_wc(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
			i++;
	}
	return (wc);
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next_token;

	current = tokens;
	while (current)
	{
		next_token = current->next;
		free(current->value);
		free(current);
		current = next_token;
	}
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen((char *)s2) + 1);
	if (!s1 || !s2 || !(str))
	{
		return (0);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
