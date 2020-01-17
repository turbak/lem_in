/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:20:06 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 17:28:31 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*roomcpy(t_rooms *room)
{
	t_rooms *new;

	new = (t_rooms *)malloc(sizeof(t_rooms));
	new->next = NULL;
	new->start = room->start;
	new->end = room->end;
	new->output = room->output;
	new->input = room->input;
	new->ants = room->ants;
	new->bfs = room->bfs;
	new->name = ft_strdup(room->name);
	new->x = room->x;
	new->y = room->y;
	return (new);
}

t_outpath	*path_init(int length, t_links *link)
{
	t_outpath	*outpath;

	outpath = (t_outpath *)malloc(sizeof(t_outpath));
	outpath->next = NULL;
	outpath->link = link;
	outpath->length = length;
	return (outpath);
}

void		add_path(t_outpath **path, t_outpath *new)
{
	new->next = *path;
	*path = new;
}

int			enqueue(t_queue **queue, t_queue *new)
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

t_queue		*init_queue(t_rooms *room)
{
	t_queue *queue;

	if (!room)
		return (NULL);
	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = room;
	queue->next = NULL;
	return (queue);
}
