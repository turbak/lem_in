/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:55:31 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/18 19:44:29 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_comment(char *str)
{
	if (!str)
		error("invalid map");
	if (!command(str) && str[0] == '#')
		return(1);
	return (0);
}

int	command(char *str)
{
	if (ft_strequ(str, "##start"))
		return (1);
	if (ft_strequ(str, "##end"))
		return (2);
	return(0);
}

int is_room(char *str)
{
	char	**s;
	int 	i;
	int		ret;

	s = ft_strsplit(str, ' ');
	ret = 0;
	i = 0;
	if (!s)
		return (ret);
	while(s[i])
		i++;
	if (i == 3 && ft_isint(s[1]) && ft_isint(s[2]))
			ret = 1;
	i = -1;
	while (s[++i])
		ft_strdel(&s[i]);
	free(s);
	s = NULL;
	return (ret);
}

int	is_link(char *str)
{
	char 	**s;
	int		i;
	int		ret;

	s = ft_strsplit(str, '-');
	i = 0;
	ret = 0;
	if (!s)
		return (ret);
	while(s[i])
		i++;
	if (i == 2)
		ret = 1;
	i = -1;
	while (s[++i])
		ft_strdel(&s[i]);
	free(s);
	s = NULL;
	return (ret);
}
