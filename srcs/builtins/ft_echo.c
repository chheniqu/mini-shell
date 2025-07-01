/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:46:46 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 17:34:43 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

static int	is_option_n(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_token *token)
{
	t_token	*current;
	int		new_line;

	current = token->next;
	new_line = 1;
	while (current && is_option_n(current->value))
	{
		new_line = 0;
		current = current->next;
	}
	while (current)
	{
		ft_putstr_fd(current->value, STDOUT_FILENO);
		if (current->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		current = current->next;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
