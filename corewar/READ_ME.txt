
J'ai regroupé certains fichiers qui se doublaient.

J'ai ajouté plusieurs chose dans la structure process.
	int	encoded
	int	decoded[]
	int	arg_size[]
	int	arg[]
	int	value[]

J'ai pu faire ma fonction 'vm_check_args()' qui check la validité de l'octet d'encodage,
	- si elle me renvoie 'valide' je récupere les valeurs dans process->value[] avec
	'vm_get_value()'
	- sinon, je quitte l'instruction

J'ai ajouté un tableau de pointeur de fonction pour appeler les instructions plus rapidement
