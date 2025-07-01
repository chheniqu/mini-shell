/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:49:50 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 16:15:28 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
			i += 2;
		else
		{
			if (s[i] == '\'' && (double_quote % 2 == 0))
				single_quote++;
			else if (s[i] == '"' && (single_quote % 2 == 0))
				double_quote++;
			i++;
		}		
	}
	if ((single_quote % 2) != 0 || (double_quote % 2) != 0)
		return (ft_putstr_fd("Wrong number of quotes\n", STDOUT_FILENO), \
		FAILURE);
	return (SUCCESS);
}
