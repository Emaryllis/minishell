/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_garbc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:36:47 by julhong           #+#    #+#             */
/*   Updated: 2026/01/22 15:18:59 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

const char	*get_ast_type(t_astype type)
{
	if (type == AST_NULL)
		return ("NULL");
	if (type == AST_CMD)
		return ("CMD");
	if (type == AST_SUBSH)
		return ("SUBSH");
	if (type == AST_PIPE)
		return ("PIPE");
	if (type == AST_AND)
		return ("AND");
	if (type == AST_OR)
		return ("OR");
	return ("UNKNOWN");
}

void	debug_parse_garbc(t_ast *gc_start)
{
	if (!DEBUG)
		return ;
	ft_printf("***DEBUG*** AST Garbage Collection:\n");
	while (gc_start)
	{
		ft_printf("%s", get_ast_type(gc_start->type));
		if (gc_start->garbc_nxt)
			ft_printf("-");
		else
			ft_printf("\n\n");
		gc_start = gc_start->garbc_nxt;
	}
}