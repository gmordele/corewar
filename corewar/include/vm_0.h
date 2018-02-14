/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:29:04 by edebise           #+#    #+#             */
/*   Updated: 2018/02/11 20:29:06 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_0_H
# define VM_0_H

# include "libft.h"
# include "op.h"
# define VISU 1

typedef	struct		s_champ
{
	t_header		header;
	char			*path;
	char			prog[CHAMP_MAX_SIZE];
	int				prog_size;
	int				fd;
	int				nb;
	char			*color;
	struct s_champ	*prev;
	struct s_champ	*next;
}					t_champ;

typedef	struct		s_all
{
	t_champ			*champs;
	char			color[40];
	int				nb_champs;
	int				dump;
	int				flag;
}					t_all;

void				vm_usage(t_all *all, char *error_mail);
int					vm_exit(t_all *all, char *error_mail);
void				*vm_malloc(t_all *all, int size);
t_champ				*vm_l_add_frt(t_champ **list, t_champ *new);
t_champ				*vm_l_add_bck(t_champ **list, t_champ *new);
void				vm_l_del(t_champ **list);
t_champ				*vm_l_del_one(t_champ **list, t_champ *target);
t_champ				*vm_l_new(t_all *all, char *path, int fd, int nb);
void				vm_get_flag(t_all *all, int *n, char **av);
void				vm_get_champ_path(t_all *all, int *n, char **av);
void				vm_get_champs(t_all *all, t_champ *champ, int buf_size);

#endif
