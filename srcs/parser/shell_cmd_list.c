/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:59:49 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/08 16:36:14 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell_cmd_list(t_shell_cmd *cmd_list)
{
	t_shell_cmd	*temp;
	t_shell_cmd	*next;

	if (!cmd_list)
		return ;
	temp = cmd_list;
	while (temp)
	{
		next = temp->next;
		if (temp->cmd_str)
			free(temp->cmd_str);
		if (temp->redir)
			free_redir_list_shell_cmd(temp);
		free(temp);
		temp = next;
	}
	cmd_list = NULL;
}

t_shell_cmd	*create_shell_cmd(char *cmd_str)
{
	t_shell_cmd	*cmd;

	if (!cmd_str)
		return (NULL);
	cmd = malloc(sizeof(t_shell_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_str = ft_strdup(cmd_str);
	if (!cmd->cmd_str)
	{
		free(cmd);
		return (NULL);
	}
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_shell_cmd_to_list(t_shell_cmd **cmd_list, t_shell_cmd *new)
{
	t_shell_cmd	*temp;

	if (!new)
		return ;
	if (!*cmd_list)
		*cmd_list = new;
	else
	{
		temp = *cmd_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
