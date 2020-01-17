/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:03:30 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 17:27:41 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links	*find_link(t_links **link, char *name, int bfs)
{
	while (*link)
	{
		if ((ft_strequ((*link)->s->name, name) && ((*link)->f->bfs == -1
		|| (*link)->s->bfs == __INT_MAX__)) ||
		(ft_strequ((*link)->f->name, name)
		&& ((*link)->s->bfs == -1 || (*link)->s->bfs == __INT_MAX__)))
		{
			if ((ft_strequ((*link)->f->name, name) && (*link)->s->bfs == -1))
				((*link)->s->bfs = bfs);
			else if ((*link)->f->bfs == -1)
				(*link)->f->bfs = bfs;
			return (*link);
		}
		(*link) = (*link)->next;
	}
	return (*link);
}

t_rooms	*remove_rooms(t_rooms **rooms)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	while ((*rooms)->next)
	{
		if ((*rooms)->bfs == -1 && rooms_head == *rooms)
			rooms_head = roomdels(rooms, *rooms);
		else if ((*rooms)->next->bfs == -1)
			roomdelm(rooms, (*rooms)->next);
		else
			*rooms = (*rooms)->next;
	}
	return (rooms_head);
}

t_links	*remove_links(t_links **links)
{
	t_links *links_head;

	links_head = *links;
	while ((*links)->next)
	{
		if (((*links)->s->bfs == -1 || (*links)->f->bfs == -1 ||
		(*links)->s->bfs == (*links)->f->bfs) && links_head == *links)
			links_head = linkdels(links, *links);
		else if (((*links)->next->s->bfs == -1 || (*links)->next->f->bfs == -1
		|| (*links)->next->s->bfs == (*links)->next->f->bfs))
			linkdelm(links, (*links)->next);
		else
		{
			if ((*links)->s->bfs > (*links)->f->bfs)
				ft_swap((void**)&(*links)->s, (void**)&(*links)->f);
			if ((*links)->next->s->bfs > (*links)->next->f->bfs)
				ft_swap((void**)&(*links)->next->s, (void**)&(*links)->next->f);
			*links = (*links)->next;
		}
	}
	return (links_head);
}

void	remove_useless_rooms_and_links(t_lem_in *stat)
{
	t_links *l_head;

	stat->links = remove_links(&stat->links);
	stat->rooms = remove_rooms(&stat->rooms);
	l_head = stat->links;
	while (l_head)
	{
		l_head->s->output++;
		l_head->f->input++;
		l_head = l_head->next;
	}
	stat->links = dead_links(&stat->links);
	stat->rooms = dead_rooms(&stat->rooms);
}

void	bfs(t_lem_in *stat)
{
	t_queue *queue;
	t_links *find;
	t_links *find_head;

	queue = init_queue(stat->start);
	stat->start->bfs = 0;
	stat->end->bfs = __INT_MAX__;
	find_head = stat->links;
	find = stat->links;
	while (queue)
	{
		stat->bfs = queue->room->bfs + 1;
		dequeue(&queue, queue);
		while ((find = find_link(&find, stat->start->name, stat->bfs)))
		{
			enqueue(&queue, init_queue(ft_strequ(stat->start->name,
			find->f->name) ? find->s : find->f));
			find = find->next;
		}
		if (queue)
			stat->start = queue->room;
		find = find_head;
	}
	remove_output_and_input_forks(stat);
}
