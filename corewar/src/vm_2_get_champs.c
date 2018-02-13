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

void	vm_sort_champs(t_all *all)
{
	t_champ	*champ;
//	t_champ	*tmp;

	champ = all->champs;
}

void	vm_number_champs(t_all *all)
{
	t_champ	*champ;
	t_champ	*tmp;
	int		n;

	if (all->nb_champs > MAX_PLAYERS)
		vm_exit(all, "Too much champs in params\n");
	champ = all->champs;
	n = 1;
	while (champ)
	{
		if (!champ->nb && (tmp = all->champs))
			while (tmp)
			{
				if (tmp->nb == n && n++)
					tmp = all->champs;
				tmp = tmp->next;
			}
		if (!champ->nb)
			champ->nb = n++;
		champ = champ->next;
	}
	vm_sort_champs(all);
}

int		reverse_endian(unsigned int big)
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

void	vm_get_champs(t_all *all, int buf_size)
{
	char	buf[buf_size];
	t_champ	*champ;
	int		ret;

	champ = all->champs;
	while (champ)
	{
		ft_bzero(buf, buf_size);
		ret = read(champ->fd, buf, sizeof(t_header));
		champ->header = *((t_header*)buf);
		if (ret != sizeof(t_header))
			vm_exit(all, "Not valid size of header\n");
		if (reverse_endian(champ->header.magic) != COREWAR_EXEC_MAGIC)
			vm_exit(all, "Not valid magic number in header\n");
		ft_bzero(buf, buf_size);
		ret = read(champ->fd, buf, CHAMP_MAX_SIZE);
		if (ret != reverse_endian(champ->header.prog_size)
			|| ret > CHAMP_MAX_SIZE)
			vm_exit(all, "Not valid prog_size\n");
		champ->prog = ft_strndup(buf, ret);
		champ->prog_size = ret;
				pf("Magic {y}%#x\n{0}", reverse_endian(champ->header.magic));
				pf("Prog_size {y}%u\n{0}", reverse_endian(champ->header.prog_size));
				pf("Name {y}%s\n{0}", champ->header.prog_name);
				pf("Comment {y}%s\n{0}", champ->header.comment);
		all->nb_champs++;
		champ = champ->next;
	}
	vm_number_champs(all);
}
