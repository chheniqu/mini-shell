/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:46:49 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/25 20:35:36 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_quoted_word_minishell(char **tab, char *s, int *i, int *j)
{
	int		start;
	char	quote;

	quote = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	tab[*j] = ft_strncpy_minishell(s + start, *i - start);
	if (!tab[*j])
		return (0);
	(*j)++;
	if (s[*i] == quote)
		(*i)++;
	return (1);
}

static int	handle_normal_word_minishell(char **tab, char *s, int *i, int *j)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t'
		&& s[*i] != '\n' && s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	tab[*j] = ft_strncpy_minishell(s + start, *i - start);
	if (!tab[*j])
		return (0);
	(*j)++;
	return (1);
}

static int	fill_words_minishell(char **tab, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (!s[i])
			break ;
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!handle_quoted_word_minishell(tab, s, &i, &j))
				return (0);
		}
		else
		{
			if (!handle_normal_word_minishell(tab, s, &i, &j))
				return (0);
		}
	}
	tab[j] = NULL;
	return (1);
}

static int	count_words_minishell(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (!s[i])
			break ;
		if (s[i] == '\'' || s[i] == '"')
			skip_quote_minishell(s, &i, &count);
		else
		{
			count++;
			while (s[i] && s[i] != ' ' && s[i] != '\t'
				&& s[i] != '\n' && s[i] != '\'' && s[i] != '"')
				i++;
		}
	}
	return (count);
}

char	**ft_split_minishell(char *str)
{
	char	**tab;

	if (!str || check_quote(str) == FAILURE)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words_minishell(str) + 1));
	if (!tab)
		return (NULL);
	if (!fill_words_minishell(tab, str))
		return (free_tab_minishell(tab));
	return (tab);
}
