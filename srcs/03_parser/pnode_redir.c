/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:56 by julhong           #+#    #+#             */
/*   Updated: 2025/12/17 14:12:23 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

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
