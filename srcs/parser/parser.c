/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:43:33 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 14:23:08 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_word(t_token *token, t_shell_cmd *cmd)
{
	char	*new_cmd;
	char	*temp_str;

	if (!token || !cmd || !token->value)
		return ;
	if (token->type == WORD && token->next && token->next->type == WORD)
	{
		temp_str = ft_strjoin(cmd->cmd_str, " ");
		if (!temp_str)
			return ;
		if (ft_strncmp(token->next->value, " ", 2) == 0)
			new_cmd = ft_strjoin(temp_str, "\" \"");
		else
			new_cmd = ft_strjoin(temp_str, token->next->value);
		free(temp_str);
		if (!new_cmd)
			return ;
		free(cmd->cmd_str);
		cmd->cmd_str = new_cmd;
	}
	get_clean_shell_cmd(cmd);
}

t_token	*heredoc_position(t_token *token)
{
	t_token	*hd_position;
	t_token	*temp;

	if (!token)
		return (NULL);
	temp = token;
	hd_position = token;
	while (temp)
	{
		if (temp->type == PIPE && temp->next)
			hd_position = temp->next;
		if (temp->type == REDIR_HEREDOC)
			return (hd_position);
		temp = temp->next;
	}
	return (token);
}

void	handle_no_cmd(t_token *token, t_shell_cmd **cmd)
{
	if (!token || !token->value)
		return ;
	if (token->type == WORD)
	{
		*cmd = create_shell_cmd(token->value);
		if (!*cmd)
			return ;
	}
	else if (!*cmd && token->type != WORD && token->next)
	{
		*cmd = create_shell_cmd("");
		if (!*cmd)
			return ;
	}
}

t_shell_cmd	*parser(t_token *token)
{
	t_shell_cmd	*cmd_list;
	t_shell_cmd	*cmd;
	t_token		*temp;

	cmd_list = NULL;
	cmd = NULL;
	temp = token;
	if (check_spaces(token) == SUCCESS)
		return (NULL);
	while (temp)
	{
		if (temp->type == PIPE)
		{
			handle_pipe(&cmd_list, &cmd);
			temp = temp->next;
		}
		if (!cmd)
			handle_no_cmd(temp, &cmd);
		if (cmd)
			handle_cmd_node(temp, &cmd);
		temp = temp->next;
	}
	if (cmd)
		add_shell_cmd_to_list(&cmd_list, cmd);
	return (cmd_list);
}
