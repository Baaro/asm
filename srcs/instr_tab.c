#include "asm.h"

t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	{T_DIR},												4,	live_compute},
	{"ld",		2,	{T_DIR | T_IND, T_REG},									4,	ld_compute},
	{"st",		3,	{T_REG, T_IND | T_REG},									4,	st_compute},
	{"add",		4,	{T_REG, T_REG, T_REG},									4,	add_compute},
	{"sub",		5,	{T_REG, T_REG, T_REG},									4,	sub_compute},	
	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	and_compute},
	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	or_compute},
	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4,	xor_compute},
	{"zjmp",	9,	{T_DIR},												2,	zjmp_compute},
	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2,	ldi_compute},
	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2,	sti_compute},
	{"fork",	12,	{T_DIR},												2,	fork_compute},
	{"lld",		13,	{T_DIR | T_IND, T_REG},									4,	lld_compute},
	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2,	lldi_compute},
	{"lfork",	15,	{T_DIR},												2,	lfork_compute},
	{"aff",		16,	{T_REG},												4,	aff_compute},
	{0, 		0,	{0}}
};
