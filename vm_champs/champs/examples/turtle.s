.name "kek"
.comment "sas"

#aff
entry:
	sti			r1, %:zork, %1
	sti			r1, %:ardef, %1
	sti			r1, %:avdef, %1
	sti			r1, %:entry_l1, %1
	ld			%0, r16
	fork		%:zork

	ld			%439025904, r1
entry_l1: ld			%439025904, r1
live %42
xor r1, r2, r3
	ld			%0, r16
	fork		%:avdef

################################################################################

ardef:
	live		%42
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	st			r2, -400
	zjmp		%:ardef

################################################################################

zork:
	live		%42
	zjmp		%:zork

################################################################################

avdef:
	live		%42
	st			r3, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	st			r2, 400
	zjmp		%:avdef

################################################################################
