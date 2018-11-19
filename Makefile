# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 16:52:43 by jguleski          #+#    #+#              #
#    Updated: 2018/11/18 17:15:59 by jguleski         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
LIBFT = libft
FLAGS = -Wall -Wextra -Werror

LIB = $(LIBFT)/libft.a

SRC = ft_printf.c specifiers.c \
	  list_funcs.c parser.c utilities.c \
	  print_router.c number_handler.c number_flags.c

INCLUDES = -I. -I$(LIBFT)/includes/

OBJECTS_DIR = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC))
OBJECTS	= $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

LIBFT_OBJ = libft/objects

all: $(NAME)

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "Directory objects was created"

$(OBJECTS_DIR)%.o : %.c
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIB):
		@make -C $(LIBFT)

$(NAME): $(OBJECTS_DIR) $(OBJECTS) $(LIB) $(LIBFT_OBJ)
		@ar rc $(NAME) $(OBJECTS) $(LIBFT_OBJ)/*.o
		@ranlib $(NAME)
		@echo "your lib is ready"

$(LIBFT_OBJ):
		make -C $(LIBFT)

debug: $(SRC) $(LIB)
		gcc $(FLAGS) -g $(INCLUDES) $(SRC) main.c $(LIB) -o test-$(NAME)

test:	$(OBJECTS)
		gcc $(OBJECTS) $(LIB) tests/main.c -o tests/a.out

clean:
		make -C $(LIBFT) clean
		@rm -rf $(OBJECTS_DIR)

fclean:	clean
		rm -f $(NAME)
		@make -C $(LIBFT) fclean

re: fclean all
