/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 00:17:50 by cauranus          #+#    #+#             */
/*   Updated: 2019/12/03 17:24:20 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
* файл с валидацией(в принципе, все это можно перенести в цикл чтения(в будущем))
*/
static int	validate_links(t_links *links)
{
	while (links)
	{
		if  (ft_strequ(links->s->name, links->f->name))
				return (0);
		links = links->next;
	}
	return (1);
}

static int	validate_rooms(t_rooms *rooms)
{
	t_rooms *tmp;
	
	if (!find_end(rooms) || !find_start(rooms))
		return (0);
	while (rooms)
	{
		tmp = rooms->next;
		while (tmp)
		{
			if (ft_strequ(rooms->name, tmp->name) || (rooms->x == tmp->x && rooms->y == tmp->y))
				return (0);
			tmp = tmp->next;
		}
		rooms = rooms->next;
	}
	return (1);
}

int validate(t_lem_in *stat)
{
	return (validate_links(stat->links) && !validate_rooms(stat->rooms));
}
