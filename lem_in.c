/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:23:46 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/20 14:58:51 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(-1);
}

t_lem_in	*init(char *tmp)
{
	t_lem_in	*stat;
	int			i;

	i = 0;
	stat = malloc(sizeof(t_lem_in));
	stat->read = ft_strsplit(tmp, '\n');
	ft_strdel(&tmp);
	read_stat(stat);
	return (NULL);
}

int	main(int ac, char **av)
{
	char *line;
	char *tmp;
	int	fd;

	if (ac < 2)
	{
		error("Usage: ./lem-in < map_file");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	tmp = ft_strnew(0);
	while (get_next_line(fd, &line) > 0)
	{
		ft_swapfree((void **)&tmp, ft_strjoin(tmp, line));
		ft_swapfree((void **)&tmp, ft_strjoin(tmp, "\n"));
		ft_strdel(&line);
	}
	init(tmp);
	return (0);
}
