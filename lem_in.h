/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:22:05 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:17:51 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct		s_rooms
{
	char			*name;
	int				x;
	int				y;
	int				ants;
	int				start;
	int				end;
	int				bfs;
	int				input;
	int				output;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_links
{
	t_rooms				*s;
	t_rooms				*f;
	struct s_links		*next;
}					t_links;

typedef struct		s_lem_in
{
	char		**read;
	int			ants;
	t_rooms		*rooms;
	t_links		*links;
	t_rooms		*end;
	t_rooms		*start;
	int			bfs;
}					t_lem_in;

typedef struct		s_outpath
{
	t_links				*link;
	int					length;
	struct s_outpath	*next;
}					t_outpath;

typedef struct		s_turn
{
	t_rooms			*room;
	int				ant_num;
	struct s_turn	*next;
}					t_turn;

typedef struct		s_roompath
{
	t_rooms				*room;
	int					length;
	t_turn				*turns;
	struct s_roompath	*next;
}					t_roompath;

typedef struct		s_queue
{
	t_rooms			*room;
	struct s_queue	*next;
}					t_queue;

t_rooms				*room_init(char **str, int com);
t_links				*link_init(char **str, t_rooms *rooms);
void				read_stat(t_lem_in *stat);
int					is_comment(char *str);
int					command(char *str);
int					is_room(char *str);
int					is_link(char *str);
int					is_name(char *str);
void				error(char *str);
void				linkadd(t_links **links, t_links *new);
void				roomadd(t_rooms **room, t_rooms *new);
void				error_mngr(t_lem_in *stat);
t_rooms				*find_start(t_rooms *rooms);
t_rooms				*find_end(t_rooms *rooms);
t_rooms				*find_room(t_rooms *rooms, char *name);
void				free_stat(t_lem_in *stat);
void				bfs(t_lem_in *stat);
void				ft_swap(void **ptr1, void **ptr2);
t_rooms				*roomdels(t_rooms **rooms, t_rooms *start);
t_links				*linkdels(t_links **links, t_links *start);
void				linkdelm(t_links **links, t_links *next);
void				roomdelm(t_rooms **rooms, t_rooms *next);
t_rooms				*dead_rooms(t_rooms **rooms);
t_links				*dead_links(t_links **links);
void				dequeue(t_queue **queue, t_queue *start);
void				build_path(t_lem_in *stat);
t_links				*find_link(t_links **link, char *name, int bfs);
void				delete_forks(t_lem_in *stat, t_rooms *rooms);
void				remove_output_forks(t_lem_in *stat);
void				form_and_sort_paths(t_lem_in *stat);
t_links				*find_next_link(t_links *link, t_rooms *room);
void				send_ants(t_roompath *paths, t_lem_in *stat);
void				free_turns(t_turn **turn);
void				free_paths(t_roompath *paths);
int					free_turns_first(t_turn **turn);
void				add_path(t_outpath **path, t_outpath *new);
t_outpath			*path_init(int length, t_links *link);
void				free_out_forks(t_outpath *path, t_links **link, int minlen);
t_rooms				*roomcpy(t_rooms *room);
void				remove_output_and_input_forks(t_lem_in *stat);
t_queue				*init_queue(t_rooms *room);
int					enqueue(t_queue **queue, t_queue *new);
void				remove_useless_rooms_and_links(t_lem_in *stat);

#endif
