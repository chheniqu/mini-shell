/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:51:41 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/26 18:03:08 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_txt_error(char *txt, char *cmd_str)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(txt, cmd_str);
	res = ft_strjoin(temp, "\n");
	free(temp);
	return (res);
}

int	check_infile(char *file_name, int fd)
{
	char	*errno_str;
	char	*txt_error;

	if (access(file_name, F_OK) == -1
		|| (access(file_name, R_OK) == -1 && fd == -1))
	{
		errno_str = ft_strjoin(strerror(errno), ": ");
		txt_error = ft_strjoin(errno_str, file_name);
		ft_putendl_fd(txt_error, STDERR_FILENO);
		free(errno_str);
		free(txt_error);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_outfile(char *file_name, int fd)
{
	char	*errno_str;
	char	*txt_error;

	if (access(file_name, W_OK) == -1 && fd == -1)
	{
		errno_str = ft_strjoin(strerror((errno)), ": ");
		txt_error = ft_strjoin(errno_str, file_name);
		ft_putendl_fd(txt_error, STDERR_FILENO);
		free(errno_str);
		free(txt_error);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_access(t_pipex_data *data, char *cmd_str)
{
	int		i;
	char	*cmd_path;
	char	*temp;

	if (!cmd_str || !data || !data->path)
		return (FAILURE);
	i = -1;
	while (data->path[++i])
	{
		cmd_path = ft_strdup(data->path[i]);
		temp = ft_strjoin(cmd_path, "/");
		free(cmd_path);
		cmd_path = ft_strjoin(temp, cmd_str);
		free(temp);
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd_path);
			return (SUCCESS);
		}
		free(cmd_path);
	}
	return (FAILURE);
}
