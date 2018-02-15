.name "ld"
.comment "Test ld _ modifie le carry si le param vaut 0"

get_nb:
	ld		%0, r2
	st		r1, 6
live:
	live	%0
	zjmp	%:live
