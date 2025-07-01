/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:58:40 by armarboe          #+#    #+#             */
/*   Updated: 2024/12/05 16:58:42 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	nbr_len(int nb)
{
	int	res;

	res = 0;
	if (nb < 0)
	{
		res++;
		nb = -nb;
	}
	if (nb == 0)
		res++;
	while (nb != 0)
	{
		nb /= 10;
		res++;
	}
	return (res);
}

int	ft_putnbr(int nb)
{
	int	nbr;

	nbr = nb;
	if (nbr == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		write(1, "147483648", 9);
		return (11);
	}
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
	}
	ft_putchar(nbr % 10 + '0');
	return (nbr_len(nb));
}
