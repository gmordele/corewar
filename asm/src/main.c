/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:24:15 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 20:10:08 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "asm.h"

static void init_data(t_data *data)
{
	(void)data;
}

void		free_data(t_data *data)
{
	(void)data;
	get_next_line(0, FREE_GNL);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data 	data;
	int		fd;
	t_token	*token;

	init_data(&data);
	if (argc < 2)
		err_exit_str("need argument", &data);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		err_exit_strerror("open()", &data);
	token = get_next_token(fd, &data);
	while (token != NULL && token->type != TOK_END)
	{
		print_token(1, token);
		ft_putchar('\n');
		free_token(token);
		token = get_next_token(fd, &data);
	}
	free_token(token);
	close(fd);
	free_data(&data);
	return (0);
}
