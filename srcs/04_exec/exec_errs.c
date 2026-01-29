/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:11:53 by julhong           #+#    #+#             */
/*   Updated: 2026/01/29 22:05:44 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	custom_syntax_err(char **err_src, char **err_msg)
{
	*err_src = "syntax error";
	*err_msg = "unexpected end of file";
}

static void	custom_redr_err(char **err_src, char **err_msg, int *exstat)
{
	(void)err_src;
	*err_msg = "ambiguous redirect";
	*exstat = 1;
}

int	ms_perr_exstat(char *err_src, int exstat)
{
	char	*err_msg;

	err_msg = strerror(errno);
	if (exstat == MS_ER_SYNTAX)
		custom_syntax_err(&err_src, &err_msg);
	else if (exstat == MS_ER_AMBRDR)
		custom_redr_err(NULL, &err_msg, &exstat);
	else if (exstat == MS_ER_CMDNOTF)
		err_msg = "command not found";
	else if (exstat == MS_ER_NOTEXEC)
		err_msg = "Permission denied";
	ft_printfd(2, "%s: %s: %s\n", NAME, err_src, err_msg);
	return (exstat);
}
