.name "st_test"
.comment "Test st _ place la valeur du reg (premier param) au deuxieme param (REG ou IND) "

get_nb:
	st		r1, 2054
	live	%0
