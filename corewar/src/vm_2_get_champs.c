/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_2_get_champs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:42:35 by edebise           #+#    #+#             */
/*   Updated: 2018/02/13 16:42:39 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	rev_endian_short()
**	Return a short with reverse endian
*/

short	rev_endian_short(short in)
{
	short	out;
	char	*ptr_in;
	char	*ptr_out;

	ptr_in = (char*)&in;
	ptr_out = (char*)&out;
	ptr_out[0] = ptr_in[1];
	ptr_out[1] = ptr_in[0];
	return (out);
}

/*
**	rev_endian_int()
**	Return a int with reverse endian
*/

int		rev_endian_int(int in)
{
	int	out;
	char	*ptr_in;
	char	*ptr_out;

	ptr_in = (char*)&in;
	ptr_out = (char*)&out;
	ptr_out[0] = ptr_in[3];
	ptr_out[1] = ptr_in[2];
	ptr_out[2] = ptr_in[1];
	ptr_out[3] = ptr_in[0];
	return (out);
}

/*
**	vm_sort_champs()
**	Sort champ_tab by champ_nb, from biggest to littlest
*/

void	vm_sort_champs(t_all *all)
{
	t_champ	tmp;
	int		n;
	int		i;

	n = all->nb_champ;
	while (n-- > 1)
	{
		i = 0;
		while (i < n)
		{
			if (all->champ[i].nb < all->champ[i + 1].nb)
			{
				tmp = all->champ[i];
				all->champ[i] = all->champ[i + 1];
				all->champ[i + 1] = tmp;
			}
			i++;
		}
	}
	ft_strcpy(all->champ[0].color, "\x1b[32m");
	ft_strcpy(all->champ[1].color, "\x1b[36m");
	ft_strcpy(all->champ[2].color, "\x1b[35m");
	ft_strcpy(all->champ[3].color, "\x1b[33m");
	n = 0;
	while (n < all->nb_champ)
	{
		pf("Champ %d %s%s\n%s\n{0}", all->champ[n].nb, all->champ[n].color, all->champ[n].header.prog_name, all->champ[n].header.comment);
		n++;
	}
}

/*
**	vm_number_champs()
**	For each champ define a champ_nb if it is not define yet
*/

void	vm_number_champs(t_all *all)
{
	int		champ_nb;
	int		n;
	int		i;

	champ_nb = -1;
	n = 0;
	while (n < all->nb_champ)
	{
		if (!all->champ[n].nb)
		{
			i = 0;
			while (i < all->nb_champ)
			{
				if (champ_nb == all->champ[i].nb)
				{
					champ_nb--;
					i = 0;
				}
				i++;
			}
			all->champ[n].nb = champ_nb;
		}
//		pf("Champ %d %s%s\n%s\n{0}", all->champ[n].nb, all->champ[n].color, all->champ[n].header.prog_name, all->champ[n].header.comment);
		n++;
	}
	vm_sort_champs(all);
}

/*
**	vm_get_champs()
**	Pour chaque champ_path de all->champ :
**		récupère la struct t_header et check la validité (taille du header et magic)
**		place un '\0' a la fin de prog_name et prog_comment par sécurité
**		récupère le programme binaire et check la validité (taille du prog)
*/

void	vm_get_champs(t_all *all, int buf_size)
{
	char	buf[buf_size];
	int		ret;
	int		n;

	n = 0;
	while (n < all->nb_champ)
	{
		ft_bzero(buf, buf_size);
		ret = read(all->champ[n].fd, buf, sizeof(t_header));
		all->champ[n].header = *((t_header*)buf);
		if (ret != sizeof(t_header))
			vm_exit(all, "Not valid size of header\n");
		if (rev_endian_int(all->champ[n].header.magic) != COREWAR_EXEC_MAGIC)
			vm_exit(all, "Not valid magic number in header\n");
		all->champ[n].header.prog_name[PROG_NAME_LENGTH] = '\0';
		all->champ[n].header.comment[COMMENT_LENGTH] = '\0';
		ft_bzero(buf, buf_size);
		ret = read(all->champ[n].fd, buf, CHAMP_MAX_SIZE);
		if (ret != rev_endian_int(all->champ[n].header.prog_size)
			|| ret > CHAMP_MAX_SIZE)
			vm_exit(all, "Not valid prog_size\n");
		ft_memcpy(all->champ[n].prog, buf, ret);
		all->champ[n].prog_size = ret;
		n++;
	}
	vm_number_champs(all);
}
