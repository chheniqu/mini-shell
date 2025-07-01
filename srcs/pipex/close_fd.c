/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:15:29 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/25 20:17:55 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_heredoc_fd(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->is_here_doc && redir->heredoc_read_fd != -1)
		{
			close(redir->heredoc_read_fd);
			redir->heredoc_read_fd = -1;
		}
		redir = redir->next;
	}
}

void	close_heredoc_read_fd(t_pipex_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd_list;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->is_here_doc && redir->heredoc_read_fd != -1)
			{
				close(redir->heredoc_read_fd);
				redir->heredoc_read_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	close_unused_pipes(t_pipex_data *data, int cmd_index)
{
	int	i;

	i = 0;
	while (i < data->pipes_count)
	{
		if (i != cmd_index)
			close(data->pipe_fd[i][1]);
		if (i != cmd_index - 1)
			close(data->pipe_fd[i][0]);
		i++;
	}
}

void	close_all_pipes(t_pipex_data *data)
{
	int	i;

	if (!data->pipe_fd)
		return ;
	i = 0;
	while (i < data->pipes_count)
	{
		if (data->pipe_fd[i])
		{
			close(data->pipe_fd[i][0]);
			close(data->pipe_fd[i][1]);
			free(data->pipe_fd[i]);
			data->pipe_fd[i] = NULL;
		}
		i++;
	}
	free(data->pipe_fd);
	data->pipe_fd = NULL;
}
