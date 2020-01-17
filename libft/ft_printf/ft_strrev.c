/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:07:42 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:13:52 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev_p(char *s)
{
	size_t	j;
	size_t	i;
	char	rev;

	i = ft_strlen_p(s);
	j = 0;
	--i;
	while (i > j)
	{
		rev = s[j];
		s[j] = s[i];
		s[i] = rev;
		j++;
		i--;
	}
	return (s);
}
