/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:35:56 by julhong           #+#    #+#             */
/*   Updated: 2025/11/25 17:48:51 by julhong          ###   ########.fr       */
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
			*type = TK_REDIR_HERE;
		}
		else
			*type = TK_REDIR_IN;
	}
	else if (*start == '>')
	{
		if (start[1] && start[1] == '>')
		{
			*len += 1;
			*type = TK_REDIR_APND;
		}
		else
			*type = TK_REDIR_OUT;
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

bool	lex_tokens(t_minsh *minsh, char *cur)
{
	t_token	*new;

	if (!lexically_valid(cur))
		return (false);
	while (*cur)
	{
		new = NULL;
		if (ft_isspace(*cur))
			adv_ptr_isspace(&cur);
		else if (*cur == '|' || *cur == '<' || *cur == '>')
			new = make_tk_op(&cur);
		else
			new = make_tk_word(&cur);
		if (new)
		{
			append_token(&minsh->tk_start, new);
			minsh->tk_ttl++;
		}
	}
	return (true);
}

// int	main(int ac, char *av[])
// {
// 	t_minsh	minsh;

// 	if (ac != 2)
// 		return (1);

// 	ft_bzero(&minsh, sizeof(t_minsh));
// 	if (!lex_tokens(&minsh, av[1]))
// 		return (1);

// 	for (t_token *tk = minsh.tk_start; tk; tk = tk->next)
// 		printf("%s\n", tk->str);
// 	return (0);
// }