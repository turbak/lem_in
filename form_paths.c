/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:07:42 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 17:52:48 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		roomaddend(t_rooms **rooms, t_rooms *new)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	if (!(*rooms))
	{
		*rooms = new;
		return ;
	}
	if (!(*rooms)->next)
	{
		(*rooms)->next = new;
		return ;
	}
	while ((*rooms)->next)
		*rooms = (*rooms)->next;
	(*rooms)->next = new;
	(*rooms) = rooms_head;
}

t_rooms		*find_next_path(t_links *link, t_rooms *current, t_rooms **list)
{
	while (link && link->s != current)
		link = link->next;
	if (link->f->end)
	{
		roomaddend(list, roomcpy(link->s));
		return (NULL);
	}
	else
	{
		roomaddend(list, roomcpy(link->s));
		return (link->f);
	}
}

t_roompath	*form_path(t_links *link, t_lem_in *stat)
{
	t_rooms		*current;
	t_links		*links_head;
	t_roompath	*roompath;

	roompath = (t_roompath*)malloc(sizeof(t_roompath));
	roompath->next = NULL;
	roompath->room = NULL;
	roompath->turns = NULL;
	roomaddend(&roompath->room, roomcpy(link->s));
	roompath->length = 0;
	current = link->f;
	links_head = stat->links;
	while ((current = find_next_path(links_head, current, &roompath->room)))
		roompath->length++;
	roomaddend(&roompath->room, roomcpy(stat->end));
	roompath->length++;
	return (roompath);
}

t_roompath	*roompathadd(t_roompath **roompath, t_roompath *new)
{
	t_roompath *head;

	head = *roompath;
	if (!*roompath)
	{
		*roompath = new;
		return (*roompath);
	}
	if (!(*roompath)->next || (*roompath)->length > new->length)
	{
		if ((*roompath)->length < new->length)
		{
			(*roompath)->next = new;
			new = *roompath;
		}
		else
			new->next = *roompath;
		return (new);
	}
	while ((*roompath)->next && (*roompath)->next->length < new->length)
		*roompath = (*roompath)->next;
	new->next = (*roompath)->next;
	(*roompath)->next = new;
	return (head);
}

void		form_and_sort_paths(t_lem_in *stat)
{
	t_rooms		*begin;
	t_links		*buf;
	t_roompath	*paths;
	int			i;

	begin = find_start(stat->rooms);
	paths = NULL;
	buf = stat->links;
	while ((buf = find_next_link(buf, begin)))
	{
		paths = roompathadd(&paths, form_path(buf, stat));
		buf = buf->next;
	}
	i = 0;
	while (stat->read[i])
		ft_printf("%s\n", stat->read[i++]);
	ft_printf("\n");
	send_ants(paths, stat);
}
