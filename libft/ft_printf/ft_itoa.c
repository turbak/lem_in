/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:41:17 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:01:27 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itoa(char *str, intmax_t nb, size_t i, uintmax_t buf)
{
	buf = (nb > 0 ? nb : -nb);
	if (nb < 0)
	{
		str[0] = '-';
		buf = -nb;
	}
	while (buf > 0)
	{
		str[i] = buf % 10 + '0';
		i--;
		buf /= 10;
	}
}

char		*ft_itoa_p(intmax_t n)
{
	size_t		i;
	uintmax_t	buf;
	char		*str;
	intmax_t	nb;

	nb = (intmax_t)n;
	i = (nb > 0 ? 0 : 1);
	buf = (nb > 0 ? nb : -nb);
	while (buf > 0)
	{
		buf = buf / 10;
		i++;
	}
	if (!(str = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	itoa(str, nb, i, buf);
	return (str);
}
