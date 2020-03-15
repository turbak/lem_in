/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:32 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/28 15:22:28 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_int(char *str, t_flags print)
{
	int len;
	int i;

	if (!print.precision && print.dot && !ft_strcmp("0", str) &&
	print.type != 'f')
	{
		free(str);
		str = "";
	}
	i = 0;
	g_count += (print.space || print.plus || str[i] == '-' ? 1 : 0);
	len = ft_strlen(str) - (*str == '-' ? 1 : 0);
	print.zero = (print.precision || print.minus ? '\0' : print.zero);
	print.width -= (print.precision > len ? print.precision : len);
	print.width -= ((print.plus || str[i] == '-') ? 1 : 0);
	print.precision -= len;
	if (print.space && str[i] != '-' && !print.plus)
	{
		write(1, " ", 1);
		print.width--;
	}
	(print.minus ? put_int_minus(str, print, len, i)
	: put_int_plus(str, print, len, i));
	if (*str)
		free(str);
}

void	put_int_minus(char *str, t_flags print, int len, int i)
{
	if (str[i] == '-')
	{
		write(1, "-", 1);
		i++;
	}
	if (print.plus && *str != '-')
		write(1, "+", 1);
	while (print.precision > 0)
	{
		write(1, "0", 1);
		print.precision--;
		g_count++;
	}
	write(1, &str[i], len);
	g_count += len;
	while (print.width > 0)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
}

void	put_int_plus(char *str, t_flags print, int len, int i)
{
	if ((str[i] == '-' || print.plus) && (print.width <= 0 || print.zero))
	{
		print.plus = '\0';
		write(1, (str[i] == '-' ? "-" : "+"), 1);
		i += (str[i] == '-' ? 1 : 0);
	}
	if ((print.plus || str[i] == '-') && (print.precision <= 0
	&& print.width <= 0))
	{
		write(1, (str[i] == '-' ? "-" : "+"), 1);
		i += (str[i] == '-' ? 1 : 0);
		print.plus = '\0';
	}
	put_int_plus2(str, print, &i);
	write(1, &str[i], len);
	g_count += len;
}

void	put_int_plus2(char *str, t_flags print, int *i)
{
	while ((print.width > 0 || print.precision > 0) && print.zero)
	{
		write(1, "0", 1);
		g_count++;
		print.width--;
		print.precision--;
	}
	while (print.width > 0 && !print.zero)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
	if (print.plus || str[*i] == '-')
	{
		write(1, (str[*i] == '-' ? "-" : "+"), 1);
		*i += (str[*i] == '-' ? 1 : 0);
	}
	while (print.precision > 0)
	{
		write(1, "0", 1);
		g_count++;
		print.precision--;
	}
}
