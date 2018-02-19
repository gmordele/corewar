.name "And"
.comment "Test and"

	and	%1, %3, r10
	sti	r10, %64, %0
	live %0
	live %0
	live %0
	live %0
