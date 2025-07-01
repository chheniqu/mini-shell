/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unisgned_nbr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:15:47 by armarboe          #+#    #+#             */
/*   Updated: 2024/12/05 18:15:48 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unsigned_nbr_len(unsigned int nb)
{
	int	res;

	res = 0;
	if (nb == 0)
		res++;
	while (nb != 0)
	{
		nb /= 10;
		res++;
	}
	return (res);
}

int	ft_put_unsigned_nbr(unsigned int nb)
{
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
	}
	ft_putchar(nb % 10 + '0');
	return (unsigned_nbr_len(nb));
}
