# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 19:42:17 by vsokolog          #+#    #+#              #
#    Updated: 2017/12/16 17:32:41 by vsokolog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC := gcc
FLAGS := -Wall -Wextra -Werror -g

INCLUDES := includes/
source_dirs := .									\
srcs/convert_to/									\
srcs/is_ascii										\
srcs/lst											\
srcs/mem											\
srcs/put											\
srcs/str											\
srcs/is_dir_file									\
srcs/convert_to										\
srcs/swap_bytes										\
srcs/get_next_line									\
srcs/ft_printf										\
srcs/ft_printf/auxiliary							\
srcs/ft_printf/form									\
srcs/ft_printf/parsing								\
srcs/ft_printf/form/form_num						\
srcs/ft_printf/form/form_num/get_num				\
srcs/ft_printf/form/form_str_char					\
srcs/ft_printf/form/form_str_char/form_unicode		\

MAKE := make
RM := rm -rf

RED = '\033[0;31m'
GR = '\033[0;32m'
NC = '\033[0m'

search_wildcards := $(addsuffix /*.c, $(source_dirs))

OBJ = $(notdir $(patsubst %.c, %.o, $(wildcard $(search_wildcards))))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "\033[092mLibft has compiled successfully!\033[0m"

VPATH := $(source_dirs)

%.o: %.c
	@$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $@

norm:
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
