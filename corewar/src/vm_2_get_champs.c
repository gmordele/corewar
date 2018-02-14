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

# include "vm_0.h"

/*
**	vm_rev_endian()
**	Renvoie un int avec les octets inversés
*/

int		rev_endian(int big)
{
	int		little;
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char*)&little;
	ptr2 = (char*)&big;
	ptr1[0] = ptr2[3];
	ptr1[1] = ptr2[2];
	ptr1[2] = ptr2[1];
	ptr1[3] = ptr2[0];
	return (little);
}

/*
**	vm_sort_champs()
**	Crée une nouvelle liste triée par nb de champions à partir de all->champs
*/

void	vm_sort_champs(t_all *all, t_champ *old_list)
{
	t_champ	*target;
	t_champ	*tmp;
	int		n;

	all->champs = NULL;
	n = all->nb_champs;
	while (n-- > 0 && old_list)
	{
		ft_ptr(old_list, 2, &target, &tmp);
		while (tmp)
		{
			if (tmp->nb > target->nb)
				target = tmp;
			tmp = tmp->next;
		}
		if (target == old_list)
			old_list = old_list->next;
		if (target->prev)
			target->prev->next = target->next;
		if (target->next)
			target->next->prev = target->prev;
		target->color = all->color + (n * 6);
		vm_l_add_frt(&all->champs, target);
	}
	tmp = all->champs;			//	Debug
	while (tmp)					//	Debug
	{
		pf("Champ %d %s%s %d octets\n", tmp->nb, tmp->color, tmp->header.prog_name, tmp->prog_size);			//	Debug
		pf("Magic %#x\n", rev_endian(tmp->header.magic));			//	Debug
		pf("%s\n{0}", tmp->header.comment);						//	Debug
		tmp = tmp->next;
	}
}

/*
**	vm_number_champs()
**	Pour chaque champion de all->champs :
**		defini un nb si il n'est pas déjà défini dans les params
**		vérifie qu'il n'y ait pas de doublon
*/

void	vm_number_champs(t_all *all)
{
	t_champ	*champ;
	t_champ	*tmp;
	int		n;

	champ = all->champs;
	n = 1;
	while (champ)
	{
		if (!champ->nb && (tmp = all->champs))
			while (tmp)
			{
				if (tmp->nb == n && ++n)
					tmp = all->champs;
				else
					tmp = tmp->next;
			}
		if (!champ->nb)
			champ->nb = n++;
		champ = champ->next;
	}
	vm_sort_champs(all, all->champs);
}

/*
**	vm_get_champs()
**	Pour chaque champ_path de all->champs :
**		récupère la struct t_header et check la validité (taille du header et magic)
**		place un '\0' a la fin de prog_name et prog_comment par sécurité
**		récupère le programme binaire et check la validité (taille du prog)
*/

void	vm_get_champs(t_all *all, t_champ *champ, int buf_size)
{
	char	buf[buf_size];
	int		ret;

	while (champ)
	{
		ft_bzero(buf, buf_size);
		ret = read(champ->fd, buf, sizeof(t_header));
		champ->header = *((t_header*)buf);
		if (ret != sizeof(t_header))
			vm_exit(all, "Not valid size of header\n");
		if (rev_endian(champ->header.magic) != COREWAR_EXEC_MAGIC)
			vm_exit(all, "Not valid magic number in header\n");
		champ->header.prog_name[PROG_NAME_LENGTH] = '\0';
		champ->header.comment[COMMENT_LENGTH] = '\0';
		ft_bzero(buf, buf_size);
		ret = read(champ->fd, buf, CHAMP_MAX_SIZE);
		if (ret != rev_endian(champ->header.prog_size)
			|| ret > CHAMP_MAX_SIZE)
			vm_exit(all, "Not valid prog_size\n");
		ft_memcpy(champ->prog, buf, ret);
		champ->prog_size = ret;
		champ = champ->next;
	}
	vm_number_champs(all);
}
