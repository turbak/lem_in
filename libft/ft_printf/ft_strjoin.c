/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:45:01 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:13:35 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	size1;
	size_t	size2;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen_p(s1);
	size2 = ft_strlen_p(s2) + 1;
	if (!(dst = (char *)malloc(sizeof(char) * (size1 + size2))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dst[i + size1] = s2[i];
		i++;
	}
	dst[i + size1] = '\0';
	return (dst);
}
