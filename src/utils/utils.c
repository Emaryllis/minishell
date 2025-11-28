/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/29 07:57:41 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

// Needs to be atomic safe
void	set_status(int status)
{
	g_sig.status = status;
}

void	debug_print(const char *format, va_list args)
{
	if (DEBUG)
		printf(format, args);
}

int	malloc_error(int ret)
{
	eprintf(NAME": malloc: Cannot allocate memory");
	set_status(EXIT_FAILURE);
	return (ret);
}

/** Only used in cell_cd */
int	handle_error(char *target, const char *format, bool nsf)
{
	if (nsf)
		eprintf(NAME": cd: %s: No such file or directory\n", target);
	else
		eprintf(format);
	free(target);
	return (EXIT_FAILURE);
}
