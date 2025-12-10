/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:25:09 by julhong           #+#    #+#             */
/*   Updated: 2025/12/10 23:10:17 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	parse_err_syntax(t_token *token)
{
	char	*token_str;

	if (!token)
		token_str = "newline";
	else
		token_str = token->str;
	eprintf("minishell: syntax error near unexpected token `%s'\n", token_str);
	token_str = NULL;
	return (MS_ER_SYNTAX);
}
