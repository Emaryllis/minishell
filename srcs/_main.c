/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 00:03:18 by julhong           #+#    #+#             */
/*   Updated: 2025/11/19 18:10:24 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"
#include <signal.h>

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	all_isspace(const char *str)
{
	while (*str)
	{
		if (!isspace(*str))
			return 0;
		str++;
	}
	return 1;
}

int main(int ac, char *av[])
{
	char	*line;

	(void)ac;
	(void)av;

	set_signals();

	line = readline("minishell$ ");
	while (line)
	{
		if (*line != '\0' && !all_isspace(line))
			add_history(line);
		free(line);
		line = readline("minishell$ ");
	}

	rl_clear_history();

	return 1;
}