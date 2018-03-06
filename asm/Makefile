#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 00:00:01 by gmordele          #+#    #+#              #
#    Updated: 2018/03/06 16:54:52 by gmordele         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME			=	asm

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra

SRC				=	main.c					err_exit.c			\
					get_next_token.c		get_statements.c	\
					get_token.c				print_token.c		\
					get_token1.c			get_token2.c		\
					get_token_string.c		op.c				\
					get_header.c			syntax_error.c		\
					pass_endl_token.c		statement_lst.c		\
					get_parameter.c			get_parameter1.c	\
					reverse_endian.c		get_offsets.c		\
					get_write_buf.c			write_buf_label.c	\
					write_buf_dir_indir.c	write_buf.c			\
					free_token.c

OBJ				=	$(addprefix $(DEST_OBJ), $(SRC:%.c=%.o))

DEST_SRC		=	./src/

DEST_INC		=	./include/

DEST_OBJ		=	./obj/

HEADERS_INC		=	asm.h		op.h

HEADERS			=	$(addprefix $(DEST_INC), $(HEADERS_INC))  $(DEST_LIB)/libft.h

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
	rm -rf $(DEST_OBJ)

fclean			:	clean
	rm -f $(NAME)

re				:	fclean all

.PHONY:all clean fclean re mklib
