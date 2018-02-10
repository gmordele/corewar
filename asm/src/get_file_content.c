/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:27:02 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 01:39:26 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "asm.h"
#include "libft.h"

static long	get_filed_size(int fd, t_data *data)
{
	long	size;

	if ((size = lseek(fd, 0, SEEK_END)) < 0)
		err_exit_strerror("lseek()", data);
	if (lseek(fd, 0, SEEK_SET) < 0)
		err_exit_strerror("lseek()", data);
	return (size);
}

char		*get_file_content(char *file, t_data *data)
{
	long	size;
	int		fd;
	char	*content;

	if ((fd = open(file, O_RDONLY)) < 0)
		err_exit_strerror("open()", data);
	size = get_filed_size(fd, data);
	if (size <= 0 || size > MAX_FILE_SIZE)
		err_exit_str("bad file size", data);
	if ((content = (char *)malloc(size + 1)) == NULL)
		err_exit_strerror("malloc()", data);
	ft_bzero(content, size + 1);
	if ((read(fd, content, size)) < 0)
		err_exit_strerror("read()", data);
	close(fd);
	return (content);
}
