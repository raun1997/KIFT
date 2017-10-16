/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 15:33:03 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/07 20:56:57 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_it(const int fd, char **holder, t_gnl *gnl)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;

	if ((gnl->counter = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[gnl->counter] = 0;
		if (*holder)
		{
			tmp = ft_strdup(*holder);
			ft_strdel(&(*holder));
			*holder = ft_strjoin(tmp, buff);
			ft_strdel(&tmp);
		}
		else
			*holder = ft_strdup(buff);
	}
	if (gnl->counter == 0)
		ft_strdel(&(*holder));
	return (gnl->counter);
}

static void	get_it(char **buff, t_gnl *gnl)
{
	gnl->next = ft_strdup(gnl->end + 1);
	ft_strdel(&(*buff));
	*buff = ft_strdup(gnl->next);
	ft_strdel(&(gnl->next));
}

int			get_next_line(const int fd, char **line)
{
	static char		*buff[FD_COUNT];
	t_gnl			gnl;

	if (fd < 0 || fd > FD_COUNT || line == NULL)
		return (-1);
	while ((gnl.counter = read_it(fd, &buff[fd], &gnl)) >= 0)
	{
		if (gnl.counter != 0 && (gnl.end = ft_strchr(buff[fd], ENDCHAR))
				!= NULL)
			break ;
		if (gnl.counter == 0)
		{
			if (!buff[fd])
				return (0);
			*line = ft_strdup(buff[fd]);
			ft_strdel(&buff[fd]);
			return (1);
		}
	}
	if (gnl.counter < 0)
		return (-1);
	*line = ft_strsub(buff[fd], 0, (gnl.end - buff[fd]));
	get_it(&buff[fd], &gnl);
	return (1);
}
