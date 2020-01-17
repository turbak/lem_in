/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:39:38 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 17:21:22 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links		*find_next_link(t_links *link, t_rooms *room)
{
	while (link && link->s != room)
		link = link->next;
	return (link);
}

static int	find_length(t_links *link, t_links *start)
{
	int		i;
	t_rooms	*room;

	i = 0;
	room = link->f;
	while (!room->end)
	{
		link = start;
		link = find_next_link(link, room);
		room = link->f;
		i++;
	}
	return (i);
}

void		free_out_forks(t_outpath *path, t_links **link, int minlen)
{
	t_links		*links_head;
	t_outpath	*buf;

	while (path)
	{
		links_head = *link;
		if (path->length != minlen)
		{
			while ((*link)->next && !(*link == path->link
			|| (*link)->next == path->link))
				(*link) = (*link)->next;
			if (*link == path->link && links_head == *link)
				links_head = linkdels(link, *link);
			else if ((*link)->next == path->link)
				linkdelm(link, (*link)->next);
		}
		buf = path;
		path = path->next;
		free(buf);
		*link = links_head;
	}
}

static void	delete_out_paths(t_rooms *begin, t_lem_in *stat)
{
	t_outpath	*path;
	t_links		*buf;
	int			minlen;

	buf = stat->links;
	path = NULL;
	minlen = __INT_MAX__;
	while ((buf = find_next_link(buf, begin)))
	{
		add_path(&path, path_init(find_length(buf, stat->links), buf));
		buf = buf->next;
		if (minlen == path->length)
			path->length++;
		minlen = path->length < minlen ? path->length : minlen;
	}
	free_out_forks(path, &stat->links, minlen);
}

void		remove_output_forks(t_lem_in *stat)
{
	t_links	*begin;
	int		flag;

	begin = stat->links;
	while (stat->bfs != 0)
	{
		while (begin)
		{
			flag = 0;
			if (begin->s->output > 1 && begin->s->bfs == stat->bfs)
			{
				delete_out_paths(begin->s, stat);
				begin = stat->links;
				flag = 1;
			}
			if (!flag)
				begin = begin->next;
		}
		begin = stat->links;
		stat->bfs--;
	}
}
