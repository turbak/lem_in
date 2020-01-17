/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:14:31 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 16:36:44 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	linkdelm(t_links **links, t_links *next)
{
	(*links)->next = (*links)->next->next;
	if (next->s->output > 0)
		next->s->output--;
	if (next->f->input > 0)
		next->f->input--;
	free(next);
}

t_links	*linkdels(t_links **links, t_links *start)
{
	(*links) = (*links)->next;
	if (start->s->output > 0)
		start->s->output--;
	if (start->f->input > 0)
		start->f->input--;
	free(start);
	return (*links);
}

void	roomdelm(t_rooms **rooms, t_rooms *next)
{
	(*rooms)->next = (*rooms)->next->next;
	ft_strdel(&next->name);
	free(next);
}

t_rooms	*roomdels(t_rooms **rooms, t_rooms *start)
{
	(*rooms) = (*rooms)->next;
	ft_strdel(&start->name);
	free(start);
	return (*rooms);
}

void	free_turns(t_turn **turn)
{
	t_turn *head;
	t_turn *buf;

	head = *turn;
	if (free_turns_first(turn))
		return ;
	while ((*turn)->next)
	{
		if (!(*turn)->room->next && *turn == head)
		{
			head = (*turn)->next;
			free(*turn);
			*turn = head;
		}
		else if (!(*turn)->next->room->next)
		{
			buf = (*turn)->next->next;
			free((*turn)->next);
			(*turn)->next = buf;
		}
		else
			(*turn) = (*turn)->next;
	}
	(*turn) = head;
}
