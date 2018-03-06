.name "Kids_1"
.comment "Kids_united_1"

	ld		%50,	r10
	fork	%:two
one:
	st		r1, 43
	ldi		%:jump, %5, r5
	and		r16, r16, r16
	zjmp	%:jump
two:
	ld		%4, r11
	ldi		%:jump, %9, r5
	and		r16, r16, r16
	zjmp	%:jump
jump:
	live	%0
	sti		r5, r10, r11
	zjmp	%45
