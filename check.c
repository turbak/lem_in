/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:55:31 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/14 13:59:59 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
* файл с функциями для проверки валидности(надо дописать ft_is_int.c в либе)
*/

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

int	is_name(char *str)
{
	return (ft_strlen(str) > 0 && str[0] != '#' && str[0] != 'L');
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
	if (i == 3 && is_name(s[0])/* && ft_isint(s[1])*/)
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
	if (i == 2 && is_name(s[0]) && is_name(s[1]))
		ret = 1;
	i = -1;
	while (s[++i])
		ft_strdel(&s[i]);
	free(s);
	s = NULL;
	return (ret);
}
