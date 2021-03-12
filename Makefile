# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/28 20:51:01 by dtsyvin           #+#    #+#              #
#    Updated: 2018/12/28 20:51:03 by dtsyvin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CC := gcc

FLAGS := -Wall -Wextra -Werror -g
HEADERS := op asm
INCLUDES :=	includes
HFILES = $(patsubst %, $(INCLUDES)/%.h, $(HEADERS))

source_dirs :=	srcs

RM := rm -rf

LIBFT := libft/libft.a

RED = '\033[0;31m'
GR = '\033[0;32m'
NC = '\033[0m'

search_wildcards := $(addsuffix /*.c, $(source_dirs))

OBJ = $(notdir $(patsubst %.c, %.o, $(wildcard $(search_wildcards))))

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBFT)
	@echo "\033[092mAssembler has compiled successfully!\033[0m"

VPATH := $(source_dirs)

%.o: %.c $(HFILES)
	@$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $@

norm:
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette

fnorm: norm
	@make norm -C ./libft

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJ) $(OBJ_DIR)
	@rm -rf *.cor

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME) $(OBJ_DIR)

re: fclean all

.PHONY: clean fclean re all
