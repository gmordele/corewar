.name "Kids_2"
.comment "Kids_united_2"

	st		r1, 6
	live	%0
	ld		%480,	r10
	fork	%:two
	fork	%:four
one:
	st		r1, 95
	ldi		%:jump, %-2, r5
	and		r16, r16, r16
	zjmp	%:jump
two:
	fork	%:three
	ld		%4, r11
	ldi		%:jump, %2, r5
	and		r16, r16, r16
	zjmp	%:jump
three:
	ld		%8, r11
	ldi		%:jump, %6, r5
	and		r16, r16, r16
	zjmp	%:jump
four:
	ld		%12, r11
	ldi		%:jump, %10, r5
	and		r16, r16, r16
	zjmp	%:jump
	live	%3855
jump:
	live	%0
	sti		r5, r10, r11
	zjmp	%477
