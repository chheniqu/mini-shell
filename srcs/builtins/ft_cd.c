/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:21:38 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 17:51:41 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	update_env(t_shell *data, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;
	char	*new_value;
	char	*new_key;

	if (!key || !value)
		return ;
	new_value = ft_strdup(value);
	new_key = ft_strdup(key);
	if (!new_key || !new_value)
		return (free(new_key), free(new_value));
	current = data->env;
	while (current && ft_strcmp(current->key, new_key) != 0)
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = new_value;
		free(new_key);
		return ;
	}
	new_node = create_env_node(new_key, new_value);
	if (!new_node)
		return (free(new_key), free(new_value));
	return (free(new_key), free(new_value), add_var_to_list(data, new_node));
}

static t_env	*get_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_cd(t_token *args, t_shell *shell)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];
	t_env	*current;

	if (!args->next)
	{
		current = get_env_var(shell->env, "HOME");
		if (!current || !current->value[0])
			return (ft_putendl_fd("minishell: cd: HOME not set", \
				STDERR_FILENO), FAILURE);
		path = current->value;
	}
	else if (args->next && args->next->next)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	else
		path = args->next->value;
	if (!getcwd(old_pwd, PATH_MAX))
		return (perror("minishell: cd"), FAILURE);
	if (chdir(path) != 0)
		return (perror("minishell: cd"), FAILURE);
	update_env(shell, "OLDPWD", old_pwd);
	if (!getcwd(pwd, PATH_MAX))
		return (perror("minishell: cd"), FAILURE);
	return (update_env(shell, "PWD", pwd), SUCCESS);
}
