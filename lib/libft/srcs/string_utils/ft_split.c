/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_protected.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:11:53 by armarboe          #+#    #+#             */
/*   Updated: 2024/11/24 12:32:36 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	count_words(const char *s, char c)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (res);
}

char	*allocate_word(const char *s, size_t start, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**write_words(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] && s[i + len] != c)
				len++;
			tab[j] = allocate_word(s, i, len);
			if (!tab[j])
				return (free_tab(tab));
			j++;
			i += len;
		}
		else
			i++;
		tab[j] = NULL;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		size;

	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		tab = malloc(sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	size = count_words(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	if (!write_words(tab, s, c))
		return (NULL);
	return (tab);
}
