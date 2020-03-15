/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:25:29 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/26 18:03:15 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itoa_uns(char *str, uintmax_t nb, uintmax_t i)
{
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		i--;
		nb /= 10;
	}
}

char		*ft_itoa_unsigned(uintmax_t n, t_flags print)
{
	uintmax_t				i;
	uintmax_t				buf;
	char					*str;
	uintmax_t				nb;

	if (!n)
		return (print.dot && !print.precision ? "" : "0");
	nb = (uintmax_t)n;
	i = 0;
	buf = nb;
	while (buf > 0)
	{
		buf = buf / 10;
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	itoa_uns(str, nb, i);
	return (str);
}

void		put_int_unsigned(char *str, t_flags print)
{
	int len;

	len = ft_strlen(str);
	if (print.precision || print.dot || print.minus)
		print.zero = '\0';
	print.width -= (print.precision > len ? print.precision : len);
	print.precision -= len - (*str == '-' ? 1 : 0);
	if (print.minus)
		put_int_unsigned_minus(str, print, len);
	else
		put_int_unsigned_plus(str, print, len);
	if (!(*str == '0' && !str[1]) && *str && *str != '%')
		free(str);
}

void		put_int_unsigned_minus(char *str, t_flags print, int len)
{
	while (print.precision > 0)
	{
		write(1, "0", 1);
		print.precision--;
		g_count++;
	}
	write(1, str, len);
	g_count += len;
	while (print.width > 0)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
}

void		put_int_unsigned_plus(char *str, t_flags print, int len)
{
	while ((print.width > 0 || print.precision > 0) && print.zero)
	{
		write(1, "0", 1);
		print.width--;
		g_count++;
		print.precision--;
	}
	while (print.width > 0 && !print.zero)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
	while (print.precision > 0)
	{
		write(1, "0", 1);
		print.precision--;
		g_count++;
	}
	write(1, str, len);
	g_count += len;
}
