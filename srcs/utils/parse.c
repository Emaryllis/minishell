/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/21 21:45:28 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	exit_print_if(int is_interactive)
{
	if (!is_interactive)
		return ;
	write(1, "\033[1A", 5);
	rl_redisplay();
	ft_printf("exit\n");
}

/** Interactive-aware reader of input from STDIN
 * - Interactively (default) via readline with prompt etc.
 * - Non-inter via gnl (new-malized)
 * - returns t_input with .line and .eof info for caller to action
 * - !buf handles Ctrl+D (EOF) with special print if inter
 */
t_input	cell_read_input(const char *prompt)
{
	char	*buf;
	int		is_interactive;

	is_interactive = isatty(STDIN_FILENO);
	if (is_interactive)
		buf = readline(prompt);
	else
	{
		buf = get_next_line(STDIN_FILENO);
		if (buf && ft_strchr(buf, '\n'))
			buf[ft_strlen(buf) - 1] = '\0';
	}
	if (!buf)
	{
		exit_print_if(is_interactive);
		return ((t_input){NULL, true});
	}
	if ((buf[0] == '\0' || all_isspace(buf)) && (free(buf), true))
		return ((t_input){NULL, false});
	if (is_interactive)
		add_history(buf);
	return ((t_input){buf, false});
}
