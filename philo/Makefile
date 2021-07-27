# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/09 11:58:23 by aldubar           #+#    #+#              #
#    Updated: 2021/07/25 18:57:50 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	main.c init.c init_philo.c event.c display.c utils.c free.c exit.c

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

INC_DIR	=	./includes

CC	=	@clang

CFLAGS	=	-Wall -Wextra -Werror -g

OK	=	"\r[ \033[0;32mok\033[0m ]"

RM	=	@rm -f

.c.o:
		$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(INC_DIR)/philo.h
		@echo "[....] Compiling $(NAME)\c"
		$(CC) $(CFLAGS) $(OBJS) -pthread -o $@
		@echo $(OK)

all:		$(NAME)

clean:
		@echo "[....] Removing $(NAME) objects\c"
		$(RM) $(OBJS)
		@echo $(OK)

fclean:		clean
		@echo "[....] Removing $(NAME)\c"
		$(RM) $(NAME)
		@echo $(OK)

test:		$(NAME)
		@echo "\033[0;33mRunning philo_checker...\033[0m"
		@bash philo_checker.sh

re:		fclean all

.PHONY:		all clean fclean re
