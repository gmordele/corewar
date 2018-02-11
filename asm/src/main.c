/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:24:15 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 05:29:08 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "asm.h"

static void init_data(t_data *data, char *file_name)
{
	(void)data;
	data->file_name = ft_strdup(file_name);
}

void		free_data(t_data *data)
{
	(void)data;
	if (data->file_name != NULL)
		free(data->file_name);
	get_next_line(0, FREE_GNL);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data 	data;
	int		fd;
	t_token	*token;

	if (argc < 2)
		err_exit_str("need argument", &data);
	init_data(&data, argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		err_exit_strerror("open()", &data);
	token = get_next_token(fd, &data);
	while (token != NULL && token->type != TOK_END)
	{
//		print_token(1, token);
//		ft_putchar('\n');
		free_token(token);
		token = get_next_token(fd, &data);
	}
	free_token(token);
	close(fd);
	free_data(&data);
	return (0);
}
