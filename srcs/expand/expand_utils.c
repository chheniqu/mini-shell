/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:38:31 by chheniqu          #+#    #+#             */
/*   Updated: 2025/06/24 11:51:21 by chheniqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

static void	init_expand_struct(t_expand *expand, int dollar_pos, char *str)
{
	expand->i = 0;
	expand->j = 0;
	expand->k = dollar_pos;
	expand->new_str = str;
}

static size_t	ft_new_size(char *str, char *var_name, char *to_remplace)
{
	size_t	og_len;
	size_t	var_len;
	size_t	remplace_len;
	size_t	new_size;

	og_len = ft_strlen(str);
	var_len = ft_strlen(var_name) + 1;
	remplace_len = ft_strlen(to_remplace);
	new_size = og_len - var_len + remplace_len + 1;
	return (new_size);
}

static void	ft_new_str(char *str, char *to_remplace, char *var_name, \
	t_expand *expand)
{
	while (expand->i < expand->k)
		expand->new_str[expand->j++] = str[expand->i++];
	while (*to_remplace)
		expand->new_str[expand->j++] = *to_remplace++;
	expand->i += ft_strlen(var_name) + 1;
	while (str[expand->i])
		expand->new_str[expand->j++] = str[expand->i++];
	expand->new_str[expand->j] = '\0';
}

char	*expand_value(char *str, char *to_remplace, char *var_name, int dollar)
{
	size_t		new_size;
	char		*new_str;
	t_expand	expand;

	if (!str || !to_remplace || !var_name)
		return (NULL);
	new_size = ft_new_size(str, var_name, to_remplace);
	if (new_size <= 0)
		return (NULL);
	new_str = malloc(new_size);
	if (!new_str)
		return (NULL);
	init_expand_struct(&expand, dollar, new_str);
	ft_new_str(str, to_remplace, var_name, &expand);
	return (new_str);
}
