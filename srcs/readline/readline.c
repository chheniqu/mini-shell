/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:59:19 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/27 12:26:27 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

extern int	g_is_sig;

void	read_prompt(t_shell *data)
{
	char	*line;

	if (!data)
		return ;
	while (1)
	{
		init_signals_parent();
		line = readline("minishell> ");
		if (g_is_sig == SIG_INT)
			data->last_status = 130;
		if (line == NULL)
		{
			free_env(data);
			exit(data->last_status);
		}
		if (*line != '\0')
		{
			add_history(line);
			ft_minishell(data, line);
		}
		free(line);
	}
	rl_clear_history();
}
