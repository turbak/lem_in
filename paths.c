/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:06:35 by cauranus          #+#    #+#             */
/*   Updated: 2019/12/17 15:06:53 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links *find_link_for_path(t_links *link, t_rooms *start)
{
	while (link->s != start && link)
		link = link->next;
	return link;
}

t_path *build_path(t_lem_in *stat)
{
	t_path *path;
	t_links *links;
	t_links *buf;
	t_path *branches;
	t_path *branches_head;

	stat->start = find_start(stat->rooms);
	links  = stat->links;
	while (links)
	{
		path = (t_path *)malloc(sizeof(t_path*));
		path->room = links->s;
		if (links->s->input > 1)
		{
			branches = (t_path *)malloc(sizeof(t_path*));
			branches_head = branches;
			buf = find_link_for_path(buf, links->s);
			if (buf == NULL)
				break;
			else
			{
				branches->room = 
			}
		}
	}
}
