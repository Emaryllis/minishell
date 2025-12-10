/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/09 16:11:00 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Displays the provided prompt.
 * Returns a t_input with data read from the stdin.
 * If EOF is reached like with Ctrl+D, exits shell.
 * If empty string or all isspace, clear for next iteration.
 * Otherwise add to history, we'll work with this line.
 */
t_input	cell_read_input(const char *prompt)
{
	char	*buf;

	buf = readline(prompt);
	if (!buf)
	{
		g_sig.status = cell_exit(NULL);
		return ((t_input){NULL, true});
	}
	if (buf[0] == '\0' || all_isspace(buf))
	{
		free(buf);
		return ((t_input){NULL, false});
	}
	add_history(buf);
	return ((t_input){buf, false});
}
