/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:47:07 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 15:28:34 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_infile_redirection(t_shell *shell, t_cmd *cmd, t_redir *redir)
{
	int	fd_infile;

	fd_infile = open(redir->infile, O_RDONLY);
	if (check_infile(redir->infile, fd_infile) == FAILURE)
	{
		if (cmd->is_builtin_parent)
		{
			shell->pipex_data->exit_status = EXIT_FAILURE;
			return ;
		}
		else
		{
			free_pipex(shell->pipex_data, EXIT_FAILURE);
			free_minishell(shell);
			free_env(shell);
			exit(EXIT_FAILURE);
		}
	}
	safe_dup2(fd_infile, STDIN_FILENO, shell->pipex_data);
	close (fd_infile);
}

void	handle_outfile_redirection(t_shell *shell, t_cmd *cmd, t_redir *redir)
{
	int	fd_outfile;

	(void)cmd;
	if (redir->append == 1)
		fd_outfile = open(redir->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_outfile = open(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (check_outfile(redir->outfile, fd_outfile) == FAILURE)
	{
		if (cmd->is_builtin_parent)
		{
			shell->pipex_data->exit_status = EXIT_FAILURE;
			return ;
		}
		else
		{
			free_pipex(shell->pipex_data, EXIT_FAILURE);
			free_minishell(shell);
			free_env(shell);
			exit(EXIT_FAILURE);
		}
	}
	safe_dup2(fd_outfile, STDOUT_FILENO, shell->pipex_data);
	close(fd_outfile);
}

int	has_redir_input(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->is_here_doc)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	has_redir_output(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}
