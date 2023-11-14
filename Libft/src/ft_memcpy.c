/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkulka <jkulka@student.42heilbronn.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:57:30 by jkulka            #+#    #+#             */
/*   Updated: 2023/11/14 15:52:04 by jkulka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void *src, unsigned int n)
{
	unsigned int i;

	i = -1;
	while(++i < n)
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
	return (dest);
}
