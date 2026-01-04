/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:11:53 by julhong           #+#    #+#             */
/*   Updated: 2026/01/04 17:33:11 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	ms_perror_stat(char *err_src, int exit_status)
{
	ft_printfd(2, "%s: %s: %s\n", NAME, err_src, strerror(errno));
	return (exit_status);
}
