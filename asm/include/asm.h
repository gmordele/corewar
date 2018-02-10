/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:19:23 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 01:35:01 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_ASM_H
# define DEF_ASM_H

typedef struct	s_data
{

}				t_data;

typedef struct	s_token
{
	int		type;
	int		row;
	int		col;
	int		int_val;
	char	*str_val;
}				t_token;

#define MAX_FILE_SIZE 100000

void 			err_exit(t_data data);
void 			err_exit_str(char *str, t_data data);
void 			err_exit_strerror(char *str, t_data data);
char			*get_file_content(char *file, t_data data);

#endif
