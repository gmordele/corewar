.name "aff_test"
.comment "Test aff"

	ld	%65, r1
	add r2, r3, r4
aff:
	aff	r1
	zjmp %:aff
