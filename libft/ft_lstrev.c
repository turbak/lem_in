/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:05:11 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 16:15:58 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrev(t_list *lst)
{
	t_list *list;
	t_list *cur;
	t_list *next;

	cur = lst;
	list = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = list;
		list = cur;
		cur = next;
	}
	lst = list;
}
