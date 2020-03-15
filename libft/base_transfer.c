/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_transfer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:45:09 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/25 21:36:43 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*base_10_trans(uintmax_t n, int base, t_flags print)
{
	char			*str;
	uintmax_t		i;
	int				len;

	i = n;
	len = 0;
	if (!n)
		return (print.hash || !(print.dot && !print.precision) ? "0" : "");
	while (i != 0)
	{
		i /= base;
		++len;
	}
	i = 0;
	str = ft_strnew(len);
	while (n != 0)
	{
		str[i++] = '0' + n % base;
		n /= base;
	}
	if (print.hash)
		ft_swapfree((void**)&str, ft_strjoin(str, "0"));
	ft_strrev(str);
	return (str);
}

char	*base_16_trans(uintmax_t n, int up, t_flags *print)
{
	char			*str;
	uintmax_t		i;
	uintmax_t		len;

	if (!n)
	{
		print->hash = '\0';
		return ((print->hash && print->precision) ||
		!(print->dot && !print->precision) ? "0" : "");
	}
	i = n;
	len = 0;
	while (i != 0 && ++len)
		i /= 16;
	i = 0;
	str = ft_strnew(len);
	while (n != 0)
	{
		len = n % 16;
		check_len(len, str, &i, up);
		n /= 16;
	}
	ft_strrev(str);
	return (str);
}

char	*put_addr(uintmax_t n, t_flags print)
{
	char			*str;
	uintmax_t		i;
	uintmax_t		len;

	if (!n)
		return (print.precision || !(print.dot && !print.precision) ? "0" : "");
	i = n;
	len = 0;
	while (i != 0)
	{
		i /= 16;
		++len;
	}
	i = 0;
	str = ft_strnew(len);
	while (n != 0)
	{
		len = n % 16;
		check_len(len, str, &i, 0);
		n /= 16;
	}
	ft_strrev(str);
	return (str);
}

void	check_len(uintmax_t len, char *str, uintmax_t *i, int up)
{
	if (len < 10)
		str[(*i)++] = '0' + len;
	else if (len == 10)
		str[(*i)++] = (up ? 'A' : 'a');
	else if (len == 11)
		str[(*i)++] = (up ? 'B' : 'b');
	else if (len == 12)
		str[(*i)++] = (up ? 'C' : 'c');
	else if (len == 13)
		str[(*i)++] = (up ? 'D' : 'd');
	else if (len == 14)
		str[(*i)++] = (up ? 'E' : 'e');
	else if (len == 15)
		str[(*i)++] = (up ? 'F' : 'f');
}
