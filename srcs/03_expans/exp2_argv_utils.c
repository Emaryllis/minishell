/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp2_argv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:25:29 by julhong           #+#    #+#             */
/*   Updated: 2026/02/10 11:01:10 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	quote_filter(char **cur, char *arg, int *i, t_quote *q)
{
	char	*start;

	start = *cur;
	if ((*start == '\'' && *q == D_QT) || (*start == '"' && *q == S_QT))
		arg[(*i)++] = *start;
	else if ((*start == '\'' && *q == S_QT)
		|| (*start == '"' && *q == D_QT))
		*q = NO_QT;
	else if (*start == '\'' && *q == NO_QT)
		*q = S_QT;
	else if (*start == '"' && *q == NO_QT)
		*q = D_QT;
	*cur = ++start;
}

/** Quote aware stripping, splitting, glob marking of a string
 * Returns: 
 * - the (new) sub-arg
 * - str (ptr to remainder of str to process)
 * 
 * Usage:
 * - *str != '\0' indicates more to process
 * - *str == '\0' indicates finished stripping &/or splitting the arg
 */
static t_strips	strip_split_gmark_nxt(char *str)
{
	char	*arg;
	t_quote	qt;
	int		i;

	adv_ptr_isspace(&str);
	arg = ft_strdup(str);
	qt = NO_QT;
	i = 0;
	while (*str)
	{
		if (ft_strchr("'\"", *str)
			|| (*str == '$' && qt == NO_QT
				&& ft_strchr("'\"", *(str + 1)) && (str++, true)))
			quote_filter(&str, arg, &i, &qt);
		else if (ft_isspace(*str) && qt == NO_QT && (adv_ptr_isspace(&str), 1))
		{
			arg[i] = '\0';
			break ;
		}
		else if ((*str == '*' && qt == NO_QT) && str++)
			arg[i++] = JAMES_BOND;
		else
			arg[i++] = *str++;
	}
	return (arg[i] = '\0', (t_strips){arg, str});
}

void	strip_split_gmark_loop(t_expav *v)
{
	t_strips	ssg_ret;

	ssg_ret = strip_split_gmark_nxt(v->tmp_argv[v->i]);
	v->output_argv[v->j++] = ssg_ret.sub_arg;
	while (*ssg_ret.split_prog != '\0')
	{
		ssg_ret = strip_split_gmark_nxt(ssg_ret.split_prog);
		if (v->j >= v->ac_max)
			v->output_argv = realloc_str_arr(v->output_argv, v->j, &v->ac_max,
					v->ac_max * 2);
		v->output_argv[v->j++] = ssg_ret.sub_arg;
	}
}
