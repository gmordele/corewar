# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edebise <edebise@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/10 18:42:46 by edebise           #+#    #+#              #
#    Updated: 2018/02/10 18:42:48 by edebise          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all		:
	make -C ./corewar
	make -C ./asm

corewar	:
	make -C ./corewar

asm		:
	make -C ./asm

clean	:
	make -C ./libft clean
	make -C ./corewar clean
	make -C ./asm clean

fclean	:
	make -C ./libft fclean
	make -C ./corewar fclean
	make -C ./asm fclean

re		:
	make -C ./libft re
	make -C ./corewar re
	make -C ./asm re

.PHONY:	all asm corewar clean fclean re
