/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:59:44 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/24 11:34:56 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_node(t_token *token)
{
	t_redir	*redir_node;

	if (!token)
		return (NULL);
	redir_node = malloc(sizeof(t_redir));
	if (!redir_node)
		return (NULL);
	redir_node->type = token->type;
	redir_node->infile = NULL;
	redir_node->outfile = NULL;
	redir_node->here_doc_lim = NULL;
	redir_node->is_here_doc = 0;
	redir_node->append = 0;
	redir_node->heredoc_read_fd = -1;
	redir_node->next = NULL;
	return (redir_node);
}

void	add_redir_to_list(t_redir **redir_list, t_redir *new)
{
	t_redir	*temp;

	if (!new)
		return ;
	if (!*redir_list)
		*redir_list = new;
	else
	{
		temp = *redir_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	free_redir_list_shell_cmd(t_shell_cmd *cmd)
{
	t_redir	*temp;
	t_redir	*next;

	if (!cmd || !cmd->redir)
		return ;
	temp = cmd->redir;
	while (temp)
	{
		next = temp->next;
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		if (temp->here_doc_lim)
			free(temp->here_doc_lim);
		free(temp);
		temp = next;
	}
	cmd->redir = NULL;
}

void	setup_redir_node(t_token *token, t_shell_cmd *cmd)
{
	t_redir	*redir_node;

	if (!token || !token->next || !cmd)
		return ;
	redir_node = create_redir_node(token);
	if (!redir_node)
		return ;
	if (token->type == REDIR_IN)
		redir_node->infile = ft_strdup(token->next->value);
	else if (token->type == REDIR_OUT)
		redir_node->outfile = ft_strdup(token->next->value);
	else if (token->type == REDIR_HEREDOC)
	{
		redir_node->is_here_doc = 1;
		if (redir_node->here_doc_lim)
			free(redir_node->here_doc_lim);
		redir_node->here_doc_lim = ft_strdup(token->next->value);
	}
	else if (token->type == REDIR_APPEND)
	{
		redir_node->append = 1;
		redir_node->outfile = ft_strdup(token->next->value);
	}
	add_redir_to_list(&cmd->redir, redir_node);
}
