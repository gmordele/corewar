.name "Test"
.comment "Test"

	#and	%16843009, %16843009, r10
lbl0:
	lldi	%1, %1, r10
	and	%1, 1, r10
	sti	r10, %64, %0
	zjmp	%:lbl0
