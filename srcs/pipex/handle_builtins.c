/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:49:11 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 15:23:29 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_token	*get_tokens_builtin(t_token *token, t_exec flag, int cmd_index)
{
	t_token	*start;
	t_token	*copy_start;

	if (!token)
		return (NULL);
	start = find_start_token(token, cmd_index);
	if (!start)
		return (NULL);
	if (flag == CHILD)
		copy_start = copy_until_pipe(start);
	else if (flag == PARENT)
		copy_start = copy_until_redir(start);
	else
		copy_start = NULL;
	return (copy_start);
}

void	exec_builtins_in_parent(t_shell *shell_data, t_cmd *cmd)
{
	int		saved_stdin;
	int		saved_stdout;
	t_token	*builtin_tokens;

	builtin_tokens = get_tokens_builtin(shell_data->token, \
		PARENT, cmd->cmd_index);
	if (ft_strncmp(cmd->clean_cmd, "exit", 5) == 0)
		exec_builtins(builtin_tokens, shell_data);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	init_redir(shell_data, cmd);
	if (shell_data->pipex_data->exit_status != EXIT_FAILURE)
		exec_builtins(builtin_tokens, shell_data);
	free_token_builtin(&builtin_tokens);
	free_tokens(&shell_data->token);
	free_pipex(shell_data->pipex_data, \
		shell_data->pipex_data->exit_status);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	close_all_pipes(shell_data->pipex_data);
}

void	exec_builtins_in_child(t_shell *shell_data, t_cmd *cmd)
{
	t_token	*builtin_tokens;

	builtin_tokens = get_tokens_builtin(shell_data->token, \
		CHILD, cmd->cmd_index);
	exec_builtins(builtin_tokens, shell_data);
	close_all_pipes(shell_data->pipex_data);
	free_token_builtin(&builtin_tokens);
	free_tokens(&shell_data->token);
	free_minishell_builtin(shell_data);
	free_env(shell_data);
	shell_data->last_status = free_pipex(shell_data->pipex_data, \
		shell_data->pipex_data->exit_status);
	free(shell_data->pipex_data);
	exit(shell_data->last_status);
}
