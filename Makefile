# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/30 12:28:57 by aldubar           #+#    #+#              #
#    Updated: 2021/07/26 11:25:43 by aldubar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO_DIR	=	./philo


all:
	@make -s -C $(PHILO_DIR)

clean:
	@make -s -C $(PHILO_DIR) clean

fclean:
	@make -s -C $(PHILO_DIR) fclean

re:	fclean all

check:	re
	@if [ ! -d philo_checker ]; then git clone https://github.com/busshi/philo_checker.git; fi
	@cd philo_checker && /bin/bash philo_checker.sh all


.PHONY:	all clean fclean re check
