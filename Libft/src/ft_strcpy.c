/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:06:45 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/27 17:49:17 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = -1;
	if (!src)
	{
		dst[0] = 0;
		return (dst);
	}
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
