/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:58:07 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 21:18:14 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	clear_redirs(t_redir **redir_start)
{
	t_redir	*rdr_cur;
	t_redir	*tmp;

	rdr_cur = *redir_start;
	while (rdr_cur)
	{
		tmp = rdr_cur;
		rdr_cur = rdr_cur->next;
		fd_clset(&tmp->hd_pfd_0);
		free(tmp);
	}
	*redir_start = NULL;
}

void	clear_ast_garbage(t_ast **gc_start)
{
	t_ast	*gc_cur;
	t_ast	*tmp;

	gc_cur = *gc_start;
	while (gc_cur)
	{
		if (gc_cur->cmd_av)
		{
			free (gc_cur->cmd_av);
			gc_cur->cmd_av = NULL;
		}
		clear_redirs(&gc_cur->redir_start);
		tmp = gc_cur;
		gc_cur = gc_cur->garbc_nxt;
		free(tmp);
	}
	*gc_start = NULL;
}
