/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:25:09 by julhong           #+#    #+#             */
/*   Updated: 2025/12/16 23:07:54 by julhong          ###   ########.fr       */
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
