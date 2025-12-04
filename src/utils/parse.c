/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/04 15:23:06 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
 * Returns a line read from the stdin.
 * Displays the prompt like in bash
 * before user input. If EOF is reached
 * like with Ctrl+D, it exits the shell.
 */
t_line	cell_read_line(const char *prompt)
{
	char	*buf;

	buf = readline(prompt);
	if (!buf)
	{
		g_sig.status = cell_exit(NULL);
		return ((t_line){NULL, true});
	}
	if (buf[0] == '\0')
	{
		free(buf);
		return ((t_line){NULL, false});
	}
	add_history(buf);
	return ((t_line){buf, false});
}
