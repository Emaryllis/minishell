/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:35:56 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 23:38:10 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minsh.h>

void	adv_ptr_isspace(char **cur)
{
	char	*start;

	start = *cur;
	while (ft_isspace(*start))
		start++;
	*cur = start;
}

void	adv_indx_quote(char *start, int *i, char quote)
{
	int	cur_indx;

	cur_indx = *i;
	cur_indx++;
	while (start[cur_indx] && start[cur_indx] != quote)
		cur_indx++;
	*i = cur_indx;
}

static t_token	*tk_make_word(char **cur)
{
	char	*start;
	int		i;
	t_token	*new;

	start = *cur;
	i = 0;
	while (1)
	{
		while (start[i]
			&& !(ft_isspace(start[i]) || ft_strchr("<>\"'|()", start[i])
				|| (start[i] == '&' && start[i + 1] == '&')))
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

static bool	lexically_valid(t_msh *msh, char *line)
{
	int		i;
	char	quote;

	if (!line || *line == '\0' || all_isspace(line))
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			adv_indx_quote(line, &i, line[i]);
			if (line[i] == '\0')
			{
				ft_printfd(2, "minishell: "
					"unexpected EOF while looking for matching `%c'\n", quote);
				msh->exstat = MS_ER_SYNTAX;
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	lex_tokens(t_msh *msh, char *line)
{
	t_token	*new;

	if (!lexically_valid(msh, line))
		return (false);
	while (*line)
	{
		new = NULL;
		if (ft_isspace(*line))
			adv_ptr_isspace(&line);
		else if (ft_strchr("<>|()", *line)
			|| (*line == '&' && *(line + 1) == '&'))
			new = tk_make_op(&line);
		else
			new = tk_make_word(&line);
		if (new)
		{
			append_token(&msh->tk_start, new);
			msh->tk_ttl++;
		}
	}
	return (true);
}
