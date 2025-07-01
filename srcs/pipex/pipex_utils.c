/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:52:23 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 14:32:49 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_ft_pipe(t_shell *shell_data, char **env)
{
	init_signals_child();
	init_pipes(shell_data->pipex_data);
	get_path_tab(shell_data->pipex_data, env);
}

void	init_pipes(t_pipex_data *data)
{
	int	i;

	if (!data || data->pipes_count <= 0)
		return ;
	i = 0;
	data->pipe_fd = malloc(sizeof(int *) * data->pipes_count);
	if (!data->pipe_fd)
		free_pipex(data, EXIT_FAILURE);
	while (i < data->pipes_count)
	{
		data->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_fd[i])
			free_pipex(data, EXIT_FAILURE);
		if (pipe(data->pipe_fd[i]) == -1)
		{
			perror("pipe failed");
			free_pipex(data, EXIT_FAILURE);
		}
		i++;
	}
}

void	safe_dup2(int fd1, int fd2, t_pipex_data *data)
{
	if (dup2(fd1, fd2) == -1)
		free_pipex(data, EXIT_FAILURE);
}
