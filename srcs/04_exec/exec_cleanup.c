/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:00:59 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 00:33:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	fd_clset(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	return (1);
}

int	fd_clstwo(int fd[2])
{
	fd_clset(&fd[0]);
	fd_clset(&fd[1]);
	return (1);
}

int	ch_msh_clean(t_exctx ctx, t_msh *ms)
{
	fd_clstwo(ctx.fdio);
	if (!ctx.in_minsh)
		main_cleanup(ms);
	return (1);
}
