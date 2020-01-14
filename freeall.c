/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:14:31 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/14 20:59:31 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
* функция очистки(надо избавиться от легаси)
*/
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
		roombuf = NULL;
	}
	i = -1;
	while(stat->read[++i])
		ft_strdel(&stat->read[i]);
	free(stat->read);
	stat->read = NULL;
	free(stat);
}
/*
* удаляет линка из середины списка
*/
void	linkdelm(t_links **links, t_links *next)
{
	(*links)->next = (*links)->next->next;
	if (next->s->output > 0)
		next->s->output--;
	if (next->f->input > 0)
		next->f->input--;
	free(next);
}
/*
* удаляет линка из старта списка, возвращает указатель на новую голову для того, чтобы переназначить голову
*/
t_links	 *linkdels(t_links **links, t_links *start)
{
	(*links) = (*links)->next;
	if (start->s->output > 0)
		start->s->output--;
	if (start->f->input > 0)
		start->f->input--;
	free(start);
	return (*links);
}
/*
* удаляет комнаты из середины списка
*/
void	roomdelm(t_rooms **rooms, t_rooms *next)
{
	(*rooms)->next = (*rooms)->next->next;
	ft_strdel(&next->name);
	free(next);
}
/*
* удаляет комнаты из старта списка, возвращает указатель на новую голову для того, чтобы переназначить голову
*/
t_rooms	*roomdels(t_rooms **rooms, t_rooms *start)
{
	(*rooms) = (*rooms)->next;
	ft_strdel(&start->name);
	free(start);
	start = NULL;
	return (*rooms);
}
/*
* удаление элемента из очереди
*/

void dequeue(t_queue **queue, t_queue *start)
{
	(*queue) = (*queue)->next;
	free(start);
	start = NULL;
}

void free_turns(t_turn **turn)
{
	t_turn *head;
	t_turn *buf;

	head = *turn;
	if (!*turn)
		return;
	if (!(*turn)->next)
	{
		if (!(*turn)->room->next && *turn == head)
		{
			free(*turn);
			*turn = NULL;
		}
		return;
	}
	while ((*turn)->next)
	{
		if (!(*turn)->room->next && *turn == head)
		{
			head = (*turn)->next;
			free(turn);
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