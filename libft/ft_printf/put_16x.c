/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_16x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:39:31 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:13:57 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_16x(char *str, t_flags print)
{
	int len;
	int i;

	i = 0;
	g_count += (print.hash ? 2 : 0);
	len = ft_strlen_p(str) + (print.hash ? 2 : 0);
	if (print.precision || print.dot || print.minus)
		print.zero = '\0';
	put_16x_minus(str, &print, i, len);
	if (!print.minus)
	{
		if ((print.precision > 0 || print.width > 0) &&
		print.zero && print.hash)
		{
			write(1, (print.hash && print.type != 'X' ? "0x" : "0X"), 2);
			print.hash = '\0';
			len -= 2;
		}
		put_16x_plus(str, print, i, len);
	}
	if (!(*str == '0' && !str[1]) && *str)
		free(str);
}

void	put_16x_plus(char *str, t_flags print, int i, int len)
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
	if (print.hash)
		write(1, (print.hash == 'A' && print.type != 'X' ? "0x" : "0X"), 2);
	while (print.precision > 0)
	{
		write(1, "0", 1);
		print.precision--;
		g_count++;
	}
	write(1, &str[i], len - (print.hash ? 2 : 0));
	g_count += len - (print.hash ? 2 : 0);
}

void	put_16x_minus(char *str, t_flags *print, int i, int len)
{
	print->precision += (print->hash ? 2 : 0);
	print->width -= (print->precision > len ? print->precision : len);
	print->precision -= len - (str[i] == '-' ? 1 : 0);
	if (print->minus)
	{
		write(1, (print->hash == 'A' && print->type != 'X'
		? "0x" : "0X"), print->hash ? 2 : 0);
		while (print->precision > 0)
		{
			write(1, "0", 1);
			print->precision--;
			g_count++;
		}
		write(1, &str[i], len - (print->hash ? 2 : 0));
		g_count += len - (print->hash ? 2 : 0);
		while (print->width > 0)
		{
			write(1, " ", 1);
			print->width--;
			g_count++;
		}
	}
}
