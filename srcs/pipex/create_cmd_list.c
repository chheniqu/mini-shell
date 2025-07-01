/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:36:10 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 15:14:33 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*create_cmd_node(char *cmd_str)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_str = ft_strdup(cmd_str);
	if (!cmd->cmd_str)
	{
		free(cmd);
		return (NULL);
	}
	cmd->clean_cmd = NULL;
	cmd->cmd_path = NULL;
	cmd->execve_av = NULL;
	cmd->pid = -1;
	cmd->cmd_index = 0;
	cmd->is_directory = false;
	cmd->is_builtin_parent = false;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd_to_list(t_pipex_data *data, t_cmd *cmd)
{
	t_cmd	*temp;

	if (!data->cmd_list)
	{
		data->cmd_list = cmd;
		cmd->cmd_index = 0;
	}
	else
	{
		temp = data->cmd_list;
		while (temp->next)
			temp = temp->next;
		temp->next = cmd;
		cmd->cmd_index = temp->cmd_index + 1;
	}
}
