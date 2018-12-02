#include <stdio.h>
#include <stdint.h>
#include <string.h>
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define NUM_INSTRUCTIONS		16


int live_compute(char *str)
{
	return (1);
}

t_instr    g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	{T_DIR},												4},
	{"ld",		2,	{T_DIR | T_IND, T_REG},									4},
	{"st",		3,	{T_REG, T_IND | T_REG},									4},
	{"add",		4,	{T_REG, T_REG, T_REG},									4},
	{"sub",		5,	{T_REG, T_REG, T_REG},									4},	
	{"and",		6,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"or",		7,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"xor",		8,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	4},
	{"zjmp",	9,	{T_DIR},												2},
	{"ldi",		10,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
	{"sti",		11,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			2},
	{"fork",	12,	{T_DIR},												2},
	{"lld",		13,	{T_DIR | T_IND, T_REG},									4},
	{"lldi", 	14,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			2},
	{"lfork",	15,	{T_DIR},												2},
	{"aff",		16,	{T_REG},												4},
	{0, 		0,	{0}
};

t_instr 	g_instrs_tab[NUM_INSTRUCTIONS + 1] =
{
	{"live",	1,	{T_DIR},												4,	live_token},
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

int		main(void)
{
	int test[2];

	test[0] = 1 | 2;
	test[1] = 5;

	int i = -1;
	char	*str = "lve";
	int		byte_code  = 0;

	while (g_instrs_tab[++i].name)
	{
		if (strcmp(str, g_instrs_tab[i].name) == 0)
			if ((token = g_instrs_tab[i].make_token(str, counter)))
				break ;
		// printf("|%s\t{%hhu, %hhu, %hhu}, %zu|", g_instrs_tab[i].name, g_instrs_tab[i].args[0],
																// g_instrs_tab[i].args[1],
																// g_instrs_tab[i].args[2],
																// g_instrs_tab[i].label_size);
		// printf("\n---------------------\n");
	}
	printf("byte: %d\n", byte_code);
	return (0);
}
