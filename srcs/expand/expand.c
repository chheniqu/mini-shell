/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:43:28 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/24 13:10:59 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_variable_name(char *token, int start)
{
	int		i;
	int		len;
	char	*var_name;

	len = 0;
	i = start + 1;
	if (token[i] == '?')
		return (ft_strdup("?"));
	while (token[i] != '\0' && (ft_isalpha(token[i]) || \
		token[i] == '_' || ft_isdigit(token[i])))
	{
		i++;
		len++;
	}
	var_name = ft_substr(token, start + 1, len);
	if (!var_name)
		return (NULL);
	return (var_name);
}

static void	init_expand_var(t_expand_var *ev, t_shell *data)
{
	ev->i = 0;
	ev->var_len = 0;
	ev->value = NULL;
	ev->new_str = NULL;
	ev->var = NULL;
	ev->env = data->env;
}

static void	handle_last_status(t_expand_var *ev, t_shell *data)
{
	if (ft_strcmp(ev->var, "?") == 0)
	{
		ev->value = ft_itoa(data->last_status);
		if (!ev->value)
		{
			free(ev->var);
			ev->var = NULL;
		}
	}
	else
		ev->value = is_in_env(ev->env, ev->var);
}

static void	process_variable(t_token *token, t_expand_var *ev, t_shell *data)
{
	ev->var = extract_variable_name(token->value, ev->i);
	if (!ev->var)
		return ;
	ev->value = NULL;
	ev->var_len = ft_strlen(ev->var);
	handle_last_status(ev, data);
	if (!ev->value)
	{
		free (ev->var);
		ev->var = NULL;
		return ;
	}
	ev->new_str = expand_value(token->value, ev->value, ev->var, ev->i);
	free (ev->var);
	ev->var = NULL;
	free (ev->value);
	ev->value = NULL;
	if (!ev->new_str)
		return ;
	free (token->value);
	token->value = ev->new_str;
	ev->new_str = NULL;
	ev->i = -1;
}

void	expand_variable(t_token *token, t_shell *data)
{
	t_expand_var	ev;

	init_expand_var(&ev, data);
	while (token)
	{
		if (is_expand(token) == SUCCESS)
		{
			ev.i = 0;
			while (token->value && token->value[ev.i])
			{
				if (token->value[ev.i] == '$' && \
					token->quote[ev.i] != SINGLE_QUOTE)
					process_variable(token, &ev, data);
				ev.i++;
			}
		}
		token = token->next;
	}
}
