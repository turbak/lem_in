/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:53:24 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/19 00:11:58 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*find_start(t_rooms *rooms)
{
	while (rooms && !rooms->start)
		rooms = rooms->next;
	return (rooms);
}

t_rooms *find_end(t_rooms *rooms)
{
	while (rooms && !rooms->end)
		rooms = rooms->next;
	return (rooms);
}

int get_max(t_rooms *rooms, char pos)
{
	t_rooms *max;
	
	max = rooms;
	while (rooms)
	{
		if (pos == 'x' ? rooms->x > max->x : rooms->y > max->y)
			max = rooms;
		rooms = rooms->next;
	}
	return (pos == 'x' ? max->x : max->y);
}

int find_room(t_rooms *rooms, char *name, char pos)
{
	while (rooms && !ft_strequ(rooms->name, name))
		rooms = rooms->next;
	return (pos == 'x' ? rooms->x : rooms->y);
}

void	fill_matrix(t_rooms *rooms, t_links *links, int **matrix)
{
	while (links)
	{
		matrix[find_room(rooms, links->start, 'x') - 1][find_room(rooms, links->link, 'y') - 1] = 1;
		links = links->next;
	}
}

int		**id_matrix(t_lem_in **stat)
{
	int i;
	int j;
	int index;
	int	**matrix;

	i = get_max((*stat)->rooms, 'x');
	j = get_max((*stat)->rooms, 'y');
	(*stat)->start = find_start((*stat)->rooms);
	(*stat)->end = find_end((*stat)->rooms);
	matrix = (int **)malloc(sizeof(int *) * i);
	index = 0;
	while (index < i)
	{
		matrix[index] = (int *)malloc(sizeof(int *) * j);
		ft_bzero(matrix[index], j);
		index++;
	}
	fill_matrix((*stat)->rooms, (*stat)->links, matrix);
	int k = 0;
	while (k < i)
	{
		index = 0;
		while (index < j)
		{
			printf("[%d] ", matrix[k][index]);
			index++;
		}
		printf("\n");
		k++;
	}
	printf("\n");
	return (matrix);
}