/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:25:04 by edebise           #+#    #+#             */
/*   Updated: 2017/11/25 19:25:23 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PF_H
# define FT_PF_H

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

# define PF_SIZE 400

typedef struct	s_pf
{
	va_list		va;
	char		buf[PF_SIZE + 100];
	int			buf_len;
	int			fd;
	char		*p1;
	char		*p2;
	int			hl;
	int			one;
	int			two;
	int			sharp;
	int			left;
	int			plus;
	int			space;
	int			zero;
	char		*s_pfx;
	char		*s_ptr;
	int			s_len;
	int			ret;
	char		*ret_s;
}				t_pf;

int				ft_pf(const char *restrict format, ...);
char			*ft_spf(const char *restrict format, ...);
int				pf(const char *restrict format, ...);
int				fpf(int fd, const char *restrict format, ...);
char			*spf(const char *restrict format, ...);
void			pf_begin(t_pf *o, char *format_dup, int fd);
void			pf_get_flag(t_pf *o);
void			pf_init_s(t_pf *o);
int				pf_buf_ncat(t_pf *o, char *s, char c, int n);
void			pf_buf_empty(t_pf *o, int fd);
void			pf_b(t_pf *o);
void			pf_bb(t_pf *o, char *ptr);
void			pf_c(t_pf *o, char c);
void			pf_lc(t_pf *o);
void			pf_d(t_pf *o);
void			pf_f(t_pf *o);
void			pf_o(t_pf *o);
void			pf_px(t_pf *o);
void			pf_s(t_pf *o, char *s, wchar_t *ws);
void			pf_ls(t_pf *o);
void			pf_u(t_pf *o);
void			pf_bdopux_hl(t_pf *o, int base);
void			pf_bdfopux_add(t_pf *o);
void			pf_utoa(unsigned long nb, int base, char *s);
char			*pf_unichar(unsigned int wc, char	*ptr);

#endif
