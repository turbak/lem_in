#include "lem_in.h"

void turn_move(t_turn *turn, t_rooms *room)
{
	turn->room = room;
}

void turnadd(t_turn **turns, t_rooms *room, int ant_num)
{
	t_turn *new;

	new = (t_turn *)malloc(sizeof(t_turn));
	new->room = room;
	new->ant_num = ant_num;
	new->next = *turns;
	*turns = new;
}

void print_turns(t_roompath *path)
{
	t_turn *turn_head;

	while (path)
	{
		turn_head = path->turns;
		while (path->turns)
		{
			path->turns->room = path->turns->room->next;
			if (path->turns->room)
				printf("L%d-%s ", path->turns->ant_num, path->turns->room->name);
			path->turns = path->turns->next;
		}
		free_turns(&turn_head);
		path->turns = turn_head;
		path = path->next;
	}
}

int count_legths_diffs(t_roompath *paths, t_roompath *current, int ants)
{
	int counter;

	counter = 0;
	while (paths != current)
	{
		counter += current->length - paths->length;
		paths = paths->next;
	}
	if (ants > counter)
		return (1);
	return (0);
}

void    send_ants(t_roompath *paths, t_lem_in *stat)
{
	int        	current_ant;
	t_roompath  *paths_head;

	paths_head = paths;
	current_ant = 0;
	while (stat->ants > 0 || paths->turns)
	{
		while (paths && stat->ants > 0)
		{
			if (count_legths_diffs(paths_head, paths, stat->ants))
			{
				turnadd(&paths->turns, paths->room, ++current_ant);
				stat->ants--;
			}
			paths = paths->next;
		}
		paths = paths_head;
		print_turns(paths);
		printf("\n");
	}
}