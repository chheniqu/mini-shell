/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:10:18 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/24 13:10:49 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expand(t_token *token)
{
	int	i;

	i = 0;
	if (!token || !token->value || !token->quote)
		return (FAILURE);
	if (token->type != WORD)
		return (FAILURE);
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->quote[i] != SINGLE_QUOTE && \
			token->value[i + 1] != '\0' && (ft_isalpha(token->value[i + 1]) || \
			token->value[i + 1] == '_' || token->value[i + 1] == '?'))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	*is_in_env(t_env *env, char *var)
{
	char	*find_in_env;

	find_in_env = NULL;
	if (!env)
		return (NULL);
	while (env)
	{
		if (env->value && env->key && (ft_strcmp(env->key, var) == 0))
		{
			find_in_env = ft_strdup(env->value);
			if (!find_in_env)
				return (NULL);
			return (find_in_env);
		}
		else
			env = env->next;
	}
	find_in_env = ft_strdup("");
	if (!find_in_env)
		return (NULL);
	return (find_in_env);
}
