/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:57:16 by armarboe          #+#    #+#             */
/*   Updated: 2025/06/27 12:28:09 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	size_env(t_env *env)
{
	int	res;

	res = 0;
	while (env)
	{
		res++;
		env = env->next;
	}
	return (res);
}

char	*join_key_value(t_env *env)
{
	char	*joined;
	char	*res;

	joined = ft_strjoin(env->key, "=");
	if (!joined)
		return (NULL);
	res = ft_strjoin(joined, env->value);
	free(joined);
	return (res);
}

char	**get_env_array(t_shell *data)
{
	char	**env_array;
	t_env	*env;
	int		len;
	int		i;

	len = size_env(data->env);
	env_array = malloc(sizeof(char *) * (len + 1));
	if (!env_array)
		return (NULL);
	env = data->env;
	i = 0;
	while (env)
	{
		env_array[i] = join_key_value(env);
		if (!env_array[i])
			return (free_tab_char(env_array), NULL);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
