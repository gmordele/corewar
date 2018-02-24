
J'ai refais un run_battle.c a ma sauce pour corriger les erreurs de comportement.

Tu peux toujours utiliser ton fichier, je n'ai rien modifié.
	il faudra decommenté les init_pro_cycle() dans les forks

J'ai créé un fichier dump_cmp_1.sh qui fait des diff des dump de zaz et des notre
Il incremente le dump et fait ds diff en boucle

ex : 'sh dump_cmp_1.sh 100 Kittystrophic.cor test.cor' commence les boucles a partir de dump=100

On peut changer l'incrémentation dans le fichier .sh

Le programme commence a se comporter correctement, il faut le tester en faisant des tests avec des champions differents, pour l'instant je n'ai testé qu'avec Kittystrophic.cor
