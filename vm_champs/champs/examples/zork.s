								.name "zork"					 ;test
.comment "I'M ALIIIIVE"

#l1: 	sti r1, %:live, %1	# 7 bytes

	l*3:
#



l2:
		sti r1,%:live,%1 	; 7 bytes
		and r1, %0, r1 		# 8 bytes

live:	live %1				# 5 bytes
		zjmp %:live			# 3 bytes
