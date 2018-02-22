# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 00:00:01 by gmordele          #+#    #+#              #
#    Updated: 2018/02/21 19:32:25 by proso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	corewar

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -fsanitize=address

SRC				=	vm_0_main.c					\
					vm_1_get_params.c			\
					vm_2_get_champs.c			\
					vm_3_set_match.c			\
					vm_4_run_battle.c			\
					vm_5_process_tools.c		\
					vm_5_op_tools.c				\
					vm_5_mem_tools.c			\
					vm_instructions.c			\
					vm_live_zjmp_aff.c			\
					vm_ld_lld_ldi_lldi.c		\
					vm_st_sti_fork_lfork.c		\
					vm_add_sub_and_or_xor.c		\
					op.c						\

OBJ				=	$(addprefix $(DEST_OBJ), $(SRC:%.c=%.o))

DEST_SRC		=	./src/

DEST_INC		=	./include/

DEST_OBJ		=	./obj/

HEADERS_INC		=	op.h		vm_0.h

HEADERS			=	$(addprefix $(DEST_INC), $(HEADERS_INC)) $(DEST_LIB)/libft.h

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

.PHONY:all clean fclean re mklib
