/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_rooms_and_links.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:29:33 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/14 14:04:56 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*dead_rooms(t_rooms **rooms)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	while ((*rooms)->next)
	{
		if (!(*rooms)->output && !(*rooms)->end && rooms_head == *rooms)
			rooms_head = roomdels(rooms, *rooms);
		else if (!(*rooms)->next->output && !(*rooms)->next->end)
			roomdelm(rooms, (*rooms)->next);
		else
			(*rooms) = (*rooms)->next;
	}
	return (rooms_head);
}

t_links		*f_dowhilelinks(t_links **links, t_links *links_head, int *n)
{
	while ((*links)->next)
	{
		if ((((*links)->f->output == 0 && !(*links)->f->end) ||
		((*links)->s->input == 0 &&
		!(*links)->s->start)) && links_head == *links)
		{
			(*n)++;
			links_head = linkdels(links, *links);
		}
		else if (((*links)->next->f->output == 0 && !(*links)->next->f->end) ||
		((*links)->next->s->input == 0 && !(*links)->next->s->start))
		{
			(*n)++;
			linkdelm(links, (*links)->next);
		}
		else
			(*links) = (*links)->next;
	}
	return (links_head);
}

t_links		*dead_links(t_links **links)
{
	t_links		*links_head;
	int			n;

	n = 123;
	while (n > 0)
	{
		n = 0;
		links_head = *links;
		*links = f_dowhilelinks(links, links_head, &n);
	}
	return (links_head);
}
