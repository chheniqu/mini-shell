/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:20:56 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 16:38:50 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	clean_ft_exit(t_token *args, t_shell *shell)
{	
	close_all_pipes(shell->pipex_data);
	free_env(shell);
	free_tokens(&shell->token);
	free_shell_cmd_list(shell->shell_cmd);
	free_token_builtin(&args);
	free(shell->pipex_data);
}

static int	is_numeric(char *str)
{
	int		i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_token *args, t_shell *shell)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args->next)
		exit_code = shell->last_status % 256;
	else if (is_numeric(args->next->value) == 0)
	{
		ft_putendl_fd("minishell: exit: numeric argument required", \
			STDERR_FILENO);
		exit_code = 2;
	}
	else if (args->next->next)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->pipex_data->exit_status = 1;
		return (FAILURE);
	}
	else
		exit_code = ft_atoi(args->next->value) % 256;
	free_pipex(shell->pipex_data, exit_code);
	clean_ft_exit(args, shell);
	rl_clear_history();
	exit(exit_code);
}
