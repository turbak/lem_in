/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:53:24 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/19 22:17:13 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*find_start(t_rooms *rooms)
{
	while (rooms && !rooms->start)
		rooms = rooms->next;
	return (rooms);
}

t_rooms *find_end(t_rooms *rooms)
{
	while (rooms && !rooms->end)
		rooms = rooms->next;
	return (rooms);
}

int get_max(t_rooms *rooms, char pos)
{
	t_rooms *max;
	
	max = rooms;
	while (rooms)
	{
		if (pos == 'x' ? rooms->x > max->x : rooms->y > max->y)
			max = rooms;
		rooms = rooms->next;
	}
	return (pos == 'x' ? max->x : max->y);
}

t_rooms *find_room(t_rooms *rooms, char *name)
{
	while (rooms && !ft_strequ(rooms->name, name))
		rooms = rooms->next;
	return (rooms);
}

void	fill_rooms(t_rooms *rooms, t_links *links)
{
	t_links *head;

	head = links;
	while (links)
	{
		links->s = find_room(rooms, links->start);
		links->f = find_room(rooms, links->link);
		links = links->next;
	}
	links = head;
}

void		id_matrix(t_lem_in **stat)
{
	int i;
	int j;
	int index;

	(*stat)->start = find_start((*stat)->links);
	(*stat)->end = find_end((*stat)->links);
	fill_rooms((*stat)->rooms, (*stat)->links);
	while ((*stat)->links)
	{
		printf("start : %s\n", (*stat)->links->start);
		printf("link : %s\n", (*stat)->links->link);
		printf("s : [%s]\n", (*stat)->links->s->name);
		printf("f : {%s}\n", (*stat)->links->f->name);
		(*stat)->links = (*stat)->links->next;
	}
}