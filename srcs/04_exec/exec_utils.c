/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:13:50 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 19:06:56 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	interp_wtstat(int wstat)
{
	if (WIFEXITED(wstat))
		return (WEXITSTATUS(wstat));
	else if (WIFSIGNALED(wstat))
		return (128 + WTERMSIG(wstat));
	return (0);
}

/** Fork settings for children: msh flag, and signals
 * type == 0: default working children, cmds
 * type == 1: coordinating "mini-shells" that need to wait for statuses
 */
int	fork_set_ch(t_exctx *ctx, int type)
{
	ctx->in_minsh = false;
	if (type == 0)
		sigset_child_dfl();
	else
	{
		sigset_generic(SIGINT, 0);
		sigset_generic(SIGQUIT, 0);
	}
	return (1);
}
