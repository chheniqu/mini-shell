/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:47:07 by chheniqu          #+#    #+#             */
/*   Updated: 2025/05/19 14:47:08 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path_name;

	path_name = getcwd(NULL, 0);
	if (path_name)
	{
		ft_putendl_fd(path_name, STDOUT_FILENO);
		free(path_name);
		return (SUCCESS);
	}
	else
	{
		perror("getcwd failed");
		return (FAILURE);
	}
}
