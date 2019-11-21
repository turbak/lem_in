/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:03:30 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/21 23:57:47 by cauranus         ###   ########.fr       */
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

void	linkdelm(t_links **links, t_links *next)
{
	(*links)->next = (*links)->next->next;
	free(next);
	next = NULL;
}
t_links	 *linkdels(t_links **links, t_links *start)
{
	(*links) = (*links)->next;
	free(start);
	start = NULL;
	return (*links);
}

void	roomdelm(t_rooms **rooms, t_rooms *next)
{
	(*rooms)->next = (*rooms)->next->next;
	ft_strdel(&next->name);
	free(next);
	next = NULL;
}

t_rooms	*roomdels(t_rooms **rooms, t_rooms *start)
{
	(*rooms) = (*rooms)->next;
	ft_strdel(&start->name);
	free(start);
	start = NULL;
	return (*rooms);
}

t_rooms *remove_rooms(t_rooms **rooms)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	while ((*rooms)->next)
	{
		if ((*rooms)->bfs == -1)
		{
			if (rooms_head == *rooms)
				rooms_head = roomdels(rooms, *rooms);
			else
				*rooms = roomdels(rooms, *rooms);
		}
		else if ((*rooms)->next->bfs == -1)
			roomdelm(rooms, (*rooms)->next);
		else
			*rooms = (*rooms)->next;
	}
	return (rooms_head);
}

t_links *remove_links(t_links **links)
{
	t_links *links_head;

	links_head = *links;
	while ((*links)->next)
	{
		if ((*links)->s->bfs == -1 || (*links)->f->bfs == -1 || (*links)->s->bfs == (*links)->f->bfs)
		{
			if (links_head == *links)
				links_head = linkdels(links, *links);
			else
				*links = linkdels(links, *links);
		}
		else if (((*links)->next->s->bfs == -1 || (*links)->next->f->bfs == -1 || (*links)->next->s->bfs == (*links)->next->f->bfs))
			linkdelm(links, (*links)->next);
		else
			*links = (*links)->next;
	}
	return (links_head);
}

void	remove_useless_rooms_and_links(t_lem_in *stat)
{
	stat->links = remove_links(&stat->links);
	stat->rooms = remove_rooms(&stat->rooms);
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
			find->f->output++;
			queue->room->input++;
			queue->room->bfs = bfs;
			find = find->next;
		}
		if (queue)
			stat->start = queue->room;
		find = find_head;
		bfs++;
	}
	remove_useless_rooms_and_links(stat);
	//while (stat->rooms)
	//{
	//	printf("%s : [%d]\n", stat->rooms->name, stat->rooms->bfs);
	//	stat->rooms = stat->rooms->next;
	//}
	//write(1, "\n", 1);
	while (stat->links)
	{
		printf("s : [%d] input : [%d]	output : [%d]	f : [%d]	input : [%d]	output : [%d]\n", stat->links->s->bfs, stat->links->f->bfs, stat->links->s->input, stat->links->s->output, stat->links->f->input, stat->links->f->output);
		stat->links = stat->links->next;
	}
}