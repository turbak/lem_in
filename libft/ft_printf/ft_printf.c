/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:15 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/07 20:33:22 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int			flag_mngr(va_list va, t_flags print)
{
	if (get_flags(va, print))
		return (0);
	else if (print.type == 'p')
	{
		print.hash = 'A';
		put_16x(put_addr((uintmax_t)va_arg(va, void *), print), print);
	}
	else if (print.type == 'o' || print.type == 'O')
		get_o(va, print);
	else if (print.type == 'x' || print.type == 'X')
	{
		print.hash = (print.type == 'X' && print.hash ? 'B' : print.hash);
		get_x(va, print);
	}
	else if (print.type == 'f')
	{
		if (print.flag == 'L')
			put_int(ft_dtoa(va_arg(va, long double), &print), print);
		else
			put_int(ft_dtoa(va_arg(va, double), &print), print);
	}
	return (0);
}

static void	read_string(const char *format, int i, va_list va)
{
	t_flags print;

	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			print = parce(format, i);
			if (print.error)
				break ;
			flag_mngr(va, print);
			i = print.index + (format[i] ? 1 : 0);
		}
		if (format[i] && format[i] != '%')
		{
			write(1, &format[i], 1);
			i++;
			g_count++;
		}
	}
}

int			ft_printf(const char *format, ...)
{
	int		i;
	va_list va;

	i = 0;
	va_start(va, format);
	g_count = 0;
	if (!format)
		exit(-1);
	read_string(format, i, va);
	va_end(va);
	return (g_count);
}
