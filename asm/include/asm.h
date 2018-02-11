/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:19:23 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 05:00:12 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_ASM_H
# define DEF_ASM_H

typedef struct	s_token
{
	int		type;
	int		row;
	int		col;
	int		int_val;
	char	*str_val;
}				t_token;

typedef struct	s_data
{
	int		fd;
}				t_data;

# define TOK_ENDLINE			1
# define TOK_END				2
# define TOK_COMMAND_NAME 		3
# define TOK_COMMAND_COMMENT	4
# define TOK_STRING				5
# define TOK_SEPARATOR			6
# define TOK_LABEL				7
# define TOK_INSTRUCTION		8
# define TOK_INDIRECT			9
# define TOK_REGISTER			10
# define TOK_INDIRECT_LABEL		11
# define TOK_DIRECT_LABEL		12
# define TOK_DIRECT				13

# define MAX_FILE_SIZE			1000000

void 			err_exit(t_data *data);
void 			err_exit_str(char *str, t_data *data);
void 			err_exit_strerror(char *str, t_data *data);
char			*get_file_content(char *file, t_data *data);
t_token			*get_next_token(int fd, t_data *data);
t_token			*new_token(int type, int row, int col, t_data *data);
t_token			*token_string(char **str, int *i, int *row, t_data *data);
void			free_token(t_token *token);
t_token			*get_token(char **str, int *i, int *row, t_data *data);
void			print_token(int fd, t_token *token);
void			free_data(t_data *data);
t_token			*token_instr_lab(char **str, int *i, int *row, t_data *data);
t_token			*token_indirect(char **str, int *i, int *row, t_data *data);
t_token			*token_register(char **str, int *i, int *row, t_data *data);
t_token			*token_direct(char **str, int *i, int *row, t_data *data);

#endif
