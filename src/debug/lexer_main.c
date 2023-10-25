/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:55:11 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/25 13:15:23 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	main(void)
{
	char	str[] = "ls -l > test.txt";
	t_token	*tokens;
	t_token	*cur;
	t_token	*temp;

	tokens = init_tokens(str);
	cur = tokens;
	while (cur)
	{
		printf("Type: %d, Value: %s\n", cur->type, (char *)cur->value);
		cur = cur->next;
	}
	// Don't forget to free the allocated memory when you're done.
	cur = tokens;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		free(temp->value);
		free(temp);
	}
	return (0);
}
