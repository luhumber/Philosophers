# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luhumber <luhumber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 17:38:31 by lucas             #+#    #+#              #
#    Updated: 2023/06/07 11:21:26 by luhumber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread

LIST_OBJS = $(SRCS:.c=.o)

DIR_OBJS = .objs/

SRCS = 	main.c \
		utils.c \
		philo.c \
		display.c \
		

OBJS = $(addprefix $(DIR_OBJS), $(LIST_OBJS))
HEADERS = ../include/philo.h

all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS) $(HEADERS)
	cc $(OBJS) -o $(NAME) -lpthread #-fsanitize=thread
	echo "\033[1;33mCompilation terminée 💥\033[0m";
	

$(DIR_OBJS)%.o: %.c  $(HEADERS) Makefile 
		@cc $(CFLAGS) -c $< -o $@ -I.

clean:
	@rm -f $(OBJS_BONUS)
	@rm -rf $(DIR_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS)