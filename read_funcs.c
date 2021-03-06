/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:53:49 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 16:39:07 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*room_init(char **str, int com)
{
	int		i;
	t_rooms *room;

	i = -1;
	if (!(room = (t_rooms *)malloc(sizeof(t_rooms))))
		error("Malloc error");
	room->next = NULL;
	room->ants = 0;
	room->name = ft_strdup(str[0]);
	room->end = com == 2 ? 1 : 0;
	room->start = com == 1 ? 1 : 0;
	room->input = 0;
	room->output = 0;
	room->x = ft_atoi(str[1]);
	room->y = ft_atoi(str[2]);
	room->bfs = -1;
	while (str[++i])
		ft_strdel(&str[i]);
	free(str);
	return (room);
}

t_links	*link_init(char **str, t_rooms *rooms)
{
	int		i;
	t_links	*link;

	i = -1;
	if (!(link = (t_links*)malloc(sizeof(t_links))))
		error("Malloc error");
	if (!(link->s = find_room(rooms, str[0])))
		error("Link read error");
	if (!(link->f = find_room(rooms, str[1])))
		error("Link read error");
	link->next = NULL;
	while (str[++i])
		ft_strdel(&str[i]);
	free(str);
	return (link);
}

void	read_stat(t_lem_in *stat)
{
	int i;
	int com;

	i = 0;
	stat->rooms = NULL;
	stat->links = NULL;
	if (!ft_isint(stat->read[i]))
		error("No ants");
	stat->ants = ft_atoi(stat->read[i++]);
	while (stat->read[i])
	{
		if (is_comment(stat->read[i]))
			i++;
		if ((com = command(stat->read[i])))
			i++;
		if (is_room(stat->read[i]))
			roomadd(&stat->rooms,
			room_init(ft_strsplit(stat->read[i], ' '), com));
		else if (is_link(stat->read[i]))
			linkadd(&stat->links,
			link_init(ft_strsplit(stat->read[i], '-'), stat->rooms));
		i++;
	}
	error_mngr(stat);
	bfs(stat);
}

void	roomadd(t_rooms **room, t_rooms *new)
{
	new->next = *room;
	*room = new;
}

void	linkadd(t_links **links, t_links *new)
{
	new->next = *links;
	*links = new;
}
