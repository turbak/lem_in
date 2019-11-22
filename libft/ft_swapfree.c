/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:23:17 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/22 19:47:57 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swapfree(void **ptr, void *ptr2)
{
	void	*temp;

	temp = ptr2;
	free(*ptr);
	*ptr = temp;
}
