/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:09 by edebise           #+#    #+#             */
/*   Updated: 2018/02/11 20:32:16 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm_0.h"

/*
**	vm_exit()
**	sort du programme proprement en libérant les mallocs depuis la structure t_all
**	si un error_mail est defini, il sera affiché sur la sortie d'erreur
*/

int		vm_exit(t_all *all, char *error_mail)
{
	vm_l_del(&all->champs);
	/*ft_free();*/
	if (error_mail)
		fpf(2, "{r}%s{0}", error_mail);
	exit(0);
	return (0);
}

/*
**	vm_usage()
**	affiche l'usage de l'executable sur la sortie d'erreur
**	si un error_mail est defini, il sera affiché sur la sortie d'erreur
**	sort du programme proprement en vm_exit()
*/

void	vm_usage(t_all *all, char *error_mail)
{
	if (error_mail)
	{
		fpf(2, "{y}%s{0}", error_mail);
		ft_free(1, &error_mail);
	}
	fpf(2, "usage:\tcorewar [--help] [--visu] [--dump nb_cycles] [-n] champ.cor ...\n");
	fpf(2, "\t--help: display the usage you're looking at\n");
	fpf(2, "\t--visu: execute corewar with a visual tool\n");
	fpf(2, "\t--dump: set number of cycles, must be followed by a reasonable int\n");
	fpf(2, "\t-n: set number of the following champ in params\n");
	fpf(2, "\t    must be followed by an int and a champ.cor\n");
	fpf(2, "\t    otherwise, corewar set this number in order of params\n");
	fpf(2, "\t    last player process will be execute in first\n");
	vm_exit(all, 0);
}

/*
**	vm_malloc()
**	alloue de la mémoire en appelant ft_malloc
**	ft_malloc alloue de la mémoire initialisée a 0 en appelant malloc
**	sort du programme proprement en vm_exit() si ft_malloc renvoie NULL
*/

void	*vm_malloc(t_all *all, int size)
{
	void *ptr;

	if (!(ptr = (void*)ft_malloc(size)))
		vm_exit(all, "Error of malloc\n");
	return (ptr);
}

/*
**	vm_init()
**	initialise les variables de la structure t_all
**	parcourt les parametres en appelant les fonctions adéquates
**	sort du programme avec vm_usage si besoin
*/

void	vm_init(t_all *all, int ac, char **av)
{
	int		n;

	ft_int(0, 3, &all->nb_champs, &all->flag, &all->dump);
	ft_ptr(NULL, 1, &all->champs);
	ft_strcpy(all->color, "\x1b[32m_\x1b[36m_\x1b[31m_\x1b[33m");
	ft_char(0, 3, all->color + 5, all->color + 11, all->color + 17);
	n = 0;
	while (++n < ac)
	{
		if (av[n][0] != '-' || !ft_strcmp(av[n], "-n"))
			vm_get_champ_path(all, &n, av);
		else
			vm_get_flag(all, &n, av);
	}
	if (!all->champs)
		vm_usage(all, spf("corewar: no champ enough\n"));
	if (all->nb_champs > MAX_PLAYERS)
		vm_exit(all, "Too much champs in params\n");
}

/*
**	main()
**	appelle les fonctions sur toutes les grandes étapes de la vm
*/

int		main(int ac, char **av)
{
	t_all	all;

	vm_init(&all, ac, av);
	vm_get_champs(&all, all.champs, sizeof(t_header));
	return (0);
}
