/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:22:05 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/19 00:16:47 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"
#include <stdio.h>

typedef struct	s_rooms
{
	char		*name;
	int			x;
	int			y;
	int			ants;
	int			start;
	int			end;
	struct s_rooms		*next;
}				t_rooms;

typedef struct	s_links
{
	char				*start;
	char				*link;
	struct s_links		*next;
}				t_links;

typedef struct	s_lem_in
{
	char		**read;
	int			ants;
	t_rooms		*rooms;
	t_links		*links;
	t_rooms		*end;
	t_rooms		*start;
	int			**matrix;
}				t_lem_in;

void	write_d(t_lem_in *stat);
t_rooms *room_init(char **str, int com);
t_links	*link_init(char **str);
void	read_stat(t_lem_in *stat);
int		is_comment(char *str);
int		command(char *str);
int 	is_room(char *str);
int		is_link(char *str);
int		is_name(char *str);
void	error(char *str);
void	linkadd(t_links **links, t_links *new);
void	roomadd(t_rooms **room, t_rooms *new);
int		**id_matrix(t_lem_in **stat);

#endif