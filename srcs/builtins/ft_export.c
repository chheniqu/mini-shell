/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:16:04 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/26 14:23:58 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	check_key_format(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (FAILURE);
	if (!(ft_isalpha(str[i])) && str[i] != '_')
		return (FAILURE);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i])) && str[i] != '_' && !(ft_isdigit(str[i])))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_env	*is_var(t_shell *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static bool	extract_key_value(char *arg, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = ft_substr(arg, 0, i);
	if (!*key)
		return (false);
	if (arg[i] == '=')
	{
		*value = ft_strdup(arg + i + 1);
		if (!*value)
		{
			free(*key);
			return (false);
		}
	}
	else
		*value = NULL;
	return (true);
}

void	export_var(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;
	bool	extraction;
	t_env	*is_var_existing;

	value = NULL;
	key = NULL;
	if (!arg)
		return ;
	extraction = extract_key_value(arg, &key, &value);
	if (extraction == false)
		return ;
	is_var_existing = is_var(shell, key);
	if (!value && is_var_existing)
	{
		free (key);
		return ;
	}
	if (value)
		update_env(shell, key, value);
	else
		update_env(shell, key, "");
	free (key);
	if (value)
		free (value);
}

int	ft_export(t_token *token, t_shell *shell)
{
	t_token	*tmp;

	if (!token->next)
	{
		print_env(shell);
		return (SUCCESS);
	}
	tmp = token->next;
	while (tmp)
	{
		if (check_key_format(tmp->value) == FAILURE)
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(tmp->value, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAILURE);
		}
		else
			export_var(shell, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
