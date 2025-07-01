/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:12:48 by armarboe          #+#    #+#             */
/*   Updated: 2024/11/20 15:08:51 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;

	dest = malloc(nmemb * size);
	if (dest == NULL)
		return (NULL);
	ft_memset(dest, 0, nmemb * size);
	return ((char *)dest);
}
