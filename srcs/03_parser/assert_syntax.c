/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:25:09 by julhong           #+#    #+#             */
/*   Updated: 2025/12/11 21:45:53 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	set_pstate_err(t_parse_state *p_state)
{
	p_state->parse_error = true;
	p_state->error_tk = p_state->cur_tk;
	p_state->cur_tk = NULL;
}	

int	pr_syntax_err(t_token *token)
{
	char	*token_str;

	if (!token)
		token_str = "newline";
	else
		token_str = token->str;
	eprintf("minishell: syntax error near unexpected token `%s'\n", token_str);
	return (MS_ER_SYNTAX);
}
