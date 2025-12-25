/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:02:46 by egoh              #+#    #+#             */
/*   Updated: 2025/12/25 19:28:17 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

volatile t_sig	g_sig;

t_newsig		g_newsig;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (g_sig.child_pid > 0)
		{
			kill(g_sig.child_pid, SIGINT);
			set_status(128 + SIGINT);
			return ;
		}
		set_status(EXIT_FAILURE);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Writing quit 3 since MACRO for SIGQUIT is 3
void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_sig.child_pid > 0)
		{
			kill(g_sig.child_pid, SIGQUIT);
			g_sig.status = 128 + SIGQUIT;
			write(1, "Quit: 3\n", 8);
			return ;
		}
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * Sets up signal handlers for SIGINT and SIGQUIT.
 * Non-interactive mode will follow default behavior.
 * Interactive mode will follow subject's requirements.
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_sig.child_pid = 0;
	set_status(EXIT_SUCCESS);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("sigaction SIGINT");
	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("sigaction SIGQUIT");
}
