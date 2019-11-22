/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:03:30 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/22 23:26:39 by cauranus         ###   ########.fr       */
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

void dequeue(t_queue **queue, t_queue *start)
{
	(*queue) = (*queue)->next;
	free(start);
	start = NULL;
	
}

t_links	*find_link(t_links **link, char *name, int bfs)
{
	while (*link)
	{
		if ((ft_strequ((*link)->s->name, name) && ((*link)->f->bfs == -1 ||(*link)->s->bfs == __INT_MAX__)) || (ft_strequ((*link)->f->name, name) && ((*link)->s->bfs == -1 || (*link)->s->bfs == __INT_MAX__)))
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
}

void	bfs(t_lem_in *stat)
{
	t_queue *queue;
	t_links *find;
	t_links *find_head;
	int		bfs;

	queue = init_queue(stat->start);
	stat->start->bfs = 0;
	stat->end->bfs = __INT_MAX__;
	find_head = stat->links;
	find = stat->links;
	while (queue && queue->room != stat->end)
	{
		bfs = queue->room->bfs + 1;
		dequeue(&queue, queue);
		while ((find = find_link(&find, stat->start->name, bfs)))
		{
			queueadd(&queue, init_queue(ft_strequ(stat->start->name, find->f->name) ? find->s :  find->f));
			find = find->next;
		}
		if (queue)
			stat->start = queue->room;
		find = find_head;
	}
	
	remove_useless_rooms_and_links(stat);
	//while (stat->rooms)
	//{
	//	printf("%s : [%d]\n", stat->rooms->name, stat->rooms->bfs);
	//	stat->rooms = stat->rooms->next;
	//}
	//write(1, "\n", 1);
	//while (stat->links)
	//{
	//	//printf("s {name %s} : [%d]	f {name %s} : [%d]\n", //stat->links->s->name,stat->links->s->bfs, stat->links->f->name, //stat->links->f->bfs);
	//	printf("{%s}_output links : [%d], {%s}_input_links : [%d], bfs : [%d]\n//{%s}_output links : [%d], {%s}_input_links : [%d],  bfs : [%d]\n",  //stat->links->s->name, stat->links->s->output, stat->links->s->name, //stat->links->s->input, stat->links->s->bfs, stat->links->f->name, //stat->links->f->output, stat->links->f->name, stat->links->s->input, //stat->links->f->bfs);
	//	stat->links = stat->links->next;
	//}
	while (stat->rooms)
	{
		if (stat->rooms->start)
			printf("start ");
		if (stat->rooms->end)
			printf("end ");
		printf("name{%s}, input [%d], output [%d], bfs [%d]\n",  stat->rooms->name, stat->rooms->input, stat->rooms->output, stat->rooms->bfs);
		stat->rooms = stat->rooms->next;
	}
}