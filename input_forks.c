/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:35 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 16:49:56 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		build_path(t_lem_in *stat)
{
	t_rooms	*rooms;
	int		bfs;

	bfs = 1;
	while (bfs <= stat->bfs)
	{
		rooms = stat->rooms;
		while (rooms)
		{
			if (rooms->bfs == bfs && rooms->input > 1)
				delete_forks(stat, rooms);
			rooms = rooms->next;
		}
		bfs++;
	}
}

t_links		*find_prev_link(t_links *links, t_rooms *rooms)
{
	while (links && links->f != rooms)
		links = links->next;
	return (links);
}

static int	find_length(t_links *link, t_links *start)
{
	t_rooms *room;

	room = link->f;
	while (!room->end)
	{
		if (room->output > 1)
			return (1);
		link = start;
		link = find_next_link(link, room);
		room = link->f;
	}
	return (0);
}

void		delete_forks(t_lem_in *stat, t_rooms *rooms)
{
	t_outpath	*path;
	t_links		*buf;
	int			minlen;

	buf = stat->links;
	path = NULL;
	minlen = __INT_MAX__;
	while ((buf = find_prev_link(buf, rooms)))
	{
		add_path(&path, path_init(find_length(buf, stat->links), buf));
		buf = buf->next;
		if (minlen == path->length)
			path->length++;
		minlen = path->length < minlen ? path->length : minlen;
	}
	free_out_forks(path, &stat->links, minlen);
}
