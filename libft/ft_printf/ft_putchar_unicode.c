/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_unicode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:06:21 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/25 21:37:53 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unicode(wchar_t c)
{
	char ch[4];

	if (c < 128)
	{
		ch[0] = c;
		write(1, ch, 1);
	}
	else if (c < 2048)
	{
		ch[0] = (c >> 6) + 0xC0;
		ch[1] = (c & 0x3F) + 0x80;
		g_count += 1;
		write(1, ch, 2);
	}
	else
		ft_unicode2(c);
}

void	ft_unicode2(wchar_t c)
{
	char ch[4];

	if (c < 65536)
	{
		ch[0] = (c >> 12) + 0xE0;
		ch[1] = ((c >> 6) & 0x3F) + 0x80;
		ch[2] = (c & 0x3F) + 0x80;
		g_count += 2;
		write(1, ch, 3);
	}
	else if (c < 1114111)
	{
		ch[0] = (c >> 18) + 0xF0;
		ch[1] = ((c >> 12) & 0x3F) + 0x80;
		ch[2] = ((c >> 6) & 0x3F) + 0x80;
		ch[3] = (c & 0x3F) + 0x80;
		g_count += 3;
		write(1, ch, 4);
	}
}
