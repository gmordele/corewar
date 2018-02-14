/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_1_get_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:54:08 by edebise           #+#    #+#             */
/*   Updated: 2018/02/13 13:54:12 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm_0.h"

/*
**	vm_get_champ_nb()
**	si le flag -n est absent : défini le nb du champion a 0
**	si le flag -n est présent : défini le nb du champion avec le param suivant
**								sort avec vm_usage() si le param n'est pas valide
**								sort avec vm_usage() si le nb est celui d'un autre champ
**								l'index *n des params est incrémenté si besoin
*/

int		vm_get_champ_nb(t_all *all, int *n, char **av)
{
	t_champ	*tmp;
	int		champ_nb;
	long	l;
	char	*s;

	champ_nb = 0;
	if (!ft_strcmp(av[*n], "-n"))
	{
		s = av[++n[0]];
		l = (s ? ft_atol(s) : 0);
		champ_nb = (s ? ft_atoi_next(&s) : 0);
		if (!s || *s || champ_nb < 1 || champ_nb != l)
			vm_usage(all, spf("corewar: '%s' is not a valid champ number\n", av[*n]));
		tmp = all->champs;
		while (tmp)
		{
			if (tmp->nb == champ_nb)
				vm_usage(all, spf("corewar: many champs have the same number '%s'\n", av[*n]));
			tmp = tmp->next;
		}
		n[0]++;
	}
	return (champ_nb);
}

/*
**	vm_get_champ_path()
**	la fonction est appellée pour tous les params concernant les champs
**	défini champ->nb avec vm_get_champ_nb()
**	un champ est ajouté dans la liste all->champs :
**		si le path contient une extension '.cor'
**		si le fd du path est valide (fd = open(path))
**	sinon, le programme sort avec vm_usage()
*/

void	vm_get_champ_path(t_all *all, int *n, char **av)
{
	int		champ_nb;
	int		path_len;
	int		fd;
	char	*s;

	champ_nb = vm_get_champ_nb(all, n, av);
	path_len = (av[*n] ? ft_strlen(av[*n]) : 0);
	fd = 0;
	if (path_len > 4)
	{
		s = av[*n] + path_len - 4;
		if (!ft_strcmp(s, ".cor"))
			fd = open(av[*n], O_RDONLY);
	}
	if (fd < 1)
		vm_usage(all, spf("corewar: '%s' is not a valid champ path\n", av[*n]));
	vm_l_add_frt(&all->champs, vm_l_new(all, av[*n], fd, champ_nb));
	all->nb_champs++;
}

/*
**	vm_get_dump()
**	la fonction est appellée après le flag '-dump'
**	l'index *n des params est incrémenté
**	défini all->dump si le param suivant est un int valide
**	sinon, le programme sort avec vm_usage()
*/

void	vm_get_dump(t_all *all, int *n, char **av)
{
	int		i;
	long	l;
	char	*s;

	all->dump = 0;
	if ((s = av[++n[0]]))
	{
		l = ft_atol(s);
		i = ft_atoi_next(&s);
		if (!*s && i > 0 && i == l)
			all->dump = i;
	}
	if (!all->dump)
		vm_usage(all, spf("corewar: '%s' is not a valid dump number\n", av[*n]));
	pf("Dump {y}%d{0}\n", all->dump);		//	Debug
}

/*
**	vm_get_flag()
**	la fonction est appellée si un param commence par '-'
**	si le flag est traité si il est valide
**	sinon, le programme sort avec vm_usage()
*/

void	vm_get_flag(t_all *all, int *n, char **av)
{
	pf("Flag {y}%s{0}\n", av[*n]);		//	Debug
	if (!ft_strcmp(av[*n], "-help") || !ft_strcmp(av[*n], "--help"))
		vm_usage(all, 0);
	else if (!ft_strcmp(av[*n], "-dump") || !ft_strcmp(av[*n], "--dump"))
		vm_get_dump(all, n, av);
	else if (!ft_strcmp(av[*n], "-visu") || !ft_strcmp(av[*n], "--visu"))
		all->flag += (all->flag & VISU ? 0 : VISU);
	else
		vm_usage(all, spf("corewar: '%s' is not a valid flag\n", av[*n]));
}
