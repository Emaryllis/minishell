/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_toks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:45:14 by julhong           #+#    #+#             */
/*   Updated: 2026/01/27 21:15:12 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static const char	*get_tk_type(t_toktype type)
{
	if (type == TK_WORD)
		return ("WORD -------");
	if (type == TK_RDR_IN)
		return ("RDR_IN -----");
	if (type == TK_RDR_HERE)
		return ("RDR_HERE ---");
	if (type == TK_RDR_OUT)
		return ("RDR_OUT ----");
	if (type == TK_RDR_APND)
		return ("RDR_APND ---");
	if (type == TK_SUBSH_OPN)
		return ("SUBSH_OPN --");
	if (type == TK_SUBSH_CLS)
		return ("SUBSH_CLS --");
	if (type == TK_PIPE)
		return ("PIPE -------");
	if (type == TK_AND)
		return ("AND --------");
	if (type == TK_OR)
		return ("OR ---------");
	return ("UNKNOWN");
}

void	debug_lex_pr_tk(t_msh *ms)
{
	t_token	*tk;

	if (!DEBUG)
		return ;
	tk = ms->tk_start;
	ft_printf("***DEBUG*** Tokens:\n");
	while (tk)
	{
		printf("%s\t%s\n", get_tk_type(tk->type), tk->str);
		tk = tk->next;
	}
	ft_printf("\n");
}
