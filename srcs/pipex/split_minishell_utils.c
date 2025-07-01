/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:46:44 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/04 11:46:45 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_quote(char *s)
{
	int	i;
	int	count_single;
	int	count_double;

	i = 0;
	count_single = 0;
	count_double = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			count_single++;
		if (s[i] == '"')
			count_double++;
		i++;
	}
	if (count_single % 2 != 0 || count_double % 2 != 0)
		return (FAILURE);
	return (SUCCESS);
}

char	*ft_strncpy_minishell(char *s1, int n)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**free_tab_minishell(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	skip_quote_minishell(char *s, int *i, int *count)
{
	char	quote;

	quote = s[(*i)++];
	(*count)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
}
