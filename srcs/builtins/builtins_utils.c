/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:09:07 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 14:01:49 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	is_builtin(char *token_value)
{
	if (!token_value || !*token_value)
		return (FAILURE);
	if (ft_strncmp(token_value, "cd", 3) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token_value, "echo", 5) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token_value, "env", 4) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token_value, "exit", 6) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token_value, "export", 7) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token_value, "pwd", 4) == 0)
		return (SUCCESS);
	else if (ft_strncmp(token_value, "unset", 6) == 0)
		return (SUCCESS);
	else
		return (FAILURE);
}

void	exec_builtins(t_token *token, t_shell *shell)
{
	if (!token || !token->value)
		return ;
	if (ft_strncmp(token->value, "cd", 3) == 0)
		ft_cd(token, shell);
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		ft_echo(token);
	else if (ft_strncmp(token->value, "env", 4) == 0)
		ft_env(token, shell);
	else if (ft_strncmp(token->value, "exit", 6) == 0)
		ft_exit(token, shell);
	else if (ft_strncmp(token->value, "export", 7) == 0)
		ft_export(token, shell);
	else if (ft_strncmp(token->value, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(token->value, "unset", 6) == 0)
		ft_unset(token, shell);
}
