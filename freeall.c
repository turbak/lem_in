/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:14:31 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/23 18:00:34 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_stat(t_lem_in *stat)
{
	t_rooms *roombuf;
	t_links *linkbuf;
	int i;
	
	while (stat->rooms)
	{
		roombuf = stat->rooms;
		stat->rooms = stat->rooms->next;
		ft_strdel(&roombuf->name);
		roombuf = NULL;
	}

	while (stat->links)
	{
		linkbuf = stat->links;
		stat->links = stat->links->next;
		ft_strdel(&linkbuf->start);
		ft_strdel(&linkbuf->link);
		roombuf = NULL;
	}
	i = -1;
	while(stat->read[++i])
		ft_strdel(&stat->read[i]);
	free(stat->read);
	stat->read = NULL;
	free(stat);
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


void dequeue(t_queue **queue, t_queue *start)
{
	(*queue) = (*queue)->next;
	free(start);
	start = NULL;
}