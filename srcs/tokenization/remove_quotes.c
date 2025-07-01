/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:30:19 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 11:49:02 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_clean_data(t_clean_data *data)
{
	data->i = 0;
	data->j = 0;
	data->current_quote = 0;
	data->word = NULL;
	data->quotes = NULL;
}

static void	handle_quotes(char *word, t_quote *quote, t_clean_data *clean)
{
	if ((word[clean->i] == '\'' || word[clean->i] == '"') && \
		!clean->current_quote)
	{
		clean->current_quote = word[clean->i];
		clean->i++;
	}
	else if (word[clean->i] == clean->current_quote)
	{
		clean->current_quote = 0;
		clean->i++;
	}
	else
	{
		clean->word[clean->j] = word[clean->i];
		clean->quotes[clean->j] = quote[clean->i];
		clean->j++;
		clean->i++;
	}
}

static void	handle_escape(char *word, t_quote *quote, t_clean_data *clean)
{
	clean->word[clean->j] = word[clean->i + 1];
	clean->quotes[clean->j] = quote[clean->i + 1];
	clean->j++;
	clean->i += 2;
}

static void	clean_array(t_clean_data *clean, char *word)
{
	size_t	len;

	len = ft_strlen(word) + 1;
	clean->word = malloc(len * sizeof(char));
	if (!clean->word)
		return ;
	if (clean->word)
		clean->quotes = malloc(len * sizeof(t_quote));
}

char	*remove_quotes(char *word, t_quote *quote, t_quote **new_quote)
{
	t_clean_data	clean;

	if (!word || !quote)
		return (NULL);
	init_clean_data(&clean);
	clean_array(&clean, word);
	if (!clean.word || !clean.quotes)
	{
		free (clean.word);
		return (NULL);
	}
	while (word[clean.i])
	{
		if (word[clean.i] == '\\' && clean.current_quote != '\'' && \
			word[clean.i + 1])
			handle_escape(word, quote, &clean);
		else
			handle_quotes(word, quote, &clean);
	}
	clean.word[clean.j] = '\0';
	clean.quotes[clean.j] = NO_QUOTE;
	*new_quote = clean.quotes;
	return (clean.word);
}
