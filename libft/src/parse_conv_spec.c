/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:16:54 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:41:02 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		atoi_format(const char **format)
{
	int	ret;

	ret = 0;
	while (**format >= '0' && **format <= '9')
		ret = 10 * ret + *((*format)++) - '0';
	return (ret);
}

static void		get_options(const char **format, t_conv_spec *conv_spec)
{
	conv_spec->flags = 0;
	while (**format == '#' || **format == '0' || **format == '-'
		|| **format == '+' || **format == ' ')
	{
		if (**format == '#')
			conv_spec->flags |= SHARP;
		else if (**format == '0')
			conv_spec->flags |= ZERO;
		else if (**format == '-')
			conv_spec->flags |= MINUS;
		else if (**format == '+')
			conv_spec->flags |= PLUS;
		else if (**format == ' ')
			conv_spec->flags |= SPACE;
		++(*format);
	}
}

static void		get_length(const char **form, t_conv_spec *conv_spec)
{
	if (**form == 'h')
	{
		if (*(*(form) + 1) == 'h')
		{
			conv_spec->length = 'H';
			++(*form);
		}
		else
			conv_spec->length = 'h';
	}
	else if (**form == 'l')
	{
		if (*(*(form) + 1) == 'l')
		{
			conv_spec->length = 'L';
			++(*form);
		}
		else
			conv_spec->length = 'l';
	}
	else
		conv_spec->length = (**form == 'j' || **form == 'z') ? **form : 0;
	*form = conv_spec->length ? *form + 1 : *form;
}

static void		get_precision(const char **format, t_conv_spec *conv_spec,
							va_list *ap)
{
	++(*format);
	if (**format == '*')
	{
		(*format)++;
		conv_spec->precision = va_arg(*ap, int);
	}
	else
		conv_spec->precision = atoi_format(format);
}

void			parse_conv_spec(const char **format, t_conv_spec *conv_spec,
								va_list *ap)
{
	get_options(format, conv_spec);
	if (**format == '*')
	{
		if ((conv_spec->min_field = (int)va_arg(*ap, int)) < 0)
		{
			conv_spec->flags |= MINUS;
			conv_spec->min_field = -conv_spec->min_field;
		}
		(*format)++;
	}
	else
		conv_spec->min_field = atoi_format(format);
	if (**format == '.')
		get_precision(format, conv_spec, ap);
	else
		conv_spec->precision = -1;
	get_length(format, conv_spec);
	conv_spec->conv = **format;
	if (conv_spec->conv != '\0')
		++(*format);
}
