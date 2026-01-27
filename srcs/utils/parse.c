/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/27 19:00:01 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static int	exit_print_if(int is_interactive)
{
	if (!is_interactive)
		return (1);
	ft_printf("exit\n");
	return (1);
}

/** Interactive-aware reader of input from STDIN
 * - Interactively (default) via readline with prompt etc.
 * - Non-inter via gnl (new-malized)
 * - returns t_input with .line and .eof info for caller to action
 * - !buf handles Ctrl+D (EOF) with special print if inter
 */
t_input	cell_read_input(t_msh *ms)
{
	char	*prompt;
	char	*buf;
	int		is_interactive;

	prompt = get_prompt();
	is_interactive = isatty(STDIN_FILENO);
	if (is_interactive && (sigset_msh(1), true))
	{
		buf = readline(prompt);
		sigset_msh(0);
	}
	else
	{
		buf = get_next_line(STDIN_FILENO);
		if (buf && ft_strchr(buf, '\n'))
			buf[ft_strlen(buf) - 1] = '\0';
	}
	msh_consume_sigint(ms);
	if (!buf && exit_print_if(is_interactive))
		return (free(prompt), (t_input){NULL, true});
	if ((buf[0] == '\0' || all_isspace(buf)))
		return (free(prompt), free(buf), (t_input){NULL, false});
	if (is_interactive)
		add_history(buf);
	return (free(prompt), (t_input){buf, false});
}
