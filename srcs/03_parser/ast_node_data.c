/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:25:10 by julhong           #+#    #+#             */
/*   Updated: 2025/12/11 20:43:00 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

t_ast	*new_ast_node(t_astype type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (malloc_fail_exit(), NULL);
	ft_bzero(node, sizeof(t_ast));
	node->type = type;
	return (node);
}

t_redir	*new_redir_node(t_toktype type)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (malloc_fail_exit(), NULL);
	ft_bzero(node, sizeof(t_redir));
	node->type = type;
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
