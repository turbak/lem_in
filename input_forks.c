/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:35 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/14 14:04:38 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
* удачи с созданием путей
*/
void	build_path(t_lem_in *stat)
{
	t_rooms *rooms;
	int bfs;

	bfs = 1;
	while (bfs <= stat->bfs)
    {
		rooms = stat->rooms;
		while (rooms)
		{
			if (rooms->bfs == bfs && rooms->input > 1)
			{
				delete_forks(stat, rooms);
			}
			rooms = rooms->next;
		}
		bfs++;
    }
	bfs = 1;
}

void		delete_forks(t_lem_in *stat, t_rooms *rooms)
{
	t_links *links;
	t_path *buffer; //лист с комнатами, ссылающимися на текущую
	t_path *head;
	t_path *best;

	links = stat->links;
	buffer = malloc(sizeof(t_path*));
	buffer->next = malloc(sizeof(t_path*));
	head = buffer->next;
	while (links)
	{
		if (links->f == rooms)
		{
			buffer = buffer->next;
			buffer->next = malloc(sizeof(t_path*));
			buffer->link = links;
		}
		links = links->next;
	}
	free(buffer->next);
	buffer->next = NULL;
	buffer = head;
	best = buffer;
	while (buffer)
	{
		if (f_checkbestroomever(buffer->link, stat))
		{
			best = buffer;
			break;
		}
		buffer = buffer->next;
	}
	f_delete_all_the_fucking_connections_between_rooms(rooms, best->link, stat);
}

int f_checkbestroomever(t_links *current, t_lem_in *stat)
{
	t_links	*to_start;


	to_start = current;
	while (to_start->s->start != 1)
	{
		if (to_start->s->output > 1)
			return 0;
		else
			to_start = find_previous_link(stat->links, to_start->s, stat);
	}
	return 1;
}

t_links *find_previous_link(t_links *links, t_rooms *rooms, t_lem_in *stat)
{
	while (links && links->f != rooms && !links->f->start)
		links = links->next;
	return (links);
}

void f_delete_all_the_fucking_connections_between_rooms(t_rooms *rooms, t_links *best, t_lem_in *stat)
{
	t_links *link;
	t_links *links_head;

	link = stat->links;
	links_head = link;
	while (link->next)
	{
		if (link->f == rooms && link != best && links_head == link)
			links_head = linkdels(&link, link);
		else if (link->next->f == rooms && link->next != best)
			linkdelm(&link, link->next);
		else
			link = link->next;
	}
	rooms->input = 1;
	stat->links = links_head;
}
