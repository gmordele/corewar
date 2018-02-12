#include <stdlib.h>
#include "libft.h"
#include "asm.h"
#include "op.h"

static int		add_line(char **ret, char **str, int begin, int end)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	if (*ret == NULL)
		*ret = ft_strndup(*str + begin, end - begin);
	else
	{
		len = ft_strlen(*ret);
		if ((tmp = malloc(len + 2)) == NULL)
			return (-1);
		tmp[len] = '\n';
		tmp[len + 1] = '\0';
		ft_memcpy(tmp, *ret, len);
		ft_strdel(ret);
		if ((tmp2 = ft_strndup(*str + begin, end - begin)) == NULL)
		{
			ft_strdel(&tmp);
			return (-1);
		}
		*ret = ft_strjoin(tmp, tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (*ret == NULL ? -1 : 0);
}

static void		init_get_string(t_get_string *gs, int i, int row)
{
	gs->begin = i + 1;
	gs->end = gs->begin;
	gs->ret = NULL;
	gs->n_row = row;
}

static int		get_string_loop(char **str, t_get_string *gs, t_data *data)
{
	while ((*str)[gs->end] != '\"')
	{
		if ((*str)[gs->end] == '\0')
		{
			if (add_line(&(gs->ret), str, gs->begin, gs->end) < 0)
			{
				ft_strdel(&(gs->ret));
				return (-1);
			}
			ft_strdel(str);
			if (get_next_line(data->fd, str) <= 0)
			{
				ft_strdel(&(gs->ret));
				return (-1);
			}
			++(gs->n_row);
			gs->begin = 0;
			gs->end = 0;
		}
		else
			++(gs->end);
	}
	return (0);
}

static char		*get_string(char **str, int *i, int *row, t_data *data)
{
	t_get_string	gs;
	
	init_get_string(&gs, *i, *row);
	if (get_string_loop(str, &gs, data) < 0)
		return (NULL);
	if (add_line(&(gs.ret), str, gs.begin, gs.end) < 0)
		ft_strdel(&(gs.ret));
	else
	{
		*row = gs.n_row;
		*i = gs.end + 1;
	}
	return (gs.ret);
}

t_token			*token_string(char **str, int *i, int *row, t_data *data)
{
	t_token	*ret;
	char	*str_val;
	int		tmp_i;
	int		tmp_row;

	tmp_i = *i;
	tmp_row = *row;
	if ((str_val = get_string(str, &tmp_i, &tmp_row, data)) == NULL)
		return (NULL);
	ret = new_token(TOK_STRING, *row, *i + 1, data);
	if (ret != NULL)
	{
		*i = tmp_i;
		*row = tmp_row;
		ret->str_val = str_val;
	}
	else
		free(str_val);
	return (ret);
}
