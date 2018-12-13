.name "zork" #test	                                                                                                                    
.comment "I'M ALIIIIVE"	;test

l2:

l3:		sti r1, %:live, %1 	#	size: 7b,		pos: 0b + 0b = 0b,		ref: 15b - 0b = 15b;	// 0110 1000
		and r1, %0, r1 		#	size: 8b,		pos: 7b + 0b = 7b;								// 0110 0100
l3:
live:	live %1				#	size: 5b,		pos: 8b + 7b = 15b;
		zjmp %:live			#	size: 3b,		pos: 5b + 15b = 20b,	ref: 15b - 20b = -5b.

# pos_cur = pos_prev + size_prev;
# ref = label_pos - ref_pos;
# size = instr_code + args1_size + args2_size + args3_size;

# sti r1, :live, %1
#         ^ -> ERROR; // wrong argument

#valid_token:
#		valid instruction:
#			get byte code of this instruction
#			while arguments exist
#				if current argument valid
#					get byte code of this argument
#				else
#					show error
