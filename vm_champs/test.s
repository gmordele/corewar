.name           "42"
.comment        "Just a basic Winner Program"

entree:
	live	%42	# entree
test:	
sti	r10,%-510,r2
test1:	
fork	%:entree
fork	%:test
fork	%:test3	
test3:	
sti	r10,%-510,r2	
