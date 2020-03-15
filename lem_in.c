/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:23:46 by cauranus          #+#    #+#             */
/*   Updated: 2020/02/17 18:24:19 by tgarkbit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	remove_output_and_input_forks(t_lem_in *stat)
{
	stat->bfs--;
	remove_useless_rooms_and_links(stat);
	build_path(stat);
	stat->links = dead_links(&stat->links);
	stat->rooms = dead_rooms(&stat->rooms);
	remove_output_forks(stat);
	stat->links = dead_links(&stat->links);
	stat->rooms = dead_rooms(&stat->rooms);
	form_and_sort_paths(stat);
}

void	error(char *str)
{
	str = "ERROR";
	ft_putendl_fd(str, 2);
	exit(0);
}

void	init(char *tmp)
{
	t_lem_in	*stat;

	stat = (t_lem_in *)malloc(sizeof(t_lem_in));
	stat->read = ft_strsplit(tmp, '\n');
	ft_strdel(&tmp);
	read_stat(stat);
}

int		main(int ac, char **av)
{
	char	*line;
	char	*tmp;
	int		fd;

	fd = 0;
	tmp = ft_strnew(0);
	while (get_next_line(fd, &line) > 0)
	{
		ft_swapfree((void **)&tmp, ft_strjoin(tmp, line));
		ft_swapfree((void **)&tmp, ft_strjoin(tmp, "\n"));
		ft_strdel(&line);
	}
	if (!*tmp || ac > 2)
	{
		ft_putstr("Usage: ./lem-in < map_file");
		exit(0);
	}
	else
		init(tmp);
	return (0);
}
