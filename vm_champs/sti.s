.name "sti_test"
.comment "Test sti _ place la valeur du reg a l'adresse de la somme des deux autres params"

get_nb:
	sti		r1, 1, %0
live:
	live	%0
