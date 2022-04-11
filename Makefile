# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 14:45:19 by jroux-fo          #+#    #+#              #
#    Updated: 2022/04/11 17:20:44 by jroux-fo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_FILES	=	main.c			\
				ft_atoi.c		\
				ft_init.c		\
				ft_utils.c		\
				ft_error.c		\
				ft_print.c		\
				ft_clean.c		\
				ft_routine.c	\

FLAGS = -Wall -Werror -Wextra -g3 -pthread

INCLUDES = header

PATH = srcs

OBJ_DIR = obj

OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRCS_FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATH)/%.c
	@$(shell mkdir -p $(OBJ_DIR))
	@printf "Compiling $< ...\n"
	@$(shell gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@)

$(OBJ_DIR)/%.o: $(PATH)/%.c
	@$(shell mkdir -p $(OBJ_DIR))
	@printf "Compiling $< ...\n"
	@$(shell gcc $(FLAGS) -g3 -I $(INCLUDES) -c $< -o $@)

$(NAME): $(OBJ_FILES)
	@$(shell gcc $(FLAGS) -I $(INCLUDES) $(OBJ_FILES) -o $(NAME))
	@printf "Executable $@ created !\n"

clean:
	@printf "Deleting objects\n"
	@$(shell rm -rf $(OBJ_DIR))

fclean: clean
	@printf "Deleting executable\n"
	@$(shell rm -rf $(NAME))
	
re: fclean all

.PHONY:		all clean fclean re