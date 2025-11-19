/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/19 03:33:43 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * Returns a line read from the stdin.
 * Displays the prompt like in bash
 * before user input. If EOF is reached
 * like with Ctrl+D, it exits the shell.
 */
t_line	cell_read_line(void)
{
	char	*buf;

	print_prompt();
	buf = readline(NULL);
	if (!buf)
	{
		cell_exit(NULL);
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
