/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_hndl_logi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:52:45 by julhong           #+#    #+#             */
/*   Updated: 2026/02/02 00:10:47 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	exc_hdl_and(t_ast *cur_node, t_exctx p_ctx, t_msh *ms)
{
	int exstat;
	
	exstat = proc_ast_node(cur_node->left, p_ctx, ms);
	if (exstat != EXIT_SUCCESS)
		return (exstat);
	return (proc_ast_node(cur_node->right, p_ctx, ms));
}

int	exc_hdl_orr(t_ast *cur_node, t_exctx p_ctx, t_msh *ms)
{
	int exstat;
	
	exstat = proc_ast_node(cur_node->left, p_ctx, ms);
	if (exstat == EXIT_SUCCESS)
		return (exstat);
	return (proc_ast_node(cur_node->right, p_ctx, ms));
}
