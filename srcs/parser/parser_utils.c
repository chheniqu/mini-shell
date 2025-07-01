/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:46:26 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 14:21:37 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char *s)
{
	int	i;

	if (!s)
		return (FAILURE);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	check_spaces(t_token *token)
{
	if (!token)
		return (FAILURE);
	if (is_whitespace(token->value) == SUCCESS)
	{
		ft_putstr_fd(token->value, STDOUT_FILENO);
		ft_putendl_fd(": command not found", STDOUT_FILENO);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	get_clean_shell_cmd(t_shell_cmd *cmd)
{
	int		i;
	char	*res;

	i = 0;
	if (!cmd || !cmd->cmd_str)
		return ;
	while (cmd->cmd_str[i] && cmd->cmd_str[i] == ' ')
		i++;
	res = ft_substr(cmd->cmd_str, i, ft_strlen(cmd->cmd_str + i));
	free(cmd->cmd_str);
	cmd->cmd_str = res;
}

void	handle_pipe(t_shell_cmd **cmd_list, t_shell_cmd **cmd)
{
	add_shell_cmd_to_list(cmd_list, *cmd);
	*cmd = NULL;
}

void	handle_cmd_node(t_token *token, t_shell_cmd **cmd)
{
	if (token->type == WORD)
		handle_word(token, *cmd);
	else if (token->type != PIPE)
		setup_redir_node(token, *cmd);
}
