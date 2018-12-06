.name "asd"
.comment "I'M ALIIIIVE"  ;test

l2:

l3:sti r1,%:live, %1 	 ;7 bytes
		and r1, %0, r1 		# 8 bytes

live:	live %1				# 5 bytes
		zjmp %:live			# 3 bytes
