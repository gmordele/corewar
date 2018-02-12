/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:24:15 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/13 00:03:06 by gmordele         ###   ########.fr       */
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

static void init_data(t_data *data, char *file_name)
{
	(void)data;
	data->file_name = NULL;
	data->new_file_name = NULL;
	if ((data->file_name = ft_strdup(file_name)) == NULL)
		err_exit_str("init_data(): ft_strdup() failed", data);
	if ((data->new_file_name = new_file_name(file_name, data)) == NULL)
		err_exit_str("Bad file name", data);
}

void		free_data(t_data *data)
{
	if (data->file_name != NULL)
		free(data->file_name);
	if (data->new_file_name != NULL)
		free(data->new_file_name);
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
	ft_printf("new_file_name = %s\n", data.new_file_name);
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
	print_token(1, token);
	ft_putchar('\n');
	free_token(token);
	close(fd);
	free_data(&data);
	return (0);
}
