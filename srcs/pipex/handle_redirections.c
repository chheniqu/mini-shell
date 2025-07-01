/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:47:00 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 15:16:31 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_redir(t_shell *shell_data, t_cmd *cmd, t_redir *redir)
{
	if (redir->is_here_doc)
	{
		safe_dup2(redir->heredoc_read_fd, STDIN_FILENO, shell_data->pipex_data);
		close(redir->heredoc_read_fd);
	}
	else if (redir->type == REDIR_IN)
		handle_infile_redirection(shell_data, cmd, redir);
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		handle_outfile_redirection(shell_data, cmd, redir);
}

void	init_redir(t_shell *shell_data, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	close_unused_pipes(shell_data->pipex_data, cmd->cmd_index);
	while (redir)
	{
		handle_redir(shell_data, cmd, redir);
		redir = redir->next;
	}
	if (!has_redir_input(cmd->redir) && cmd->cmd_index > 0)
	{
		safe_dup2(shell_data->pipex_data->pipe_fd[cmd->cmd_index - 1][0], \
			STDIN_FILENO, shell_data->pipex_data);
		close(shell_data->pipex_data->pipe_fd[cmd->cmd_index - 1][0]);
	}
	if (!has_redir_output(cmd->redir) && cmd->next)
	{
		safe_dup2(shell_data->pipex_data->pipe_fd[cmd->cmd_index][1], \
			STDOUT_FILENO, shell_data->pipex_data);
		close(shell_data->pipex_data->pipe_fd[cmd->cmd_index][1]);
	}
}
