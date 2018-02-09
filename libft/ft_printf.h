/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:59:11 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:29:23 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <wchar.h>

# ifdef linux
#  include <inttypes.h>
# endif

# define SHARP 0x1
# define ZERO  0x2
# define MINUS 0x4
# define PLUS  0x8
# define SPACE 0x10

# define BUF_SIZE_PF 100000

# define COL_RES	"\033[0m"

# define COL_BLA	"\033[30m"
# define COL_RED	"\033[31m"
# define COL_GRE	"\033[32m"
# define COL_YEL	"\033[33m"
# define COL_BLU	"\033[34m"
# define COL_MAG	"\033[35m"
# define COL_CYA	"\033[36m"
# define COL_WHI	"\033[37m"

# define COL_BLA_BG	"\033[40m"
# define COL_RED_BG	"\033[41m"
# define COL_GRE_BG	"\033[42m"
# define COL_YEL_BG	"\033[43m"
# define COL_BLU_BG	"\033[44m"
# define COL_MAG_BG	"\033[45m"
# define COL_CYA_BG	"\033[46m"
# define COL_WHI_BG	"\033[47m"

typedef struct	s_conv_spec
{
	unsigned int	flags;
	int				min_field;
	int				precision;
	char			length;
	char			conv;
}				t_conv_spec;

typedef struct	s_buff_info
{
	int	len;
	int	total_size;
	int	start;
	int	add;
}				t_buff_info;

int				ft_printf(const char *format, ...);
void			parse_conv_spec(const char **format, t_conv_spec *conv_spec,
								va_list *ap);
char			*ft_strcpy(char *dest, const char *src);
int				handle_conv_spec(va_list *ap, t_conv_spec conv_spec);
int				ft_strequ(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
void			ft_putstr(const char *s);
int				decimal_itoa(char **buff, int n, t_conv_spec cs);
int				long_decimal_itoa(char **buff, long n, t_conv_spec cs);
int				llong_decimal_itoa(char **buff, long long n, t_conv_spec cs);
int				handle_decimal_int(char conv, va_list *ap, t_conv_spec cs);
int				handle_unsigned_int(char conv, va_list *ap, t_conv_spec cs);
int				handle_octal(char conv, va_list *ap, t_conv_spec cs);
int				handle_hex(va_list *ap, t_conv_spec cs);
int				handle_udecimal(char conv, va_list *ap, t_conv_spec cs);
int				octal_itoa(char **buff, unsigned int n, t_conv_spec cs);
int				ulong_octal_itoa(char **buff, unsigned long n, t_conv_spec cs);
int				ullong_octal_itoa(char **buff, unsigned long long n,
								t_conv_spec cs);
int				hex_itoa(char **buff, unsigned int n, t_conv_spec cs);
int				ulong_hex_itoa(char **buff, unsigned long n, t_conv_spec cs);
int				ullong_hex_itoa(char **buff, unsigned long long n,
								t_conv_spec cs);
int				handle_pointer(va_list *ap, t_conv_spec cs);
int				pointer_itoa(char **buff, unsigned long n, t_conv_spec cs);
int				udec_itoa(char **buff, unsigned n, t_conv_spec cs);
int				ulong_udec_itoa(char **buff, unsigned long n, t_conv_spec cs);
int				ullong_udec_itoa(char **buff, unsigned long long n,
								t_conv_spec cs);
int				handle_char(char conv, va_list*ap, t_conv_spec cs);
int				buff_char(char **buff, char c, t_conv_spec cs);
int				buff_wchar(char **buff, wint_t wc, t_conv_spec cs);
int				handle_string(char conv, va_list *ap, t_conv_spec cs);
int				buff_strwch(char **buff, wchar_t *strwch, t_conv_spec cs);
int				buff_string(char **buff, char *str, t_conv_spec cs);
char			*ft_strdup(const char *s1);
void			to_buff(const char *s, int len);
void			flush_buff();
int				handle_color(const char **format);
int				print_col1(const char **ft);
int				print_col2(const char **ft);
int				print_col3(const char **ft);
int				print_col4(const char **ft);
int				get_mb_len(wint_t wc);
int				handle_bin(va_list *ap, t_conv_spec cs);
int				ullong_bin_itoa(char **buff, unsigned long long n,
								t_conv_spec cs);
int				ulong_bin_itoa(char **buff, unsigned long n, t_conv_spec cs);
int				bin_itoa(char **buff, unsigned int n, t_conv_spec cs);

#endif
