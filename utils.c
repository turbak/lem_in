/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:10:28 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 16:37:00 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_swap(void **ptr1, void **ptr2)
{
	void *swap;

	swap = *ptr2;
	*ptr2 = *ptr1;
	*ptr1 = swap;
}

void	free_stat(t_lem_in *stat)
{
	int i;

	while (stat->rooms)
		stat->rooms = roomdels(&stat->rooms, stat->rooms);
	while (stat->links)
		stat->links = linkdels(&stat->links, stat->links);
	i = -1;
	while (stat->read[++i])
		ft_strdel(&stat->read[i]);
	free(stat->read);
	stat->read = NULL;
	free(stat);
}

void	free_paths(t_roompath *paths)
{
	t_roompath *buf;

	while (paths)
	{
		buf = paths;
		while (paths->room)
			paths->room = roomdels(&paths->room, paths->room);
		paths = paths->next;
		free(buf);
	}
}

void	dequeue(t_queue **queue, t_queue *start)
{
	(*queue) = (*queue)->next;
	free(start);
}

int		free_turns_first(t_turn **turn)
{
	if (!*turn)
		return (1);
	if (!(*turn)->next)
	{
		if (!(*turn)->room->next)
		{
			free(*turn);
			*turn = NULL;
		}
		return (1);
	}
	return (0);
}
