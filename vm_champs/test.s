.name "Test"
.comment "Test"

	sub		r2, r1, r10
	sti		r10, 0, %64
	live	%-1;

#lbl0:
	#ld		1, r2
	#lld		1, r2
	#lldi		0, %2049, r2
	#sti		r2, 0, %64
