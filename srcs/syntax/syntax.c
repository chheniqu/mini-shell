/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:38:39 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 17:16:47 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

int	is_redirection(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_HEREDOC || type == REDIR_APPEND)
		return (SUCCESS);
	return (FAILURE);
}

int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (FAILURE);
}

static int	redirection_syntax(t_token *tokens)
{
	if (!tokens->next)
		return (syntax_error("newline"));
	if (tokens->next->type == PIPE)
		return (syntax_error("|"));
	if (tokens->type == REDIR_APPEND && tokens->next->type != WORD)
		return (syntax_error(">>"));
	if (tokens->type == REDIR_HEREDOC && tokens->next->type != WORD)
		return (syntax_error("<<"));
	if (tokens->type == REDIR_IN && tokens->next->type != WORD)
		return (syntax_error("<"));
	if (tokens->type == REDIR_OUT && tokens->next->type != WORD)
		return (syntax_error(">"));
	if (tokens->next->type != WORD)
		return (syntax_error("newline"));
	return (SUCCESS);
}

bool	has_syntax_error(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	if (!tokens)
		return (SUCCESS);
	if (ft_strncmp((tokens->value), ";", 2) == 0)
		return (syntax_error(";"));
	if (tokens->type == PIPE || last_token(tokens)-> type == PIPE)
		return (syntax_error("|"));
	while (tokens)
	{
		if (tokens->type == PIPE && prev && prev->type == PIPE)
			return (syntax_error("|"));
		if (is_redirection(tokens->type) == SUCCESS)
		{
			if (redirection_syntax(tokens) == FAILURE)
				return (FAILURE);
			tokens = tokens->next;
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
