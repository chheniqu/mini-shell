/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:41:48 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 13:22:26 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(char c, char *in_quotes)
{
	if (c == '\'' || c == '"')
	{
		if (!*in_quotes)
			*in_quotes = c;
		else if (*in_quotes == c)
			*in_quotes = 0;
	}
}

static void	handle_escape(char *line, int *i, char in_quotes)
{
	if (line[*i] == '\\' && !in_quotes && line[*i + 1])
	{
		if (line[*i + 1] == '$')
			(*i)++;
		else
			(*i) += 2;
	}
	else
		(*i)++;
}

static t_quote	*ft_quotes(char *word, int len)
{
	int		j;
	char	in_quotes;
	t_quote	*quotes;

	j = 0;
	in_quotes = 0;
	quotes = malloc((len + 1) * sizeof(t_quote));
	if (!quotes)
		return (NULL);
	while (j < len)
	{
		handle_quotes(word[j], &in_quotes);
		if (in_quotes == '\'')
			quotes[j] = SINGLE_QUOTE;
		else if (in_quotes == '"')
			quotes[j] = DOUBLE_QUOTE;
		else
			quotes[j] = NO_QUOTE;
		j++;
	}
	quotes[j] = NO_QUOTE;
	return (quotes);
}

char	*extract_word(char *line, int *i, t_quote **quote_str)
{
	int		start;
	int		len;
	int		processing;
	char	*word;
	char	in_quotes;

	start = *i;
	processing = 1;
	in_quotes = 0;
	while (line[*i] && (in_quotes || (line[*i] != ' ' && line[*i] != '\t' \
				&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')))
	{
		handle_quotes(line[*i], &in_quotes);
		handle_escape(line, i, in_quotes);
	}
	len = *i - start;
	word = ft_substr(line, start, *i - start);
	if (!word)
		return (NULL);
	*quote_str = ft_quotes(word, len);
	if (!*quote_str)
		return (free(word), NULL);
	return (word);
}
