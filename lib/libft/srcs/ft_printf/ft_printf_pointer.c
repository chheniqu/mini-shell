/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:07:16 by armarboe          #+#    #+#             */
/*   Updated: 2024/12/05 19:07:17 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	unsigned_nbr_len_pointer(unsigned long nb)
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

int	ft_putnbr_pointer(unsigned long nb)
{
	if (nb >= 16)
		ft_putnbr_pointer(nb / 16);
	ft_putchar("0123456789abcdef"[nb % 16]);
	return (unsigned_nbr_len_pointer(nb));
}

int	ft_putpointer(void *p)
{
	int				len;
	unsigned long	address;

	if (!p)
	{
		ft_putstr("(nil)");
		return (5);
	}
	address = (unsigned long)p;
	ft_putstr("0x");
	len = ft_putnbr_pointer(address);
	return (2 + len);
}
