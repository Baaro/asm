.name "zork" #test	                                                                                                                    
.comment "I'M ALIIIIVE"	;test

###	size: 7b,		pos: 0b + 0b = 0b,		ref: 15b - 0b = 15b;	// instr: 0x0b args: 0110 1000
	l2:
	l3:		sti r17	, %:live, %1# 4 args
	l3:		sti r1 ,%:live, %1			#
# live:
# live2:
# live3:
###	size: 8b,		pos: 0b + 7b = 7b;								// instr: 0x06 args: 0110 0100
	and r1, %0, r1
	aff r1
###	size: 5b,		pos: 8b + 7b = 15b; 							// instr: 0x01
	# l3:
	live: live %4294967295
###	size: 3b,		pos: 5b + 15b = 20b,	ref: 15b - 20b = -5b.	// instr: 0x09
	zjmp %:live
#live:

# pos_cur = pos_prev + size_prev;
# ref = label_pos - ref_pos;
# size = instr_code + args1_size + args2_size + args3_size;
#	ld			%439025904,,,,,,, r1
#.comment	"TURTLE 



#"
#.name 		"tu
			#asdasd
#a
#rt
#le
#"