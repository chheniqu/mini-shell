/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:46:58 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 16:44:18 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	ft_env(t_token *token, t_shell *data)
{
	t_env	*current;

	if (!token || !data || !data->env)
		return (SUCCESS);
	if (token->next)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	current = data->env;
	while (current)
	{
		if (current->key && current->value[0] != '\0')
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(current->value, STDOUT_FILENO);
		}
		current = current->next;
	}
	return (SUCCESS);
}
