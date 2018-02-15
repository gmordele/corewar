.name "fork"
.comment "Test fork _ "

get_nb:
	sti		r1, %:live0, %1
	sti		r1, %:live1, %1
	ld		%0, r2
	fork	%:live1
live0:
	live	%0
	zjmp	%:live0
live1:
	live	%0
	zjmp	%:live1
