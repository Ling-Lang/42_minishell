/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:55:11 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/24 16:43:17 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
int	get_token_type(char *str, int len)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * len + 1);
	ft_strncpy(str, tmp, len);
	// printf("\t%s\n", tmp);
	if (!ft_strcmp(tmp, ">"))
		return (free(tmp),R_TO_FILE);
	else if (!ft_strcmp(tmp, "<"))
		return (free(tmp), R_FROM_FILE);
	else if (!ft_strcmp(tmp, "|"))
		return (free(tmp), PIPE);
	else if (!ft_strcmp(tmp, "<<"))
		return (free(tmp), LESS);
	else if (!ft_strcmp(tmp, ">>"))
		return (free(tmp), GREATER);
    else
	    return (free(tmp), WORD);
}
int	is_separator(char s)
{
	if (s == ' ' || s == '>' || s == '<' || s == '|')
		return (1);
	return (0);
}
int	c_separator(char *str, int len)
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

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (is_separator(str[i]) == 1)
			break ;
		len++;
	}
	if (is_separator(*str) == 1)
		len = c_separator(str, len);
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
		// printf("%s\n", &str[i]);
		str = str + len;
		c++;
	}
	return (c);
}
t_token	*ft_tk_last(t_token *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
void	ft_tk_add_back(t_token **token, t_token *new)
{
	t_token	*last;

	last = *token;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_tk_last(*token);
	last->next = new;
}

t_token	*init_token(char *str, int len)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}
	// Set type to 0 (default)
	token->type = get_token_type(str, len);
	// Allocate memory for the value and copy the token string
	token->value = (char *)malloc(len + 1);
	if (token->value == NULL)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}
	ft_strncpy(str, (char *)(token->value), len);
	((char *)(token->value))[len] = '\0';
	token->next = NULL;
	return (token);
}

// Function to add a new token to the linked list
void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

t_token	*init_tokens(char *str)
{
	t_token	*tokens;
	int		len;
	t_token	*new_token;

	tokens = NULL;
	len = 0;
	while (*str)
	{
		while (*str == ' ' && *str)
			str++;
		len = get_token_len(str);
		if (!len)
			break ;
		new_token = init_token(str, len);
		add_token(&tokens, new_token);
		str = str + len;
	}
	return (tokens);
}

// int	main(void)
// {
// 	char	str[] = "ls -l > test.txt";
// 	t_token	*tokens;
// 	t_token	*cur;
// 	t_token	*temp;

// 	tokens = init_tokens(str);
// 	cur = tokens;
// 	while (cur)
// 	{
// 		printf("Type: %d, Value: %s\n", cur->type, (char *)cur->value);
// 		cur = cur->next;
// 	}
// 	// Don't forget to free the allocated memory when you're done.
// 	cur = tokens;
// 	while (cur)
// 	{
// 		temp = cur;
// 		cur = cur->next;
// 		free(temp->value);
// 		free(temp);
// 	}
// 	return (0);
// }
