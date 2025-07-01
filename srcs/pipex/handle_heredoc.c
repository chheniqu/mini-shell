/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:43:31 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 13:42:36 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		g_is_sig = NO_SIG;

void	read_from_stdin(char *limiter, int pipe_heredoc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_is_sig == SIG_INT)
				break ;
			ft_putstr_fd("warning: here-document delimited ", 2);
			ft_putstr_fd("by end-of-file (wanted `", 2);
			ft_putstr_fd(limiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strncmp(line, limiter, (ft_strlen(line) + 1)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_heredoc, line, ft_strlen(line));
		write(pipe_heredoc, "\n", 1);
		free(line);
	}
	close(pipe_heredoc);
}

void	heredoc_child(t_shell *shell_data, t_redir *redir, int *pipe_heredoc)
{
	init_signals_heredoc();
	close_heredoc_read_fd(shell_data->pipex_data);
	close(pipe_heredoc[0]);
	read_from_stdin(redir->here_doc_lim, pipe_heredoc[1]);
	free_pipex(shell_data->pipex_data, EXIT_SUCCESS);
	free_minishell(shell_data);
	free_env(shell_data);
	if (g_is_sig == SIG_INT)
		exit(130);
	else
		exit(EXIT_SUCCESS);
}

void	heredoc_parent(t_shell *data, t_redir *redir, int *pipe_hd, int *pid)
{
	int		status;

	close(pipe_hd[1]);
	waitpid(*pid, &status, 0);
	redir->heredoc_read_fd = pipe_hd[0];
	if (WIFEXITED(status))
		data->pipex_data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->pipex_data->exit_status = 128 + WTERMSIG(status);
}

void	child_process_heredoc(t_shell *shell_data, t_redir *redir)
{
	pid_t	pid;
	int		pipe_heredoc[2];

	if (pipe(pipe_heredoc) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_heredoc[0]);
		close(pipe_heredoc[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		heredoc_child(shell_data, redir, pipe_heredoc);
	else
		heredoc_parent(shell_data, redir, pipe_heredoc, &pid);
}

void	handle_heredoc(t_shell *shell_data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = shell_data->pipex_data->cmd_list;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->is_here_doc)
				child_process_heredoc(shell_data, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
