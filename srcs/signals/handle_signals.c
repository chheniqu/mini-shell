/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:36:20 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/25 20:38:53 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_is_sig;

void	handle_signals_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_is_sig = SIG_INT;
		write(1, "\n", 1);
		close(0);
	}
}

void	handle_signals_child(int sig)
{
	if (sig == SIGINT)
	{
		g_is_sig = SIG_INT;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_is_sig = SIG_QUIT;
		write(1, "Quit (core dumped)\n", 19);
	}
	else if (sig == SIGTSTP)
	{
		g_is_sig = SIG_TSTP;
		write(1, "Stopped (SIGTSTP)\n", 18);
	}
}

void	handle_signals_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_is_sig = SIG_INT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_signals_parent(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}
