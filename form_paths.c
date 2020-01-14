#include "lem_in.h"

void roomaddend(t_rooms **rooms, t_rooms *new)
{
	t_rooms *rooms_head;

	rooms_head = *rooms;
	if (!(*rooms))
	{
		*rooms = new;
		return;
	}
	if (!(*rooms)->next)
	{
		(*rooms)->next = new;
		return;
	}
	while ((*rooms)->next)
		*rooms = (*rooms)->next;
	(*rooms)->next = new;
	(*rooms) = rooms_head;
}

t_rooms *roomcpy(t_rooms *room)
{
	t_rooms *new;

	new = (t_rooms *)malloc(sizeof(t_rooms));
	new->next = NULL;
	new->start = room->start;
	new->end = room->end;
	new->output = room->output;
	new->input = room->input;
	new->ants = room->ants;
	new->bfs = room->bfs;
	new->name = room->name;
	new->x = room->x;
	new->y = room->y;
	return (new);
}

t_rooms *find_next_path(t_links *link, t_rooms *current, t_rooms **list)
{
	while (link && link->s != current)
		link = link->next;
	if (link->f->end)
	{
		roomaddend(list, roomcpy(link->s));
		return (NULL);
	}
	else
	{
		roomaddend(list, roomcpy(link->s));
		return (link->f);
	}
}

t_roompath *form_path(t_links *link, t_lem_in *stat)
{
	t_rooms *current;
	t_links *links_head;
	t_roompath *roompath;

	roompath = (t_roompath*)malloc(sizeof(t_roompath));
	roompath->next = NULL;
	roompath->room = NULL;
	roompath->turns = NULL;
	roomaddend(&roompath->room, roomcpy(link->s));
	roompath->length = 0;
	current = link->f;
	links_head = stat->links;
	while ((current = find_next_path(links_head, current, &roompath->room)))
		roompath->length++;
	roomaddend(&roompath->room, roomcpy(stat->end));
	roompath->length++;
	return (roompath);
}

t_roompath *roompathadd(t_roompath **roompath, t_roompath *new)
{
	t_roompath *head;

	if (new->length == 18)
		new = new;
	head = *roompath;
	if (!*roompath)
	{
		*roompath = new;
		return (*roompath);
	}
	if (!(*roompath)->next || (*roompath)->length > new->length)
	{
		if ((*roompath)->length < new->length)
		{
			(*roompath)->next = new;
			return (*roompath);
		}
		else
		{
			new->next = *roompath;
			return (new);
		}
	}
	while ((*roompath)->next && (*roompath)->next->length < new->length)
		*roompath = (*roompath)->next;
	new->next = (*roompath)->next;
	(*roompath)->next = new;
	return (head);
}

t_roompath *form_and_sort_paths(t_lem_in *stat)
{
	t_rooms *begin;
	t_links *buf;
	t_roompath *paths;

	begin = find_start(stat->rooms);
	paths = NULL;
	buf = stat->links;
	while ((buf = find_next_link(buf, begin)))
	{
		paths = roompathadd(&paths, form_path(buf, stat));
		buf = buf->next;
	}
	int i = 0;
	while (stat->read[i])
	{
		printf("%s\n", stat->read[i]);
		i++;
	}
	printf("\n");
	send_ants(paths, stat);
	return (paths);
}