/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:48:37 by julhong           #+#    #+#             */
/*   Updated: 2025/12/19 18:49:55 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	close_set(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	fd_cleanup(t_fds *fds)
{
	close_set(&fds->fdin);
	close_set(&fds->fdout);
	close_set(&fds->pipe_hdoc[WR_END]);
	close_set(&fds->pipe_hdoc[RE_END]);
	close_set(&fds->pipe_a[WR_END]);
	close_set(&fds->pipe_a[RE_END]);
	close_set(&fds->pipe_b[WR_END]);
	close_set(&fds->pipe_b[RE_END]);
}
