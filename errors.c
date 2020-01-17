/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:53:24 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 16:17:59 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*find_start(t_rooms *rooms)
{
	while (rooms && !rooms->start)
		rooms = rooms->next;
	return (rooms);
}

t_rooms	*find_end(t_rooms *rooms)
{
	while (rooms && !rooms->end)
		rooms = rooms->next;
	return (rooms);
}

t_rooms	*find_room(t_rooms *rooms, char *name)
{
	while (rooms && !ft_strequ(rooms->name, name))
		rooms = rooms->next;
	return (rooms);
}

void	error_mngr(t_lem_in *stat)
{
	if (!stat->rooms)
		error("No rooms");
	if (!stat->links)
		error("No links");
	if (!(stat->start = find_start(stat->rooms)))
		error("No start");
	if (!(stat->end = find_end(stat->rooms)))
		error("No end");
}
