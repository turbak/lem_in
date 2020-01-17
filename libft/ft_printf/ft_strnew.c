/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 17:33:45 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 15:28:06 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	char *ptr;

	if (size + 1 == 0)
		return (NULL);
	if (!(ptr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ptr[size] = '\0';
	while (size--)
		ptr[size] = '\0';
	return (ptr);
}
