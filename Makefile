NAME = asm

CC := gcc

# FLAGS := -Wall -Wextra -Werror -g

INCLUDES :=	includes					\

source_dirs :=	srcs					\

# OBJ_DIR := objs

RM := rm -rf

LIBFT := libft/libft.a

search_wildcards := $(addsuffix /*.c, $(source_dirs))

OBJ = $(notdir $(patsubst %.c, %.o, $(wildcard $(search_wildcards))))

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(FLAGS) -o $@ $(OBJ) $(LIBFT)

VPATH := $(source_dirs)

%.o: %.c
	# $(CC) $(FLAGS) -c $(addprefix -I $(INCLUDES), $(source_dirs)) $<
	$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $@
	
clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(OBJ_DIR)

re: fclean all

.PHONY: clean fclean re all