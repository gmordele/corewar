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

.PHONY:	all asm corewar clean fclean
