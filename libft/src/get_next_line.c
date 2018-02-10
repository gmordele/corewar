/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:51:36 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/01 01:50:18 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void			add_chunk(char **line, char *buff, size_t size)
{
	char	*tmp;
	char	*ptr_tmp;

	if (*line == NULL)
		if ((*line = ft_strnew(1)) == NULL)
			return ;
	if ((tmp = ft_strsub(buff, 0, size)) == NULL)
	{
		ft_strdel(line);
		return ;
	}
	ptr_tmp = *line;
	*line = ft_strjoin(*line, tmp);
	free(ptr_tmp);
	free(tmp);
}

static void			parse(const int fd, char **line, t_fd_buff *fd_buff)
{
	unsigned int b_p;

	b_p = fd_buff->pos;
	while (fd_buff->buff[fd_buff->pos] != '\n' && fd_buff->n > 0)
	{
		if (--(fd_buff->n) == 0)
		{
			add_chunk(line, fd_buff->buff + b_p, fd_buff->pos - b_p + 1);
			if (*line == NULL)
				return ;
			fd_buff->pos = 0;
			b_p = fd_buff->pos;
			fd_buff->n = read(fd, fd_buff->buff, BUFF_SIZE_GNL);
		}
		else
			(fd_buff->pos)++;
	}
	if (fd_buff->n > 0)
	{
		add_chunk(line, fd_buff->buff + b_p, fd_buff->pos - b_p);
		--(fd_buff->n);
		++(fd_buff->pos);
	}
}

static t_fd_buff	*find_fd_buff(t_list *lst, int fd)
{
	while (lst != NULL)
	{
		if (((t_fd_buff *)lst->content)->fd == fd)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

static t_fd_buff	*select_fd_buff(t_list **lst, int fd)
{
	t_fd_buff	*new_fd_buff;
	t_fd_buff	*ptr;
	t_list		*new_lst;

	if ((ptr = find_fd_buff(*lst, fd)) != NULL)
		return (ptr);
	if ((new_fd_buff = (t_fd_buff *)malloc(sizeof(t_fd_buff))) == NULL)
		return (NULL);
	new_fd_buff->fd = fd;
	new_fd_buff->pos = 0;
	new_fd_buff->n = 0;
	new_fd_buff->buff = (char *)malloc(sizeof(char) * BUFF_SIZE_GNL);
	if (new_fd_buff->buff == NULL)
		return (NULL);
	if ((new_lst = ft_lstnew(new_fd_buff, sizeof(t_fd_buff))) == NULL)
		return (NULL);
	ft_lstadd(lst, new_lst);
	free(new_fd_buff);
	return ((*lst)->content);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	t_fd_buff		*fd_buff;

	if (line == FREE_GNL)
		return (free_gnl_lst(&lst));
	if (line == NULL)
		return (-1);
	*line = NULL;
	fd_buff = select_fd_buff(&lst, fd);
	if (fd_buff == NULL)
		return (-1);
	if (fd_buff->n <= 0)
	{
		if ((fd_buff->n = read(fd, fd_buff->buff, BUFF_SIZE_GNL)) <= 0)
			return (fd_buff->n);
		else
			fd_buff->pos = 0;
	}
	parse(fd, line, fd_buff);
	if (*line != NULL)
		return (1);
	else
		return (-1);
}
