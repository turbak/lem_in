/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:03:30 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/21 05:25:28 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue 	*init_queue(t_rooms *room)
{
	t_queue *queue;

	if (!room)
		return (NULL);
	queue = malloc(sizeof(t_queue));
	queue->room = room;
	queue->next = NULL;
	return (queue);
}

int	queueadd(t_queue **queue, t_queue *new)
{
	t_queue *buf;

	if (!new)
		return (0);
	if (*queue)
	{
		buf = *queue;
		while (buf->next)
			buf = buf->next;
		buf->next = new;
	}
	else
		*queue = new;
	return (1);
}

void dequeue(t_queue **queue)
{
	t_queue *buf;
	
	if (!*queue)
		return ;
	buf = (*queue)->next;
	free(*queue);
	*queue = NULL;
	*queue = buf;
	
}

t_links	*find_link(t_links **link, char *name)
{
	while (*link)
	{
		if (ft_strequ((*link)->s->name, name) && (*link)->f->bfs == -1)
			return (*link);
		(*link) = (*link)->next;
	}
	return (*link);
}

void	roomdel(t_rooms **room, t_rooms *next)
{
		ft_strdel(&(*room)->name);
		free(*room);
		*room = next;
}

void 	linkdel(t_links **links, t_links *next)
{
	free(*links);
	*links = next;
}
void	remove_useless_rooms_and_links(t_links **link, t_rooms **room)
{
	t_links *links_head;
	t_rooms *rooms_head;
	

	links_head = *link;
	rooms_head = *room;
	while (*link)
	{
		if ((*link)->s->bfs == -1 || (*link)->f->bfs == -1)
			linkdel(link, (*link)->next);
		else
			(*link) = (*link)->next;
	}
	while ((*room))
	{
		if ((*room)->bfs == -1)
			roomdel(room, (*room)->next);
		else
			(*room) = (*room)->next;
	}
	*link = links_head;
	*room = rooms_head;
}

void	bfs(t_lem_in *stat)
{
	t_queue *queue;
	t_links *find;
	t_links *find_head;
	char	*name;
	int		bfs;

	queue = init_queue(stat->start);
	stat->start->bfs = 0;
	find_head = stat->links;
	find = stat->links;
	bfs = 1;
	while (queue && queue->room != stat->end)
	{
		dequeue(&queue);
		while ((find = find_link(&find, stat->start->name)))
		{
			queueadd(&queue, init_queue(find->f));
			queue->room->bfs = bfs;
			find = find->next;
		}
		if (queue)
			stat->start = queue->room;
		find = find_head;
		bfs++;
	}
	remove_useless_rooms_and_links(&stat->links, &stat->rooms);
	while (stat->rooms)
	{
		printf("%s : [%d]\n", stat->rooms->name, stat->rooms->bfs);
		stat->rooms = stat->rooms->next;
	}
	write(1, "\n", 1);
	while (stat->links)
	{
		printf("s : [%s]\nf : [%s]\n", stat->links->s->name, stat->links->f->name);
		stat->links = stat->links->next;
	}
}