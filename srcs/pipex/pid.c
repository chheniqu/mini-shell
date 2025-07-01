/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:23:25 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/25 20:17:34 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern int	g_is_sig;

void	handle_child_status(int status, t_shell *shell_data)
{
	if (WIFSIGNALED(status))
		shell_data->pipex_data->exit_status = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		shell_data->pipex_data->exit_status = 128 + WSTOPSIG(status);
	else if (WIFEXITED(status))
		shell_data->pipex_data->exit_status = WEXITSTATUS(status);
}

void	wait_for_children(t_shell *shell_data)
{
	int		status;
	t_cmd	*temp;

	status = 0;
	temp = shell_data->pipex_data->cmd_list;
	while (temp)
	{
		if (temp->pid > 0)
		{
			waitpid(temp->pid, &status, WUNTRACED);
			if (!temp->next)
				handle_child_status(status, shell_data);
		}
		temp = temp->next;
	}
	g_is_sig = NO_SIG;
}
