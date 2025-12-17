/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:25:09 by julhong           #+#    #+#             */
/*   Updated: 2025/12/17 16:28:35 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	set_pstate_err(t_parse_state *p_state)
{
	p_state->parse_error = true;
	p_state->error_tk = p_state->cur_tk;
	p_state->cur_tk = NULL;
}

int	pr_syntax_err(t_parse_state p_state)
{
	t_token	*final_token;
	char	*token_str;

	if (p_state.unexp_end)
	{
		eprintf("minishell: syntax error: unexpected end of file\n");
		return (MS_ER_SYNTAX);
	}
	final_token = p_state.error_tk;
	if (!final_token)
		token_str = "newline";
	else
		token_str = final_token->str;
	eprintf("minishell: syntax error near unexpected token `%s'\n", token_str);
	return (MS_ER_SYNTAX);
}

static void	clear_redirs(t_redir **redir_start)
{
	t_redir	*rdr_cur;
	t_redir	*tmp;

	rdr_cur = *redir_start;
	while (rdr_cur)
	{
		tmp = rdr_cur;
		rdr_cur = rdr_cur->next;
		free(tmp);
	}
	*redir_start = NULL;
}

void	clear_ast_garbage(t_ast **gc_start)
{
	t_ast	*gc_cur;
	t_ast	*tmp;

	gc_cur = *gc_start;
	while (gc_cur)
	{
		if (gc_cur->cmd_av)
		{
			free (gc_cur->cmd_av);
			gc_cur->cmd_av = NULL;
		}
		clear_redirs(&gc_cur->redir_start);
		tmp = gc_cur;
		gc_cur = gc_cur->garbc_nxt;
		free(tmp);
	}
	*gc_start = NULL;
}
