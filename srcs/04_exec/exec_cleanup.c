/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:00:59 by julhong           #+#    #+#             */
/*   Updated: 2025/12/23 15:57:24 by julhong          ###   ########.fr       */
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

void	fd_cleanup(t_exctx *ctx)
{
	close_set(&ctx->fdin);
	close_set(&ctx->fdout);
	// close_set(&ctx->pipe[WR_END]);
	// close_set(&ctx->pipe[RE_END]);
}
