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

char	*str3join(const char *s1, const char *s2, const char *s3)
{
	int		ttl_len;
	char	*res_str;

	ttl_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	res_str = malloc(ttl_len + 1);
	if (!res_str)
		return (NULL);
	res_str[0] = '\0';
	ft_strcpy(res_str, s1);
	ft_strcat(res_str, s2);
	ft_strcat(res_str, s3);
	return (res_str);
}

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
