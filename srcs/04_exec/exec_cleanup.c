/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:00:59 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 15:36:26 by julhong          ###   ########.fr       */
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

/** Generic main_cleanup++ in child
 * - cleans up the main minishell allocations that fork with child
 * - also closes the current fds (if any) used to redirect stdin/out
 * 
 * Note
 * - any additional allocations in child will have to be handled separately
 * - e.g. PIPE: internal pipe fds; CMD: allocated char** for execve
 */
int	ch_msh_clean(t_exctx ctx, t_msh *ms)
{
	fd_clstwo(ctx.fdio);
	if (!ctx.in_minsh)
	{
		ms->shell_exit = true;
		main_cleanup(ms);
	}
	return (1);
}
