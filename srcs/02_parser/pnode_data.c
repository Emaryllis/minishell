/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pnode_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:56 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 21:18:14 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

//AST NODES

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

//REDIR NODES (for t_astype: AST_CMD)

t_redir	*new_redir_node(t_toktype type)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (malloc_fail_exit(), NULL);
	ft_bzero(node, sizeof(t_redir));
	node->type = type;
	node->hd_pfd_0 = -1;
	return (node);
}

static t_redir	*last_redir(t_redir *redir)
{
	if (redir == NULL)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	append_redir(t_redir **start, t_redir *new)
{
	t_redir	*last;

	if (!start || !new)
		return ;
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	last = last_redir(*start);
	last->next = new;
}
