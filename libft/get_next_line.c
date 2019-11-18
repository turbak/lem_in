/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:39:55 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/18 19:47:19 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				get_next_line(const int fd, char **line)
{
	static	char	*a[256];
	char			buf[BUFF_SIZE + 1];
	int				n;

	CHECKRETURN(fd < 0 || !line || (read(fd, buf, 0) < 0), -1);
	if (!a[fd])
		a[fd] = ft_strnew(0);
	while ((n = read(fd, buf, BUFF_SIZE)))
	{
		buf[n] = '\0';
		ft_swapfree((void**)&a[fd], ft_strjoin(a[fd], buf));
		if (ft_strchr(a[fd], '\n'))
			break ;
	}
	CHECKRETURN((!n && *a[fd] == '\0'), 0);
	n = 0;
	while (a[fd][n] && a[fd][n] != '\n')
		n++;
	*line = ft_strsub(a[fd], 0, n);
	(ft_strlen(*line) < ft_strlen(a[fd])) ?
	ft_swapfree((void **)&a[fd], ft_strdup(a[fd] + n + 1))
	: ft_strdel(&a[fd]);
	return (1);
}
