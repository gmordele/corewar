.name "sti_test"
.comment "Test sti _ place la valeur du reg a l'adresse de la somme des deux autres params"

get_nb:
	sti		r1, %2147422207, %1
live:
	live	%0
