/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:40:11 by armarboe          #+#    #+#             */
/*   Updated: 2024/12/05 15:40:12 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(char c, va_list args)
{
	char	*hexa_low;
	char	*hexa_up;

	hexa_low = "0123456789abcdef";
	hexa_up = "0123456789ABCDEF";
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_put_unsigned_nbr(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_putnbr_hexadecimal(va_arg(args, unsigned int), hexa_low));
	else if (c == 'X')
		return (ft_putnbr_hexadecimal(va_arg(args, unsigned int), hexa_up));
	else if (c == 'p')
		return (ft_putpointer(va_arg(args, void *)));
	else if (c == '%')
		return (ft_putpercent());
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			res += check_format(str[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			res++;
		}
		i++;
	}
	va_end(args);
	return (res);
}
