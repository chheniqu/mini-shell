/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:08:32 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 14:24:44 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	remove_variable(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = shell->env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				shell->env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_token *token, t_shell *shell)
{
	t_token	*tmp;

	if (!token || !shell || !shell->env)
		return ;
	tmp = token->next;
	while (tmp)
	{
		if (check_key_format(tmp->value) == SUCCESS)
			remove_variable(shell, tmp->value);
		tmp = tmp->next;
	}
}
