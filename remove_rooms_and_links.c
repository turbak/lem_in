/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_rooms_and_links.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:29:33 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/23 17:51:07 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*dead_rooms(t_rooms **rooms)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	while ((*rooms)->next)
	{
		if (!(*rooms)->output && !(*rooms)->end)
		{
			if (rooms_head == *rooms)
				rooms_head = roomdels(rooms, *rooms);
			else
				*rooms = roomdels(rooms, *rooms);
		}
		else if (!(*rooms)->next->output && !(*rooms)->next->end)
			roomdelm(rooms, (*rooms)->next);
		else
			(*rooms) = (*rooms)->next;
	}
	return (rooms_head);
}

t_links	*dead_links(t_links **links)
{
	t_links	*links_head;

	links_head = *links;
	while ((*links)->next)
	{
		if (!(*links)->s || !(*links)->f)
		{
			if (links_head == *links)
				links_head = linkdels(links, *links);
			else
				*links = linkdels(links, *links);
		}
		else if (!(*links)->next->s || !(*links)->next->f)
			linkdelm(links, (*links)->next);
		else
			(*links) = (*links)->next;
	}
	return (links_head);
}