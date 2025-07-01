/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <armarboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:45:27 by armarboe          #+#    #+#             */
/*   Updated: 2025/03/21 00:48:05 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * str_base + str[i] - '0';
		if (str[i] >= 'A' && str[i] <= 'Z')
			res = res * str_base + str[i] - 55;
		if (str[i] >= 'a' && str[i] <= 'z')
			res = res * str_base + str[i] - 87;
		i++;
	}
	return (res * sign);
}
