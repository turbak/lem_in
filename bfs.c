/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:03:30 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/13 19:48:44 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
* создание элемента очереди
*/
t_queue 	*init_queue(t_rooms *room)
{
	t_queue *queue;

	if (!room)
		return (NULL);
	queue = (t_queue *)malloc(sizeof(t_queue));
	queue->room = room;
	queue->next = NULL;
	return (queue);
}
/*
* добавление элемента в очередь
*/
int	enqueue(t_queue **queue, t_queue *new)
{
	t_queue *buf;

	if (!new)
		return (0);
	if (*queue)
	{
		buf = *queue;
		while (buf->next)
			buf = buf->next;
		buf->next = new;
	}
	else
		*queue = new;
	return (1);
}

/*
* нахождение нужной ссылки(работает только для поиска в ширину, для всего
*  остального надо написать свою по аналогии)
*/

t_links	*find_link(t_links **link, char *name, int bfs)
{
	while (*link)
	{
		if ((ft_strequ((*link)->s->name, name) && ((*link)->f->bfs == -1 ||(*link)->s->bfs == __INT_MAX__)) || (ft_strequ((*link)->f->name, name) && ((*link)->s->bfs == -1 || (*link)->s->bfs == __INT_MAX__)))
		{
			if ((ft_strequ((*link)->f->name, name) && (*link)->s->bfs == -1))
				((*link)->s->bfs = bfs);
			else if ((*link)->f->bfs == -1)
				(*link)->f->bfs = bfs;
			return (*link);
		}
		(*link) = (*link)->next;
	}
	return (*link);
}
/*
* удаляет комнаты с нулевым индексом бфс
*/
t_rooms *remove_rooms(t_rooms **rooms)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	while ((*rooms)->next)
	{
		if ((*rooms)->bfs == -1 && rooms_head == *rooms)
			rooms_head = roomdels(rooms, *rooms);
		else if ((*rooms)->next->bfs == -1)
			roomdelm(rooms, (*rooms)->next);
		else
			*rooms = (*rooms)->next;
	}
	return (rooms_head);
}
/*
* удаляет пути с нулевым индексом бфс и сортирует линки, делая их однонаправленными
*/
t_links *remove_links(t_links **links)
{
	t_links *links_head;

	links_head = *links;
	while ((*links)->next)
	{
		if (((*links)->s->bfs == -1 || (*links)->f->bfs == -1 || (*links)->s->bfs == (*links)->f->bfs) && links_head == *links)
			links_head = linkdels(links, *links);
		else if (((*links)->next->s->bfs == -1 || (*links)->next->f->bfs == -1 || (*links)->next->s->bfs == (*links)->next->f->bfs))
			linkdelm(links, (*links)->next);
		else
		{
			if ((*links)->s->bfs > (*links)->f->bfs)
				ft_swap((void**)&(*links)->s, (void**)&(*links)->f);
			if ((*links)->next->s->bfs > (*links)->next->f->bfs)
				ft_swap((void**)&(*links)->next->s, (void**)&(*links)->next->f);
			*links = (*links)->next;
		}
	}
	return (links_head);
}
/*
* удаляет комнаты и пути с нулевым индексом бфс, а так же тупики, считает количество входных и выходных путей
*/
void	remove_useless_rooms_and_links(t_lem_in *stat)
{
	t_links *l_head;

	stat->links = remove_links(&stat->links);
	stat->rooms = remove_rooms(&stat->rooms);
	l_head = stat->links;
	while (l_head)
	{
			l_head->s->output++;
			l_head->f->input++;
			l_head = l_head->next;
	}
	/*
	 * Утечка памяти
	 */
	stat->links = dead_links(&stat->links);
	stat->rooms = dead_rooms(&stat->rooms);
}
/*
* поиск в ширину, и тонна закоменченных принтфов
*/
void	bfs(t_lem_in *stat)
{
	t_queue *queue;
	t_links *find;
	t_links *find_head;
	t_roompath *paths;
	int		bfs;

	queue = init_queue(stat->start);
	stat->start->bfs = 0;
	stat->end->bfs = __INT_MAX__;
	find_head = stat->links;
	find = stat->links;
	while (queue && queue->room != stat->end)
	{
		bfs = queue->room->bfs + 1;
		dequeue(&queue, queue);
		while ((find = find_link(&find, stat->start->name, bfs)))
		{
			enqueue(&queue, init_queue(ft_strequ(stat->start->name, find->f->name) ? find->s :  find->f));
			find = find->next;
		}
		if (queue)
			stat->start = queue->room;
		find = find_head;
	}
	stat->bfs = bfs--;
	remove_useless_rooms_and_links(stat);
	//while (stat->rooms)
	//{
	//	printf("%s : [%d]\n", stat->rooms->name, stat->rooms->bfs);
	//	stat->rooms = stat->rooms->next;
	//}
	//write(1, "\n", 1);
	//while (stat->links)
	//{
	//	//printf("s {name %s} : [%d]	f {name %s} : [%d]\n", //stat->links->s->name,stat->links->s->bfs, stat->links->f->name, //stat->links->f->bfs);
	//	printf("{%s}_output links : [%d], {%s}_input_links : [%d], bfs : [%d]\n//{%s}_output links : [%d], {%s}_input_links : [%d],  bfs : [%d]\n",  //stat->links->s->name, stat->links->s->output, stat->links->s->name, //stat->links->s->input, stat->links->s->bfs, stat->links->f->name, //stat->links->f->output, stat->links->f->name, stat->links->s->input, //stat->links->f->bfs);
	//	stat->links = stat->links->next;
	//}
	build_path(stat);
	stat->links = dead_links(&stat->links);
	stat->rooms = dead_rooms(&stat->rooms);
	remove_output_forks(stat);
	stat->links = dead_links(&stat->links);
	stat->rooms = dead_rooms(&stat->rooms);
	paths = form_and_sort_paths(stat);
	//while (paths)
	//{
	//	printf("path_length [%d]\n", paths->length);
	//	while (paths->room)
	//	{
	//		printf("[%s]%s", paths->room->name, !paths->room->next ? "\n" : "->");
	//		paths->room = paths->room->next;
	//	}
	//	paths = paths->next;
	//}
	//ft_putchar('\n');
    //    while (stat->links)
    //    {
    //      printf("s {name %s} : [%d]	f {name %s} : [%d]\n", stat->links->s->name,stat->links->s->input, stat->links->f->name, stat->links->f->input);
    //      //printf("{%s}_output links : [%d], {%s}_input_links : [%d], bfs : [%d]\n{%s}_output links : [%d], {%s}_input_links : [%d],  bfs : [%d]\n",  stat->links->s->name, stat->links->s->output, stat->links->s->name, stat->links->s->input, stat->links->s->bfs, stat->links->f->name, stat->links->f->output, stat->links->f->name, stat->links->s->input, stat->links->f->bfs);
    //      stat->links = stat->links->next;
    //    }
	/*while (stat->rooms)
	{
		if (stat->rooms->start)
			printf("start ");
		if (stat->rooms->end)
			printf("end ");
		//printf("%s\n", stat->rooms->name);
		printf("name{%s}, input [%d], output [%d], bfs [%d]\n",  stat->rooms->name, stat->rooms->input, stat->rooms->output, stat->rooms->bfs);
		stat->rooms = stat->rooms->next;*/
	//}
}