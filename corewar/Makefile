#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 00:00:01 by gmordele          #+#    #+#              #
#    Updated: 2018/02/01 19:15:42 by gmordele         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME			=	corewar

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -fsanitize=address

SRC				=	vm_0_main.c				\
					vm_1_get_params.c		\
					vm_2_get_champs.c		\
					vm_3_list_tools.c		\

OBJ				=	$(addprefix $(DEST_OBJ), $(SRC:%.c=%.o))

DEST_SRC		=	./src/

DEST_INC		=	./include/

DEST_OBJ		=	./obj/

HEADERS			=	$(DEST_INC) $(DEST_LIB)

DEST_LIB		=	../libft

LIBFT			=	$(DEST_LIB)/libft.a

all 			:	mklib $(NAME)

$(NAME)			:	$(DEST_OBJ) $(LIBFT) $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -I$(DEST_INC) -I$(DEST_LIB)

$(DEST_OBJ)%.o	:	$(DEST_SRC)%.c $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(DEST_INC) -I$(DEST_LIB)

$(DEST_OBJ)		:
	mkdir -p $(DEST_OBJ)

mklib			:
	make -C $(DEST_LIB)

clean			:
	make clean -C $(DEST_LIB)
	rm -rf $(DEST_OBJ)

fclean			:	clean
	make fclean -C $(DEST_LIB)
	rm -f $(NAME)

re				:	fclean all

.PHONY:all clean fclean re mklib mkdir_obj
