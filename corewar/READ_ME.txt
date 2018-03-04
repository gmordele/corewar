Il faudrait prévoir de faire pause quand la partie est finie !

J'ai encore corrigé une erreur de %IDX_MOD qui faisait merder un seul combat parmis tous les match possibles dans champs/cor/

J'ai fait les tests avec l'instruction aff, j'ai ajouté le flag -a (--aff).

==

J'ai corrigé l'erreur, elle dans la fonction decode_byte().
C'est encore le encod_byte dans le cas ou les arguments n'existent pas qui faisait une erreur
Du coup on sautait un st qui changeait le r2 alors qu'il était valide.
mea culpa

Il reste a continuer les tests de battle et à vérifier aff.

==

probleme corrigés:
	%IDX_MOD sur and, or et xor
	all->nb_live += 1 (même si le live est bidon)
	all->nb_checks >= MAX_CHECKS (dans manage_cycle)
	
==

J'ai rajoute un dossier champs a la base avec un script de test pour faire beaucoup de tests
Il y a des fails mais je crois que c'est juste une question de formatage quand il y a un gagnant

==

Ajout de 
void visu_print(t_all *all, char *format, ...) 
pour afficher sous l'arene avec un formatage a la printf
Exemple : visu_print(all, "salut les %s, il est %d:%d\n", "homos", 23, 42)

==

Visu :
Utiliser les fleches pour se deplacer entre les processus
page up, page down, home et end pour modifier la vitesse (seulement pendant une pause)

==

J'ai refais un run_battle.c a ma sauce pour corriger les erreurs de comportement.

Tu peux toujours utiliser ton fichier, je n'ai rien modifié.
	il faudra decommenté les init_pro_cycle() dans les forks

J'ai créé un fichier dump_cmp.sh qui fait des diff des dump de zaz et des notre
Il incremente le dump et fait des diff en boucle

ex : 'sh dump_cmp.sh 1000 10 Kittystrophic.cor ultima.cor' commence les boucles a partir de dump=100 et incrémente de 10

On peut changer l'incrémentation dans le fichier .sh

Le programme commence a se comporter correctement, il faut le tester en faisant des tests avec des champions differents, pour l'instant je n'ai testé qu'avec Kittystrophic.cor
