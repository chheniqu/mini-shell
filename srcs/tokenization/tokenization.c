/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:49:36 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/27 13:11:15 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	int				i;
	t_token			*tokens;
	t_token			*new;

	i = 0;
	tokens = NULL;
	if (!line || check_quotes(line) == FAILURE)
		return (NULL);
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		new = process_tokens(line, &i);
		if (!new)
		{
			free_tokens(&tokens);
			return (NULL);
		}
		add_token_back(&tokens, new);
	}
	return (tokens);
}
