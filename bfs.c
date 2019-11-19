/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:03:30 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/19 19:11:17 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue 	*init_queue(t_rooms *room)
{
	t_queue *queue;

	queue = malloc(sizeof(t_queue));
	queue->room = room;
	queue->next = NULL;
	return (queue);
}

void	queueadd(t_queue **queue, t_queue *new)
{
	t_queue *buf;

	buf = *queue;
	while (buf->next)
		buf = buf->next;
	buf->next = new;
}

t_queue	*bfs(t_lem_in *stat)
{
	int	i;
	int j;
	t_queue *queue;

	
}