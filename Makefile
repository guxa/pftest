# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 16:52:43 by jguleski          #+#    #+#              #
#    Updated: 2018/11/22 18:16:40 by jguleski         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror
LIB = libft/

LIBFT = get_next_line.c \
	  ft_strtolower.c ft_strrev.c ft_sortlist.c \
	  ft_lstmap.c ft_lstadd.c ft_lstiter.c ft_lstnew.c  \
	  ft_lstdel.c ft_lstdelone.c ft_strequ.c ft_strnequ.c \
	  ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
	  ft_strtrim.c ft_putendl.c ft_memalloc.c ft_strdel.c ft_strclr.c \
	  ft_strsub.c ft_strsplit.c ft_strncmp.c ft_strnstr.c \
	  ft_isascii.c ft_isalnum.c ft_isalpha.c ft_isprint.c \
	  ft_strrchr.c ft_strlcat.c ft_strncat.c \
	  ft_memcmp.c ft_memchr.c ft_memmove.c ft_memccpy.c \
	  ft_memcpy.c ft_bzero.c \
	  ft_putnbr.c \
	  ft_strstr.c \
	  ft_strjoin.c \
	  ft_atoi.c \
	  ft_strcat.c \
	  ft_putstr.c \
	  ft_putchar.c \
	  ft_strnew.c \
	  ft_itoa.c ft_isdigit.c ft_memset.c ft_strchr.c \
	  ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlen.c \
	  ft_strncpy.c ft_tolower.c ft_toupper.c \
	  ft_memdel.c \
	  b_printf.c bprintf_parser.c findarg.c \

PRINTF = ft_printf.c specifiers.c \
	  list_funcs.c parser.c utilities.c \
	  print_router.c number_handler.c number_flags.c \

INCLUDES = -I. -I$(LIB)includes

OBJECTS_DIR = objects/

OBJECTS_LIST = $(patsubst %.c, %.o, $(LIBFT))
OBJECTS	= $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

PF_OBJ_LIST = $(patsubst %.c, %.o, $(PRINTF))
PF_OBJ	= $(addprefix $(OBJECTS_DIR), $(PF_OBJ_LIST))

all: $(NAME)

$(NAME): $(OBJECTS_DIR) $(OBJECTS) $(PF_OBJ)
		@ar rc $(NAME) $(OBJECTS) $(PF_OBJ)
		@ranlib $(NAME)
		@echo "your lib is ready"

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "Compiling stuff.. you know how it goes..."

$(OBJECTS_DIR)%.o : %.c
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJECTS_DIR)%.o : $(LIB)%.c
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

debug:
		# gcc $(FLAGS) -g $(OBJECTS) $(PF_OBJ) -o test

clean:
		@rm -rf $(OBJECTS_DIR)
		@echo "Object files and objects directory deleted"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(NAME) deleted"

re: fclean all