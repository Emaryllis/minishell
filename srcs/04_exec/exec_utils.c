/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:13:50 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 01:28:18 by julhong          ###   ########.fr       */
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

int	fork_set_ch(t_exctx ctx)
{
	ctx.in_minsh = false;
	sigset_child_dfl();
	return (1);
}
