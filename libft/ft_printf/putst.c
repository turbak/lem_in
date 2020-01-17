/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:48:14 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:14:15 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putstl(wchar_t *str, t_flags print)
{
	int len;
	int i;

	if (print.dot && !print.precision)
		str = L"\0";
	if (!str)
		str = L"(null)";
	len = (ft_strlenw(str) > (size_t)print.precision && print.precision ?
	print.precision : ft_strlenw(str));
	i = 0;
	print.width = (print.minus ? print.width : print.width - len);
	if (print.minus)
		putstl_minus(str, print, i, len);
	else
		putstl_plus(str, print, i, len);
}

void	putst(char *str, t_flags print)
{
	int len;

	if (!print.precision && print.dot)
		str = "";
	if (!str)
		str = "(null)";
	len = (ft_strlen_p(str) > (size_t)print.precision && print.precision ?
	print.precision : ft_strlen_p(str));
	print.width = (print.minus ? print.width : print.width - len);
	if (print.minus)
	{
		write(1, str, len);
		print.width -= len;
		g_count += len;
		while (print.width > 0)
		{
			write(1, " ", 1);
			print.width--;
			g_count++;
		}
	}
	else
		putst_plus(str, print, len);
}

void	putstl_minus(wchar_t *str, t_flags print, int i, int len)
{
	while (i < len)
	{
		ft_unicode((wchar_t)str[i]);
		i++;
		print.width--;
		g_count++;
	}
	while (print.width > 0)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
}

void	putst_plus(char *str, t_flags print, int len)
{
	while (print.width > 0)
	{
		if (print.zero)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		print.width--;
		g_count++;
	}
	write(1, str, len);
	g_count += len;
}

void	putstl_plus(wchar_t *str, t_flags print, int i, int len)
{
	while (print.width > 0)
	{
		if (print.zero)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		print.width--;
		g_count++;
	}
	while (i < len)
	{
		ft_unicode((wchar_t)str[i]);
		i++;
		g_count++;
	}
}
