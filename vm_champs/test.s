.name "Test"
.comment "Test"

	#and	%16843009, %16843009, r10
lbl0:
	#ld		1, r2
	#lld		1, r2
	lldi		0, %2049, r2
	sti		r2, 0, %64
