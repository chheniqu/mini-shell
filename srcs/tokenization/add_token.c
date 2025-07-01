/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:49:23 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 11:48:26 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type, t_quote *quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free (token);
		return (NULL);
	}
	token->type = type;
	token->quote = quote;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		if (tmp->quote)
		{
			free(tmp->quote);
			tmp->quote = NULL;
		}
		free(tmp);
	}
	*tokens = NULL;
}
