/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:59:44 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/18 19:51:12 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int			ft_isint(char *str)
{
	long	num;
	int		neg;
	int		len;

	neg = 0;
	num = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	len = ft_strlen(str);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		if (neg ? num > 2147483648l : num > 2147483647l)
			return (0);
		str++;
	}
	if (ft_numlen(num) == len)
		return (1);
	return (0);
}