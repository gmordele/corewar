.name "aff_test"
.comment "Test aff"

	live	%0
	ld		%0, r1
	ld		%1, r2
while:
	st		r1, 128
	aff		r1
	add		r1, r2, r1
	and		r10, r10, r10
	zjmp	%:while
