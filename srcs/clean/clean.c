/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:05:18 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 14:56:30 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	protect_ft_minishell(void *ptr, t_shell *data, char *sruct_name)
{
	if (!ptr)
	{
		ft_putstr_fd("error: no data->", STDERR_FILENO);
		ft_putendl_fd(sruct_name, STDERR_FILENO);
		free_minishell(data);
		exit(EXIT_FAILURE);
	}
}

void	free_minishell(t_shell *shell_data)
{
	if (shell_data->token)
		free_tokens(&shell_data->token);
	if (shell_data->shell_cmd)
		free_shell_cmd_list(shell_data->shell_cmd);
	if (shell_data->pipex_data)
		free(shell_data->pipex_data);
}
