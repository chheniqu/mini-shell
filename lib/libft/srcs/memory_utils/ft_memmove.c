/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:15:48 by armarboe          #+#    #+#             */
/*   Updated: 2024/11/23 17:35:44 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;

	if (!dest && !src)
		return (NULL);
	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dest;
	if (psrc < pdest)
	{
		while (n > 0)
		{
			pdest[n - 1] = psrc[n - 1];
			n--;
		}
	}
	else
		pdest = ft_memcpy(pdest, psrc, n);
	return (dest);
}
