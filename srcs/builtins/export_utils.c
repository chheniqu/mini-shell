/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:08:05 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/23 18:11:14 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

static void	bubble_sort(t_env **env_sorted, int count)
{
	int		i;
	int		j;
	t_env	*swap;

	i = 0;
	j = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_sorted[j]->key, env_sorted[j + 1]->key) > 0)
			{
				swap = env_sorted[j];
				env_sorted[j] = env_sorted[j + 1];
				env_sorted[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

static t_env	**sorted_array(t_env *env, int count)
{
	int		i;
	t_env	*tmp;
	t_env	**env_sorted;

	i = 0;
	env_sorted = malloc(count * sizeof(t_env *));
	if (!env_sorted)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		env_sorted[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	bubble_sort(env_sorted, count);
	return (env_sorted);
}

static void	print_env_sorted(t_env **env_sorted, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(env_sorted[i]->key, STDOUT_FILENO);
		if (env_sorted[i]->value && env_sorted[i]->value[0] == '\0')
			ft_putstr_fd("", STDOUT_FILENO);
		else if (env_sorted[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_sorted[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		i++;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	print_env(t_shell *shell)
{
	int		count;
	t_env	**env_sorted;

	count = count_env_vars(shell->env);
	env_sorted = sorted_array(shell->env, count);
	if (! env_sorted)
		return (FAILURE);
	print_env_sorted(env_sorted, count);
	free(env_sorted);
	return (SUCCESS);
}
