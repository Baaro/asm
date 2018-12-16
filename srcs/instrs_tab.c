#include "asm.h"

const t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	{T_DIR},												false, 4},
	{"ld",		2,	{T_DIR | T_IND, T_REG},									true, 4},
	{"st",		3,	{T_REG, T_IND | T_REG},									true, 4},
	{"add",		4,	{T_REG, T_REG, T_REG},									true, 4},
	{"sub",		5,	{T_REG, T_REG, T_REG},									true, 4},	
	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	true, 4},
	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	true, 4},
	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	true, 4},
	{"zjmp",	9,	{T_DIR},												false, 2},
	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			true, 2},
	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			true, 2}, 
	{"fork",	12,	{T_DIR},												false, 2},
	{"lld",		13,	{T_DIR | T_IND, T_REG},									true, 4},
	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			true, 2},
	{"lfork",	15,	{T_DIR},												false, 2},
	{"aff",		16,	{T_REG},												false, 4},
	{0, 		0,	{0}}
};
