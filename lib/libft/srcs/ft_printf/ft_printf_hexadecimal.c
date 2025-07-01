/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexadecimal_x.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:07:06 by armarboe          #+#    #+#             */
/*   Updated: 2024/12/05 19:07:10 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unisgned_nbr_len_hexa(unsigned int nb)
{
	int	res;

	res = 0;
	if (nb == 0)
		res++;
	while (nb != 0)
	{
		nb /= 16;
		res++;
	}
	return (res);
}

int	ft_putnbr_hexadecimal(unsigned int nb, char *base)
{
	if (nb >= 16)
	{
		ft_putnbr_hexadecimal(nb / 16, base);
	}
	(ft_putchar(base[nb % 16]));
	return (unisgned_nbr_len_hexa(nb));
}
