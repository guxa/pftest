# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguleski <jguleski@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 16:52:43 by jguleski          #+#    #+#              #
#    Updated: 2018/11/14 18:00:42 by jguleski         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ftprintf
LIBFT = libft
FLAGS = -Wall -Wextra #-Werror

LIB = $(LIBFT)/libft.a

SRC = ft_printf.c specifiers.c \
	  list_funcs.c parser.c utilities.c \
	  print_router.c number_handler.c

INCLUDES = -I. -I$(LIBFT)/includes/

OBJECTS_DIR = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC))
OBJECTS	= $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

all: $(NAME)

# $(NAME): $(LIB) $(OBJECTS_DIR) $(OBJECTS)
# 	 gcc $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIB) -o $(NAME)

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "Directory objects was created"

$(OBJECTS_DIR)%.o : %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIB):
		@make -C $(LIBFT)

debug: $(SRC) $(LIB)
		gcc $(FLAGS) -g $(INCLUDES) $(SRC) $(LIB) -o test-$(NAME)

test:	$(OBJECTS)
		gcc $(OBJECTS) $(LIB) tests/main.c -o tests/a.out

clean:
		#make -C $(LIBFT) clean
		@rm -rf $(OBJECTS_DIR)

fclean:	clean
		rm -f $(NAME)
		@make -C $(LIBFT) fclean

re: fclean all

$(NAME): $(OBJECTS_DIR) $(OBJECTS) $(LIB)
		@ar rc libftprintf.a $(OBJECTS) libft/objects/*.o
		@ranlib libftprintf.a
		@echo "your lib is ready"
