/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:24:15 by gmordele          #+#    #+#             */
/*   Updated: 2018/03/01 20:29:38 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "asm.h"

static char	*new_file_name(char *file_name, t_data *data)
{
	int		i;
	char	*ret;

	i = ft_strlen(file_name);
	while (file_name[i] != '.' && i > 0)
		--i;
	if (!ft_strequ(file_name + i, ".s"))
		return (NULL);
	if ((ret = (char *)malloc(ft_strlen(file_name) + 3)) == NULL)
		err_exit_strerror("malloc()", data);
	ft_strcpy(ret, file_name);
	ft_strcpy(ret + i, ".cor");
	return (ret);
}

static void	init_data(t_data *data, char *file_name)
{
	(void)data;
	data->file_name = NULL;
	data->new_file_name = NULL;
	data->str = NULL;
	data->statement_lst = NULL;
	ft_bzero(&(data->header), sizeof(data->header));
	if ((data->file_name = ft_strdup(file_name)) == NULL)
		err_exit_str("init_data(): ft_strdup() failed", data);
	if ((data->new_file_name = new_file_name(file_name, data)) == NULL)
		err_exit_str("bad file name", data);
	data->header.magic = reverse_endian_int(COREWAR_EXEC_MAGIC);
}

void		free_data(t_data *data)
{
	if (data->file_name != NULL)
		free(data->file_name);
	if (data->new_file_name != NULL)
		free(data->new_file_name);
	ft_strdel(&(data->str));
	statement_lst_free(data);
	get_next_line(0, FREE_GNL);
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	int		fd_write;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 2)
		err_exit_str("missing argument", &data);
	init_data(&data, argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		err_exit_strerror("open()", &data);
	get_header(fd, &data);
	get_statements(fd, &data);
	get_offsets(&data);
	get_write_buf(&data);
	if ((fd_write = open(data.new_file_name,
						O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0)
		err_exit_strerror("open():", &data);
	write_buf(fd_write, &data);
	ft_printf("Writing output program to %s\n", data.new_file_name);
	close(fd);
	close(fd_write);
	free_data(&data);
	return (0);
}
