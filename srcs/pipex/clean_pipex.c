/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:42:34 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/25 18:19:35 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_minishell_builtin(t_shell *shell_data)
{
	if (shell_data->token)
		free_tokens(&shell_data->token);
	if (shell_data->shell_cmd)
		free_shell_cmd_list(shell_data->shell_cmd);
}

void	free_token_builtin(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
	}
	*tokens = NULL;
}

void	free_cmd_list(t_pipex_data *data)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = data->cmd_list;
	while (temp)
	{
		next = temp->next;
		if (temp->cmd_str)
			free(temp->cmd_str);
		if (temp->clean_cmd)
			free(temp->clean_cmd);
		if (temp->cmd_path)
			free(temp->cmd_path);
		if (temp->execve_av)
			free_tab_char(temp->execve_av);
		free(temp);
		temp = next;
	}
	data->cmd_list = NULL;
}

int	free_pipex(t_pipex_data *data, int exit_status)
{
	if (data->path)
	{
		free_tab_char(data->path);
		data->path = NULL;
	}
	if (data->cmd_list)
	{
		free_cmd_list(data);
		data->cmd_list = NULL;
	}
	if (data->env)
	{
		free_tab_char(data->env);
		data->env = NULL;
	}
	close_all_pipes(data);
	return (exit_status);
}
