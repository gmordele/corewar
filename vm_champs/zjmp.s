.name "zjmp"
.comment "Test zjmp _ jump uniquement si carry vaut 1"

get_nb:
	sub		r1, r1, r2
	st		r1, 6
live:
	live	%0
	zjmp	%:live
