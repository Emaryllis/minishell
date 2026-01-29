/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/29 15:52:11 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// Needs to be atomic safe
// void	set_status(int status)
// {
// 	g_sig.status = status;
// }

void	debug_print(const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	if (DEBUG)
		printf(format, va);
	va_end(va);
}

int	malloc_error(int ret)
{
	ft_printfd(2, NAME": malloc: Cannot allocate memory\n");
	return (ret);
}

int	malloc_fail_exit(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}
