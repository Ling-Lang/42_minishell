/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ih_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:37:10 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 19:28:03 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	ft_write_here(int fd, char **str, int len)
{
	int	ret;

	ret = write(fd, *str, len);
	free(*str);
	str = NULL;
	return (ret);
}

int	ft_open_fd(int fd, char *file, int *here_fd, int num)
{
	if (!close(fd))
	{
		fd = open(file, O_RDONLY);
		if (fd > 0)
		{
			here_fd[num] = fd;
			free(file);
			return (0);
		}
	}
	free(file);
	return (ERR);
}
