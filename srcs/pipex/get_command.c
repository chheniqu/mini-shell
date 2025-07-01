/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:52:19 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 13:42:44 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_clean_cmd(t_cmd *cmd, char *cmd_str)
{
	int		i;

	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == ' ')
		{
			cmd->clean_cmd = ft_substr(cmd_str, 0, i);
			return ;
		}
		i++;
	}
	cmd->clean_cmd = ft_strdup(cmd_str);
}

void	get_path_tab(t_pipex_data *data, char **env)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 4) == 0)
			temp = env[i];
		i++;
	}
	if (!temp)
		return ;
	data->path = ft_split(temp + 5, ':');
}

void	access_error(t_shell *shell_data, t_cmd *cmd)
{
	char	*txt_error;

	txt_error = get_txt_error("command not found: ", cmd->clean_cmd);
	ft_putstr_fd(txt_error, 2);
	free(txt_error);
	shell_data->last_status = free_pipex(shell_data->pipex_data, \
		CMD_NOT_FOUND);
	free_minishell(shell_data);
	free_env(shell_data);
	exit(shell_data->last_status);
}

void	build_cmd_path(t_shell *shell_data, t_cmd *cmd)
{
	char	*cmd_path;
	char	*temp;

	if (check_access(shell_data->pipex_data, cmd->clean_cmd) == FAILURE)
		access_error(shell_data, cmd);
	shell_data->pipex_data->i = -1;
	while (shell_data->pipex_data->path[++shell_data->pipex_data->i])
	{
		cmd_path = ft_strdup(shell_data->pipex_data->\
			path[shell_data->pipex_data->i]);
		temp = ft_strjoin(cmd_path, "/");
		free(cmd_path);
		cmd_path = ft_strjoin(temp, cmd->clean_cmd);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
	}
	cmd->cmd_path = ft_strdup(cmd_path);
	free(cmd_path);
}

void	get_cmd_path(t_shell *shell_data, t_cmd *cmd)
{
	char	*txt_error;

	if (strchr(cmd->clean_cmd, '/'))
	{
		if (access(cmd->clean_cmd, X_OK) == 0)
			cmd->cmd_path = ft_strdup(cmd->clean_cmd);
		else
		{
			txt_error = get_txt_error("command not found: ", cmd->clean_cmd);
			ft_putstr_fd(txt_error, 2);
			free(txt_error);
			free_pipex(shell_data->pipex_data, CMD_NOT_FOUND);
			free_minishell(shell_data);
			free_env(shell_data);
			exit(CMD_NOT_FOUND);
		}
	}
	else
		build_cmd_path(shell_data, cmd);
}
