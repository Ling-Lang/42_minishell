/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:58:59 by jkulka            #+#    #+#             */
/*   Updated: 2023/10/27 16:47:04 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "test.h"
int	ft_get_next_line(int fd, char **line, int to_free);
t_ptable *init_table(int fd)
{
    // READ until end and assign the t_ptable array atoi values
}
int main()
{
    // ft_printf("%s", get_next_line(open("test.txt", O_RDONLY)));
    char	str[] = "ls -l > test.txt";
	t_token	*tokens;
	t_token	*cur;
	t_token	*temp;
	int fd = open("test", O_RDONLY);
	char *tmp = NULL;
	int i = 1;
	while(i >= 0)
	{
		if(i == 0)
			break ;
		i = ft_get_next_line(fd, &tmp, 0);
		printf("%s\n", tmp);
	}
    // char **table = get_next_line(open("test.txt", O_RDONLY));)
    // printf("%s", ttype_names[SHIFT]);
	// tokens = init_tokens(str);
	// cur = tokens;
	// while (cur)
	// {
	// 	printf("Type: %d, Value: %s\n", cur->type, (char *)cur->value);
	// 	cur = cur->next;
	// }
	// // Don't forget to free the allocated memory when you're done.
	// cur = tokens;
	// while (cur)
	// {
	// 	temp = cur;
	// 	cur = cur->next;
	// 	free(temp->value);
	// 	free(temp);
	// }
}