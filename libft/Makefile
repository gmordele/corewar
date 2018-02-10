#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 16:55:22 by gmordele          #+#    #+#              #
#    Updated: 2018/02/01 02:02:45 by gmordele         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME			=	libft.a

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra

SRC				=	ft_atoi.c				ft_bzero.c					ft_isalnum.c				\
					ft_isalpha.c			ft_isascii.c	    		ft_isdigit.c				\
					ft_isprint.c			ft_itoa.c					ft_memalloc.c				\
					ft_memccpy.c 			ft_memchr.c					ft_memcmp.c					\
					ft_memcpy.c				ft_memdel.c					ft_memmove.c				\
					ft_memset.c				ft_putchar.c				ft_putchar_fd.c				\
					ft_putendl.c			ft_putendl_fd.c 			ft_putnbr.c					\
					ft_putnbr_fd.c			ft_putstr.c					ft_putstr_fd.c				\
					ft_strcat.c 			ft_strchr.c					ft_strclr.c					\
					ft_strcmp.c				ft_strcpy.c					ft_strdel.c					\
					ft_strdup.c				ft_strequ.c					ft_striter.c				\
					ft_striteri.c			ft_strjoin.c 				ft_strlcat.c				\
					ft_strlen.c				ft_strmap.c					ft_strmapi.c				\
					ft_strncat.c 			ft_strncmp.c				ft_strncpy.c				\
					ft_strnequ.c			ft_strnew.c					ft_strnstr.c				\
					ft_strrchr.c			ft_strsplit.c				ft_strstr.c					\
					ft_strsub.c				ft_strtrim.c 				ft_tolower.c				\
					ft_toupper.c			ft_lstnew.c					ft_lstdelone.c				\
					ft_lstdel.c 			ft_lstadd.c					ft_lstiter.c				\
					ft_lstmap.c				ft_putnbr_base_fd.c			ft_putnbr_base.c			\
					get_next_line.c 		ft_atoi_base_fwd.c 			free_string_arr.c  			\
					ft_printf.c				parse_conv_spec.c			ft_strcpy.c					\
					handle.c				ft_strequ.c					ft_strlen.c					\
					ft_putstr.c				decimal_itoa.c				long_decimal_itoa.c			\
					llong_decimal_itoa.c	handle_decimal_int.c		handle_unsigned_int.c		\
					handle_octal.c			handle_udecimal.c			handle_hex.c				\
					octal_itoa.c			ulong_octal_itoa.c			ullong_octal_itoa.c			\
					hex_itoa.c				ulong_hex_itoa.c			ullong_hex_itoa.c			\
					handle_pointer.c		pointer_itoa.c				udec_itoa.c					\
					ulong_udec_itoa.c		ullong_udec_itoa.c			handle_char.c				\
					buff_char.c				buff_wchar.c				handle_string.c				\
					buff_strwch.c			buff_string.c				ft_strdup.c					\
					buff.c					ft_strnequ.c				handle_color.c				\
					print_col.c				handle_bin.c				bin_itoa.c					\
					ulong_bin_itoa.c		ullong_bin_itoa.c 			ft_isspace.c				\
					skip_spaces.c			skip_word.c					ft_strndup.c				\
					ft_strjoinfree.c		ft_dprintf.c				btree_create_node.c			\
					btree_apply.c			btree_insert_data.c			btree_free.c				\
					free_gnl_lst.c

DEST_SRC		=	./src/

DEST_OBJ		=	./obj/

OBJ				=	$(addprefix $(DEST_OBJ), $(SRC:%.c=%.o))

HEADERS			=	libft.h ft_printf.h

all				: $(NAME)

test      :
	echo $(OBJ)

$(NAME)			: $(DEST_OBJ) $(OBJ) $(DEST_INC)
	ar rcs  $(NAME) $(OBJ)

$(DEST_OBJ)%.o	: $(DEST_SRC)%.c $(DEST_INC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I.

$(DEST_OBJ)		:
	mkdir -p $(DEST_OBJ)

clean 			:
	rm -rf $(DEST_OBJ)

fclean 			: clean
	rm -f $(NAME)

re 				: fclean all

.PHONY:all clean fclean re
