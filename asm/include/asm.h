/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:19:23 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/17 02:14:45 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_ASM_H
# define DEF_ASM_H

# include "op.h"

typedef struct	s_token
{
	int		type;
	int		row;
	int		col;
	int		int_val;
	char	*str_val;
}				t_token;

typedef struct	s_get_string
{
	int		end;
	int		begin;
	int		n_row;
	char	*ret;
}				t_get_string;

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

typedef int		t_offset;

typedef struct	s_param
{
	int		type;
	char	*value;
}				t_param;

typedef struct	s_instruction
{
	int				type;
	t_op			*op_instruc;
	t_param			param[3];
	char			*write_buf;
	t_offset		offset;
	t_offset		size;
}				t_instruction;

typedef struct	s_label
{
	int				type;
	t_offset		offset;
	char			*name;
}				t_label;

typedef union	u_statement
{
	int				type;
	t_instruction	instruction;
	t_label			label;
}				t_statement;

typedef struct	s_statement_lst
{
	t_statement				statement;

	struct s_statement_lst	*next;
}				t_statement_lst;

# define LABEL			1
# define INSTRUCTION	2

typedef struct	s_data
{
	int					fd;
	char				*file_name;
	char				*new_file_name;
	char				*str;
	t_header			header;
	t_statement_lst		*statement_lst;
}				t_data;

void			err_exit(t_data *data);
void			err_exit_str(char *str, t_data *data);
void			err_exit_strerror(char *str, t_data *data);
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
void			get_header(int fd, t_data *data);
void			syntax_error(t_token *token, t_data *data);
t_token			*pass_endl_token(int fd, t_data *data);
void			get_statements(int fd, t_data *data);
void			statement_lst_add(t_statement_lst *statement, t_data *data);
void			statement_lst_free(t_data *data);
void			get_parameter(t_token *token, t_instruction *stat_instruct,
							int i, t_data *data);
char			*param_type_str(t_token *token);
int				is_parameter(int type);
void			invalid_instruction(t_token *token, t_data *data);
void			free_parameters(int i, t_instruction *state_instruct);
int				reverse_endian_int(int n);
short			reverse_endian_short(short n);
void			get_offsets(t_data *data);
void			get_write_buf(t_data *data);
void			write_buf_label(int *i, int j, t_instruction instruction,
								t_data *data);
int				reverse_endian_int(int	n);
short			reverse_endian_short(short n);
void			write_buf_dir_indir(int *i, int j, t_instruction instruction);
void			write_buf(int fd, t_data *data);
t_token			*get_next_token_no_exit(int fd, t_data *data);

#endif
