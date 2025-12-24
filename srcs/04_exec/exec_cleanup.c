/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:00:59 by julhong           #+#    #+#             */
/*   Updated: 2025/12/24 08:40:10 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	fd_cls_set(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	fd_cleanup(t_exctx *ctx)
{
	fd_cls_set(&ctx->fdin);
	fd_cls_set(&ctx->fdout);
	// fd_cls_set(&ctx->pipe[WR_END]);
	// fd_cls_set(&ctx->pipe[RE_END]);
}
