/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 00:17:50 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/19 21:58:43 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	validate_links(t_links *links, t_rooms *rooms)
{
	t_rooms *head;
	int 	counter;
	
	while (links)
	{
		if (!(find_room(rooms, links->start) || find_room(rooms, links->link))
		|| ft_strequ(links->link, links->start))
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
	int i;
	int j;

	i = 0;
	while (stat->read[i])
	{
		if (is_link(stat->read[i]))
		{
			j = i + 1;
			while (stat->read[j])
			{
				if (is_link(stat->read[j]) && ft_strequ(stat->read[i], stat->read[j]))
					return (0);
				j++;
			}
		}
		i++;
	}
	return (validate_links(stat->links, stat->rooms) && validate_rooms(stat->rooms));
}
