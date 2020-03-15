/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:08:47 by cauranus          #+#    #+#             */
/*   Updated: 2020/02/17 18:25:57 by tgarkbit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	charcheck(char c)
{
	return (c != 'i' && c != 'd' && c != 's' && c != 'S'
	&& c != '%' && c != 'c' && c != 'p' && c != 'U' &&
	c != 'o' && c != 'u' && c != 'u' && c != 'x' && c != 'C'
	&& c != 'X' && c != 'f' && c != 'D' && c != 'O');
}

static int	parce_convs(t_flags *print, int i, const char *format)
{
	if ((format[i - 1] == 'l' && format[i - 2] == 'l')
	|| format[i - 1] == 'L')
		print->flag = 'L';
	else if (format[i - 1] == 'l' && format[i - 2] != 'l')
		print->flag = 'l';
	else if (format[i - 1] == 'h' && format[i - 2] == 'h')
		print->flag = 'H';
	else if (format[i - 1] == 'h' && format[i - 2] != 'h')
		print->flag = 'h';
	print->type = format[i];
	print->index = i;
	i -= (print->type == '%' ? 1 : 0);
	while (format[i] != '%' ? format[i] != '%' : 0)
		i--;
	++i;
	return (i);
}

static int	parce_flags(t_flags *print, int i, const char *format)
{
	while (format[i] && !(format[i] > '0' && format[i] <= '9') &&
	format[i] != '.' && charcheck(format[i]))
	{
		if (format[i] == '-')
			print->minus = 'A';
		if (format[i] == '+')
			print->plus = 'A';
		if (format[i] == '0')
			print->zero = 'A';
		if (format[i] == '#')
			print->hash = 'A';
		if (format[i] == ' ')
			print->space = 'A';
		i++;
	}
	print->width = (format[i] >= '0' && format[i] <= '9' ?
	ft_atoi(&format[i]) : 0);
	return (i);
}

t_flags		parce(const char *format, int i)
{
	t_flags	print;

	print = init_print();
	while (charcheck(format[i]))
	{
		if (format[i] == '.')
			print.dot = 'A';
		if (!format[i++])
		{
			print.error = 'A';
			return (print);
		}
	}
	i = parce_convs(&print, i, format);
	i = parce_flags(&print, i, format);
	if (print.dot)
	{
		while (format[i] != '.')
			i++;
		print.precision = (ft_atoi(&format[i + 1]) == 0 && print.type == 'f'
		? -1 : ft_atoi(&format[i + 1]));
		print.precision = print.precision <
			0 ? -print.precision : print.precision;
	}
	return (print);
}
