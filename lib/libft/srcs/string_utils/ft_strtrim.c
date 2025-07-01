/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:18:48 by armarboe          #+#    #+#             */
/*   Updated: 2024/11/22 16:51:05 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_len_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_set(s1[i], set) == 1)
	{
		i++;
	}
	return (i);
}

int	ft_len_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	i = ft_strlen(s1) - 1;
	len = 0;
	while (i > 0 && is_set(s1[i], set) == 1)
	{
		i--;
		len++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		i;
	int		len_start;
	int		len_end;
	int		len_s1;

	if (!s1 || !set)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_start = ft_len_start(s1, set);
	len_end = ft_len_end(s1, set);
	if (len_start + len_end >= len_s1)
		return (ft_strdup(""));
	dest = malloc(sizeof(char) * (len_s1 - (len_start + len_end) + 1));
	if (!dest)
		return (NULL);
	i = len_start;
	while (i < len_s1 - len_end)
	{
		dest[i - len_start] = s1[i];
		i++;
	}
	dest[i - len_start] = '\0';
	return (dest);
}
