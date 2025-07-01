/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarboe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:59:52 by armarboe          #+#    #+#             */
/*   Updated: 2024/12/03 16:59:54 by armarboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	nbr_len(int nb);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_printf(const char *str, ...);
int	ft_putnbr(int nb);
int	ft_put_unsigned_nbr(unsigned int nb);
int	ft_putnbr_hexadecimal(unsigned int nb, char *base);
int	ft_putpointer(void *p);
int	ft_putpercent(void);

#endif