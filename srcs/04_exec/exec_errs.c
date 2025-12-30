/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:11:53 by julhong           #+#    #+#             */
/*   Updated: 2025/12/25 18:00:54 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	ms_perror_stat(char *err_src, int exit_status)
{
	// eprintf("%s: %s: %s\n", NAME, err_src, strerror(errno)); ->vargs bad?
	ft_putstr_fd(NAME, STDERR_FILENO);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (exit_status);
}
