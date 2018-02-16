/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:29:04 by edebise           #+#    #+#             */
/*   Updated: 2018/02/16 19:35:09 by proso            ###   ########.fr       */
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
	char			color[10];
	struct s_champ	*prev;
	struct s_champ	*next;
}					t_champ;

typedef	struct		s_process
{
	int				pc;
	int				r[17];
	int				carry;
	int				cycle;
	int				nb_live;
	int				num;
	struct s_champ	*prev;
	struct s_champ	*next;
}					t_process;

typedef	struct		s_all
{
	t_champ			champ[MAX_PLAYERS];
	t_process		*process_list;
	int				nb_champ;
	int				dump;
	int				flag;
	int				cycle;
	int				cycle_to_die;
	char			arena[MEM_SIZE];
	char			color[MEM_SIZE];
}					t_all;

void				vm_usage(t_all *all, char *error_mail);
int					vm_exit(t_all *all, char *error_mail);
void				*vm_malloc(t_all *all, int size);
void				vm_get_flag(t_all *all, int *n, char **av);
void				vm_get_champ_path(t_all *all, int *n, char **av);
void				vm_get_champs(t_all *all, int buf_size);
void				vm_number_champs(t_all *all);
short				rev_endian_short(short in);
int					rev_endian_int(int in);
void				vm_set_arena(t_all *all);
void				vm_set_process(t_all *all);

#endif
