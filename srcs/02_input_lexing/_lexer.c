/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:35:56 by julhong           #+#    #+#             */
/*   Updated: 2025/11/29 15:56:23 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minsh.h>

static t_token	*make_tk_word(char **cur)
{
	char	*start;
	int		i;
	t_token	*new;

	start = *cur;
	i = 0;
	while (1)
	{
		while (start[i]
			&& !(ft_isspace(start[i]) || ft_strchr("|<>'\"", start[i])))
			i++;
		if (start[i] == '\'' || start[i] == '"')
		{
			adv_indx_quote(start, &i, start[i]);
			i++;
		}
		else
			break ;
	}
	new = new_token(start, i, TK_WORD);
	*cur = &start[i];
	return (new);
}

static void	tk_op_type(char *start, int *len, t_toktype *type)
{
	if (*start == '|')
		*type = TK_PIPE;
	else if (*start == '<')
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

static t_token	*make_tk_op(char **cur)
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

static bool	lexically_valid(char *line)
{
	int	i;

	if (!line || *line == '\0' || all_isspace(line))
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			adv_indx_quote(line, &i, line[i]);
			if (line[i] == '\0')
				return (false);
		}
		i++;
	}
	return (true);
}

bool	lex_tokens(t_minsh *msh, char *line)
{
	t_token	*new;

	if (!lexically_valid(line))
		return (false);
	while (*line)
	{
		new = NULL;
		if (ft_isspace(*line))
			adv_ptr_isspace(&line);
		else if (*line == '|' || *line == '<' || *line == '>')
			new = make_tk_op(&line);
		else
			new = make_tk_word(&line);
		if (new)
		{
			append_token(&msh->tk_start, new);
			msh->tk_ttl++;
		}
	}
	return (true);
}
