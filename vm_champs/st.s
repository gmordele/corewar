.name "st_test"
.comment "Test st _ place la valeur du reg (premier param) au deuxieme param (REG ou IND) "

get_nb:
	st		r1, r2
	st		r2, 0
