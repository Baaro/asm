# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/02 21:11:22 by dtsyvin           #+#    #+#              #
#    Updated: 2018/09/30 14:33:11 by dtsyvin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -O3
HDRDIR = ./includes
HEADERS = libft get_next_line ft_printf
SRCDIR = ./src

CALCDIR = calc_func
CALCFUNC = ft_max \
			ft_min
FCALCFUNC = $(patsubst %, $(CALCDIR)/%, $(CALCFUNC))

CHARDIR = char_func
CHARFUNC = ft_tolower \
			ft_toupper \
			ft_wcharlen \
			ft_wstrlen
FCHARFUNC = $(patsubst %, $(CHARDIR)/%, $(CHARFUNC))

GNLDIR = gnl
GNLFUNC = get_next_line
FGNLFUNC = $(patsubst %, $(GNLDIR)/%, $(GNLFUNC))

LOGICALDIR = logical_func
LOGICALFUNC = ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_islower \
			ft_isprint \
			ft_isupper
FLOGICALFUNC = $(patsubst %, $(LOGICALDIR)/%, $(LOGICALFUNC))

LSTDIR = lst_func
LSTFUNC = ft_lstadd \
			ft_lstaddback \
			ft_lstdel \
			ft_lstdelone \
			ft_lstiter \
			ft_lstlen \
			ft_lstmap \
			ft_lstmerge \
			ft_lstnew \
			ft_lstrev \
			ft_lstsort
FLSTFUNC = $(patsubst %, $(LSTDIR)/%, $(LSTFUNC))

MEMDIR = mem_func
MEMFUNC = ft_bzero \
			ft_memalloc \
			ft_memccpy \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memdel \
			ft_memmove \
			ft_memset
FMEMFUNC = $(patsubst %, $(MEMDIR)/%, $(MEMFUNC))

PRINTFDIR = print_func/ft_printf
PRINTFFUNC = ft_parse \
			ft_printf \
			hard \
			print_numbers_i \
			print_numbers_x \
			print_strings
FPRINTFFUNC = $(patsubst %, $(PRINTFDIR)/%, $(PRINTFFUNC))

PRINTDIR = print_func
PRINTFUNC = ft_putchar \
			ft_putchar_fd \
			ft_putendl \
			ft_putendl_fd \
			ft_putnbr \
			ft_putnbr_fd \
			ft_putstr \
			ft_putstr_fd
FPRINTFUNC = $(patsubst %, $(PRINTDIR)/%, $(PRINTFUNC))

SPLITDIR = split
SPLITFUNC = ft_arrdel \
			ft_strsort \
			ft_strsplit
FSPLITFUNC = $(patsubst %, $(SPLITDIR)/%, $(SPLITFUNC))

STRDIR = str_func
STRFUNC = ft_atoi \
			ft_itoa \
			ft_strcat \
			ft_strchr \
			ft_strclr \
			ft_strcmp \
			ft_strcpy \
			ft_strdel \
			ft_strdup \
			ft_strequ \
			ft_striter \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlen \
			ft_strmap \
			ft_strmapi \
			ft_strncat \
			ft_strnchr \
			ft_strncmp \
			ft_strncpy \
			ft_strnequ \
			ft_strnew \
			ft_strnstr \
			ft_strrchr \
			ft_strstr \
			ft_strsub \
			ft_strtrim
FSTRFUNC = $(patsubst %, $(STRDIR)/%, $(STRFUNC))

FILENAMES = $(FCALCFUNC) \
			$(FCHARFUNC) \
			$(FGNLFUNC) \
			$(FLOGICALFUNC) \
			$(FLSTFUNC) \
			$(FMEMFUNC) \
			$(FPRINTFUNC) \
			$(FPRINTFFUNC) \
			$(FSPLITFUNC) \
			$(FSTRFUNC)

ODIR = ./obj
CFILES = $(patsubst %, $(SRCDIR)/%.c, $(FILENAMES))
OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))
HFILES = $(patsubst %, $(HDRDIR)/%.h, $(HEADERS))

RED = '\033[0;31m'
GR = '\033[0;32m'
NC = '\033[0m'

all: $(NAME)

$(NAME): $(ODIR) $(OFILES) $(HFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo ${GR}"================= $(NAME) is up to date. ================="${NC}

$(ODIR)/%.o: $(SRCDIR)/%.c
	@gcc $(FLAGS) -o $@ -c $< -I $(HDRDIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(CALCDIR)
	@mkdir -p $(ODIR)/$(CHARDIR)
	@mkdir -p $(ODIR)/$(GNLDIR)
	@mkdir -p $(ODIR)/$(LOGICALDIR)
	@mkdir -p $(ODIR)/$(LSTDIR)
	@mkdir -p $(ODIR)/$(MEMDIR)
	@mkdir -p $(ODIR)/$(PRINTFDIR)
	@mkdir -p $(ODIR)/$(SPLITDIR)
	@mkdir -p $(ODIR)/$(STRDIR)

norm:
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette $(CFILES) $(HFILES)

clean:
	@/bin/rm -Rf $(ODIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
