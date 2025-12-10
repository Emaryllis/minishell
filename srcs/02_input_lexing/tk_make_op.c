/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_make_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:06:16 by julhong           #+#    #+#             */
/*   Updated: 2025/12/10 21:32:51 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	what_redir(char *start, int *len, t_toktype *type)
{
	if (*start == '<')
	{
		if (start[1] && start[1] == '<')
		{
			*len += 1;
			*type = TK_RDR_HERE;
		}
		else
			*type = TK_RDR_IN;
	}
	else if (*start == '>')
	{
		if (start[1] && start[1] == '>')
		{
			*len += 1;
			*type = TK_RDR_APND;
		}
		else
			*type = TK_RDR_OUT;
	}
}

static void	tk_op_type(char *start, int *len, t_toktype *type)
{
	if (*start == '<' || *start == '>')
		what_redir(start, len, type);
	else if (*start == '|')
	{
		if (start[1] && start[1] == '|')
		{
			*type = TK_OR;
			*len += 1;
		}
		else
			*type = TK_PIPE;
	}
	else if (*start == '&' && start[1] == '&')
	{
		*type = TK_AND;
		*len += 1;
	}
	else if (*start == '(' || *start == ')')
		*type = TK_SUBSH;
}

t_token	*tk_make_op(char **cur)
{
	char		*start;
	int			len;
	t_toktype	type;
	t_token		*new;

	start = *cur;
	len = 1;
	tk_op_type(start, &len, &type);
	new = new_token(start, len, type);
	*cur = start + len;
	return (new);
}
