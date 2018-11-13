# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 16:11:31 by dtsyvin           #+#    #+#              #
#    Updated: 2018/11/07 16:46:23 by dtsyvin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
# FILENAMES =
HEADERS = corewar
SRCDIR = ./src
HDRDIR = ./includes
ODIR = ./obj
#CFILES = $(patsubst %, $(SRCDIR)/%.c, $(FILENAMES))
#OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))
CFILES = $(patsubst %, %, $(wildcard $(addsuffix /*.c, $(SRCDIR))))
OFILES = $(patsubst $(SRCDIR)/%.c, $(ODIR)/%.o, $(wildcard $(addsuffix /*.c, $(SRCDIR))))
HFILES = $(patsubst %, $(HDRDIR)/%.h, $(HEADERS))
LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
LIBHDRDIR = $(LIBDIR)/includes
FLAGS = -Wall -Wextra -Werror -O3

RED = '\033[0;31m'
GR = '\033[0;32m'
NC = '\033[0m'

all: $(NAME)

$(NAME): $(ODIR) $(HFILES) $(OFILES) $(LIBFT)
	@gcc $(FLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo ${GR}"================= $(NAME) is up to date. ================="${NC}

$(ODIR)/%.o: $(SRCDIR)/%.c
	@gcc $(FLAGS) -o $@ -c $< -I$(HDRDIR) -I$(LIBHDRDIR)

$(ODIR):
	@mkdir -p $(ODIR)

$(LIBFT):
	@make -C $(LIBDIR)

norm:
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette $(CFILES) $(HFILES)

fnorm: norm
	@make norm -C ./libft

echo:
	@echo $(HFILES)
	@echo $(HEADERS)
	@echo $(HDRDIR)

clean:
	@rm -Rf $(ODIR)
	@make clean -C $(LIBDIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBDIR)

re: fclean all
