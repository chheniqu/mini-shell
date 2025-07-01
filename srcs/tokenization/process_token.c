/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:21:05 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 11:44:31 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_token_data(t_token_data *data)
{
	data->word = NULL;
	data->clean_token = NULL;
	data->quote = NULL;
	data->clean_quotes = NULL;
}

static void	handle_word_token(char *line, int *i, t_token_data *data)
{
	data->word = extract_word(line, i, &data->quote);
	if (data->word && data->quote)
	{
		data->clean_token = remove_quotes(data->word, data->quote, \
			&data->clean_quotes);
		free(data->word);
		free(data->quote);
		data->word = data->clean_token;
		data->quote = data->clean_quotes;
	}
}

static t_token	*create_token(t_token_data *data, t_token_type type)
{
	t_token	*new;

	if (!data->word)
		return (NULL);
	new = new_token(data->word, type, data->quote);
	if (!new)
		return (free(data->quote), NULL);
	free (data->word);
	return (new);
}

t_token	*process_tokens(char *line, int *i)
{
	t_token_data	data;
	t_token_type	type;
	t_token			*new;

	new = NULL;
	init_token_data(&data);
	if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		type = token_type(line, i);
		if (type == INVALID)
			return (syntax_error("<"), NULL);
		else if (type == INVALID2)
			return (syntax_error("newline"), NULL);
		data.word = ft_strdup(symbol_type(type));
	}
	else
	{
		type = WORD;
		handle_word_token(line, i, &data);
	}
	if (!data.word)
		return (NULL);
	new = create_token(&data, type);
	return (new);
}
