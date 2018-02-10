/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:24:15 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 01:31:55 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static void init_data(t_data *data)
{
	(void)data;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data data;

	init_data(&data);
	if (argc < 2)
		err_exit_str("need argument", data);
	ft_printf("%s\n", get_file_content(argv[1], data));

	return (0);
}
