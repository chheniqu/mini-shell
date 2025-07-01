/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:08:31 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 11:20:38 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_token	*copy_until_redir(t_token *start)
{
	t_token	*copy_start;
	t_token	*new;

	copy_start = NULL;
	while (start && start->type == WORD)
	{
		new = new_token(start->value, start->type, start->quote);
		if (!new)
		{
			free_tokens(&copy_start);
			return (NULL);
		}
		add_token_back(&copy_start, new);
		start = start->next;
	}
	return (copy_start);
}

t_token	*copy_until_pipe(t_token *start)
{
	t_token	*copy_start;
	t_token	*new;

	copy_start = NULL;
	while (start && start->type != PIPE)
	{
		new = new_token(start->value, start->type, start->quote);
		if (!new)
		{
			free_tokens(&copy_start);
			return (NULL);
		}
		add_token_back(&copy_start, new);
		start = start->next;
	}
	return (copy_start);
}

t_token	*find_start_token(t_token *token, int cmd_index)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = token;
	while (temp && i < cmd_index)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (temp);
}
