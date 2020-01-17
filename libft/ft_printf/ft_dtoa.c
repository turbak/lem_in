/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:06:23 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/14 21:45:08 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

long double	round_of(long double nb, int power)
{
	while (power > 0)
	{
		nb *= 0.1;
		power--;
	}
	return (nb);
}

static char	*handle_dot(long double nb, t_flags print)
{
	int		i;
	char	*full;
	int		tmp;

	full = ft_strnew(print.precision + 1);
	full[0] = '.';
	tmp = 0;
	i = 1;
	while (i - 1 < print.precision)
	{
		if ((int)nb == 0)
			full[i] = '0';
		nb = (nb - tmp) * 10;
		tmp = (uintmax_t)nb;
		full[i] = tmp + '0';
		i++;
	}
	full[i] = '\0';
	return (full);
}

static char	*handle_all(t_flags *print, char *dot, long double n)
{
	char *all;
	char *full;

	full = handle_dot(n, *print);
	dot[1] = (dot[0] == '-' && !dot[1] ? '0' : dot[1]);
	all = ft_strjoin((!dot[0] ? "0" : dot), (print->precision == -1
	&& !print->hash ? "" : full));
	print->precision = 0;
	return (all);
}

char		*ft_dtoa(long double n, t_flags *print)
{
	char		dot[20];
	size_t		i;
	long double dig;

	print->precision = (!print->precision && !print->dot ?
	6 : print->precision);
	ft_bzero(dot, 20);
	i = (n < 0 ? 1 : 0);
	dot[0] = (i == 1 ? '-' : '\0');
	n = (n < 0 ? -n : n);
	n += print->precision == -1 ? 0 : round_of(0.5, print->precision);
	dig = 1;
	while ((int)(n /= 10) != 0)
		dig *= 10;
	n *= dig * 10;
	while ((int)dig != 0)
	{
		dot[i++] = (char)(n / dig + '0');
		n -= (int)(n / dig) * dig;
		dig /= 10;
	}
	return (handle_all(print, dot, n));
}
