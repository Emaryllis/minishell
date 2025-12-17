/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:25:10 by julhong           #+#    #+#             */
/*   Updated: 2025/12/17 14:58:06 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	garbc_addfront(t_ast **start, t_ast *new)
{
	if (!start || !new)
		return ;
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	new->garbc_nxt = *start;
	*start = new;
}

t_ast	*new_ast_node(t_astype type, t_ast **garbc_start)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (malloc_fail_exit(), NULL);
	ft_bzero(node, sizeof(t_ast));
	node->type = type;
	garbc_addfront(garbc_start, node);
	return (node);
}
