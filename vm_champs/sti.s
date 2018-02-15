.name "sti"
.comment "Test sti _ place la valeur du reg a l'adresse de la somme des deux autres params"

get_nb:
	sti		r1, %:live, %1
	ld		%0, r2
live:
	live	%0
	zjmp	%:live
