/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:14:31 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/19 22:14:53 by cauranus         ###   ########.fr       */
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