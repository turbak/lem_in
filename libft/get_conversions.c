/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conversions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:42:27 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 19:01:22 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_flags(va_list va, t_flags print)
{
	if (print.type == 'd' || print.type == 'i' || print.type == 'D')
		get_ints(va, print);
	else if (print.type == 'u' || print.type == 'U')
		get_unsigned(va, print);
	else if (print.type == 'S' || (print.type == 's' && print.flag == 'l'))
		putstl(va_arg(va, wchar_t	*), print);
	else if (print.type == 's')
		putst((va_arg(va, char *)), print);
	else if (print.type == '%')
		put_int_unsigned("%", print);
	else if (print.type == 'c' && print.flag != 'l')
		put_char((char)va_arg(va, int), print);
	else if (print.type == 'C' || (print.type == 'c' && print.flag == 'l'))
		put_char(va_arg(va, wchar_t), print);
	else
		return (0);
	return (1);
}

void	get_ints(va_list va, t_flags print)
{
	if (print.flag == 'l' || print.type == 'D')
		put_int(ft_itoa_p((intmax_t)va_arg(va, long)), print);
	else if (print.flag == 'L')
		put_int(ft_itoa_p((intmax_t)va_arg(va, long long)), print);
	else if (print.flag == 'h')
		put_int(ft_itoa_p((intmax_t)((short)va_arg(va, int))), print);
	else if (print.flag == 'H')
		put_int(ft_itoa_p((intmax_t)((char)va_arg(va, int))), print);
	else
		put_int(ft_itoa_p((intmax_t)va_arg(va, int)), print);
}

void	get_unsigned(va_list va, t_flags print)
{
	if (print.flag == 'l')
		put_int_unsigned(ft_itoa_unsigned(
		(uintmax_t)((size_t)va_arg(va, long)), print), print);
	else if (print.flag == 'L')
		put_int_unsigned(ft_itoa_unsigned(
		(uintmax_t)((size_t)va_arg(va, long long)), print), print);
	else if (print.flag == 'h')
		put_int_unsigned(ft_itoa_unsigned((
		(unsigned short)va_arg(va, int)), print), print);
	else if (print.flag == 'H')
		put_int_unsigned(ft_itoa_unsigned((uintmax_t)(
		(unsigned char)va_arg(va, int)), print), print);
	else
		put_int_unsigned(ft_itoa_unsigned((
		va_arg(va, unsigned int)), print), print);
}

void	get_o(va_list va, t_flags print)
{
	if (print.flag == 'L')
		put_int_unsigned(base_10_trans(
		(uintmax_t)((size_t)va_arg(va, long long)), 8, print), print);
	else if (print.flag == 'l')
		put_int_unsigned(base_10_trans(
		(uintmax_t)((size_t)va_arg(va, unsigned long)), 8, print), print);
	else if (print.flag == 'h')
		put_int_unsigned(base_10_trans(
		(unsigned short)va_arg(va, int), 8, print), print);
	else if (print.flag == 'H')
		put_int_unsigned(base_10_trans(
		(unsigned char)va_arg(va, int), 8, print), print);
	else
		put_int_unsigned(base_10_trans(
		(va_arg(va, unsigned int)), 8, print), print);
}

void	get_x(va_list va, t_flags print)
{
	if (print.flag == 'l')
		put_16x(base_16_trans((uintmax_t)((size_t)va_arg(va, long)),
		(print.type == 'x' ? 0 : 1), &print), print);
	else if (print.flag == 'L')
		put_16x(base_16_trans((uintmax_t)((size_t)va_arg(va, long long)),
		(print.type == 'x' ? 0 : 1), &print), print);
	else if (print.flag == 'h')
		put_16x(base_16_trans((unsigned short)va_arg(va, int),
		(print.type == 'x' ? 0 : 1), &print), print);
	else if (print.flag == 'H')
		put_16x(base_16_trans((unsigned char)va_arg(va, int),
		(print.type == 'x' ? 0 : 1), &print), print);
	else
		put_16x(base_16_trans(va_arg(va, unsigned int),
		(print.type == 'x' ? 0 : 1), &print), print);
}
