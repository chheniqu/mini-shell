/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:05:05 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 18:07:39 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_punctuation(t_shell *shell_data, t_cmd *cmd)
{
	int	exit_code;

	if (ft_strncmp(cmd->cmd_str, "!", 2) == 0)
		exit_code = 1;
	else if (ft_strncmp(cmd->cmd_str, ":", 2) == 0)
		exit_code = 0;
	else
		return ;
	shell_data->pipex_data->exit_status = exit_code;
	free_pipex(shell_data->pipex_data, exit_code);
	free_minishell(shell_data);
	free_env(shell_data);
	exit(exit_code);
}

int	is_directory(t_shell *shell_data, char *path)
{
	struct stat	path_data;
	DIR			*dir;

	dir = opendir(path);
	if (stat(path, &path_data) == -1)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (shell_data->pipex_data->exit_status = CMD_NOT_FOUND, SUCCESS);
	}
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (shell_data->pipex_data->exit_status = CMD_NOT_EXEC, SUCCESS);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		return (shell_data->pipex_data->exit_status = CMD_NOT_EXEC, SUCCESS);
	}
	return (FAILURE);
}

void	check_directory(t_shell *shell_data, t_cmd *cmd)
{
	if (ft_strchr(cmd->clean_cmd, '/') || ft_strchr(cmd->clean_cmd, '.'))
	{
		if (is_directory(shell_data, cmd->clean_cmd) == SUCCESS)
			cmd->is_directory = true;
	}
}
